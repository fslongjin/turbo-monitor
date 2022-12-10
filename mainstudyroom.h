#ifndef MAINSTUDYROOM_H
#define MAINSTUDYROOM_H
#include "web_socket/websocket.h"
#include "alarmnew.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QtNetwork>
#include <QJsonDocument>
namespace Ui {
class MainStudyRoom;
}

class MainStudyRoom : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainStudyRoom(QString qstudyRoomId="null",QWidget *parent = nullptr);
    ~MainStudyRoom();
    void FreshPlayer();
    void closeEvent(QCloseEvent*event);
private slots:
    void on_fleshBtn_clicked();

    void on_alarmBtn_clicked();

private:
    Ui::MainStudyRoom *ui;
    QMediaPlayer *player1,*player2,*player3,*player4;
    QVideoWidget *videoWidget,*videoWidget2,*videoWidget3,*videoWidget4;
    QString studyRoomId;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *preplay;
    QNetworkRequest request;
    QJsonDocument jsonManager;
    QJsonObject jsonObject;
    QDateTime startTime;
    WebSocket *danmuSocket;
    AlarmNew *alarmNow;
};

#endif // MAINSTUDYROOM_H
