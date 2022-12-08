#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include "soloplay.h"
#include "liveroom.h"
#include "createvlog.h"
#include "show_all_studyroom/studyroompage.h"
#include "show_all_studyroom/studyroomshowwidget.h"
#include "createstudyroom.h"
#include "mainstudyroom.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
class QPushButton;
class QVBoxLayout;

class QHBoxLayout;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPushButton *soloPlayButton,*mulPlayButton,*pointPlayButton;
    LiveRoom *liveRoom,*watchLiveRoom;
    StudyRoomShowWidget *studyRoomShowWidget;
    CreateVlog *createVlogWindow;
    CreateStudyRoom *createStudyRoomDialog;
    QPushButton *createVlog,*joinLiveBtn;
    QPushButton *createStudyRoomBtn;
    QPushButton *showJoinedStudyRoomBtn;
    QLineEdit *lineEdit;//自习室的
    QPushButton *showStudyRoomBtn;
    QWidget *centreWid ;
    QVBoxLayout *centreLay;
    QHBoxLayout *mainFuncLay,*bottomFuncLay;
    MainStudyRoom *mainStudyRoom;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *preplay;
    QNetworkRequest request;
    QJsonDocument jsonManager;
    QJsonObject jsonObject;
     QLabel *labeltemp;
public://加入直播窗口
    QWidget *joinWidget;
    QPushButton *mulJoinBtn;
    QLabel *joinLabel;
    QLineEdit *joinLineEdit;
    QVBoxLayout *joinCentreLay;
    void init();
    void Connect();
    QJsonObject getStudyRoomIdMessage(QString temp);
    void JoinStudyRoomFun(QString temp);
    static bool onLine;
    static QString userId;
    static QString token;
    static QString pullUrl;
    static QString roomId;
    static QString userName;
    static QString imageUrl;
    static QString pushUrl;
    static QString key;
public slots:
    void show_mainwindow();
    void InitSoloWindow();
    void InitCreateVlog();
    void InitJoinLive();
    void InitCreateStudyRoom();
    void CreateJoinLive();
    void GetAllUserStudyRoom();
    void GetAllJoinedStudyRoom();
    void InitJoinStudyRoom();
    void JoinStudyRoom();
};
#endif // MAINWINDOW_H
