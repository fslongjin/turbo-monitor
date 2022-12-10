
#include <QObject>
class QWebSocket;
class QTimer;
class WsClientPrivate;
class WebSocket : public QObject
{
    Q_OBJECT
public:
    ~WebSocket();
    explicit WebSocket(const QString &serverIpPort, const QString &gatewayId, const QString &gatewayName);
    void connectToServer();

        /**
         * @brief 发送消息到服务器
         *
         * @param type    消息类型，如 METRICS, ECHO 等
         * @param message 消息
         */
        void sendMessage(const QString &type, const QString &message);
    QString whaturl;
    signals:
        /**
         * @brief 与服务器连接成功或者连接断开的信号
         *
         * @param yes 连接成功时 yes 为 true, 连接断开时 yes 为 false
         */
        void connected(bool yes);

        /**
         * @brief 收到消息
         *
         * @param message 消息
         */
        void messageReceived(const QString &message);

  public:
        WsClientPrivate *d;


};


