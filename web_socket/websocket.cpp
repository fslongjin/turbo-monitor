#include "websocket.h"
#include <QWebSocket>
#include <QTimer>
#include <QDebug>
class WsClientPrivate {
public:
    WsClientPrivate(const QString &serverIpPort, const QString &gatewayId, const QString &gatewayName);
    ~WsClientPrivate();

    // 连接到服务器的 Websocket 连接字符串，例如 ws://127.0.0.1:9321?gatewayId=1&gatewayName=bob
    QString connectUrl() const;

    QString serverIpPort;   // 服务器的 IP Port
    QString gatewayId;      // 设备网关 Id
    QString gatewayName;    // 设备网关名字
    QWebSocket *socket;     // Websocket 对象
    bool connected;         // 是否已经和服务器连接上
    QTimer *heartbeatTimer; // 心跳定时器
    QTimer *reconnectTimer; // 重连定时器
    int heartbeatInterval = 10000; // 心跳间隔
    int reconnectInterval = 5000;  // 重连间隔
    int reconnectCount    = 0;     // 重连次数
};

WsClientPrivate::WsClientPrivate(const QString &serverIpPort, const QString &gatewayId, const QString &gatewayName) {
    this->serverIpPort   = serverIpPort;
    this->gatewayId      = gatewayId;
    this->gatewayName    = gatewayName;
    this->connected      = false;
    this->socket         = new QWebSocket();
    this->heartbeatTimer = new QTimer();
    this->reconnectTimer = new QTimer();

    // 启动心跳定时器，定时给服务器发送心跳消息
}

WsClientPrivate::~WsClientPrivate() {
    heartbeatTimer->stop();
    heartbeatTimer->deleteLater();
    reconnectTimer->stop();
    reconnectTimer->deleteLater();
    socket->close();
    socket->deleteLater();
}

QString WsClientPrivate::connectUrl() const {
    return QString("%1/%2%3")
                .arg(serverIpPort)
                .arg(gatewayId)
                .arg(gatewayName);
}

WebSocket::WebSocket(const QString &serverIpPort, const QString &gatewayId, const QString &gatewayName) : QObject()
{
    d = new WsClientPrivate(serverIpPort, gatewayId, gatewayName);
    whaturl = d->connectUrl();
        // 连接成功
        QObject::connect(d->socket, &QWebSocket::connected, [this] {
            d->connected = true;
            d->heartbeatTimer->start(d->heartbeatInterval); // 连接成功时启动心跳计时器
            d->reconnectTimer->stop();                      // 连接成功时关闭重连计时器

            emit this->connected(true);
        });

        // 连接断开
        QObject::connect(d->socket, &QWebSocket::disconnected, [this] {
            d->connected = false;
            d->heartbeatTimer->stop();                      // 连接断开时关闭心跳计时器
            d->reconnectTimer->start(d->reconnectInterval); // 连接断开时启动重连计时器

            emit this->connected(false);
        });

        // 收到消息
        QObject::connect(d->socket, &QWebSocket::textMessageReceived, [this](const QString &message) {
            emit this->messageReceived(message);
        });

        // 定时发送心跳，当服务器端在指定时间内没有收到客户端的心跳消息，服务器会主动断开对应的连接
        QObject::connect(d->heartbeatTimer, &QTimer::timeout, [this] {
            if (d->connected) {
                d->socket->sendTextMessage(R"({"type": "HEARTBEAT"})");
            }
        });

        // 连接断开后定时尝试重连
        // 定时 5 秒尝试连接到服务器，如果连接断开了，测试方法: 连接上服务器，然后把服务器关闭，再打开服务器，查看连接状态。
        // 如果不这么做，服务器重启后，设备网关连接断开不主动自动重连，那么只有重启设备网关的程序才会再次连接。
        QObject::connect(d->reconnectTimer, &QTimer::timeout, [this] {
            this->connectToServer(); // 如果已经是连接成功状态，不会重复连接
        });
}
WebSocket::~WebSocket() {
    delete d;
}
void WebSocket::connectToServer() {
    // 1. 如果已经连接，直接返回，不要重复连接
    // 2. 如果重连计时器没有启动，则启动他，当没有连接到服务器的时候，自动尝试重连
    // 3. 连接到服务器

    // [1] 如果已经连接，直接返回，不要重复连接
    if (d->connected) {
        return;
    }

    // [2] 如果重连计时器没有启动，则启动他，当没有连接到服务器的时候，自动尝试重连
    if (!d->reconnectTimer->isActive()) {
        d->reconnectTimer->start(d->reconnectInterval);
    }

    // [3] 连接到服务器
    QString url = d->connectUrl();
    d->socket->open(QUrl(url));

    d->reconnectCount++;
    qDebug().noquote() << QString("第 %1 次尝试连接到服务器 %2 ...").arg(d->reconnectCount).arg(url);
}

void WebSocket::sendMessage(const QString &type, const QString &message) {
    // 未连接，不发送消息
    if (!d->connected) {
        return;
    }

    // 消息使用 JSON 格式，如 {"type": "ECHO", "content": "Hello"}
    //type:this.roomId+this.User.userName
    QString msg = QString(R"({"userInformation": "%1", "messageToSend": "%2","type":"弹幕"})").arg(type).arg(message);
    d->socket->sendTextMessage(msg);
}
