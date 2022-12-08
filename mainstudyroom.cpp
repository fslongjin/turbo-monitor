#include "mainstudyroom.h"
#include "ui_mainstudyroom.h"
#include "mainwindow.h"
MainStudyRoom::MainStudyRoom(QString qstudyRoomId,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainStudyRoom)
{
    ui->setupUi(this);
    studyRoomId=qstudyRoomId;
    alarmNow = new AlarmNew();
    videoWidget = new QVideoWidget();
    videoWidget2 = new QVideoWidget();
    videoWidget3 = new QVideoWidget();
    videoWidget4 = new QVideoWidget();
    ui->gridLayout_2->addWidget(videoWidget);
    ui->gridLayout_2->addWidget(videoWidget2);
    ui->gridLayout_2->addWidget(videoWidget3);
    ui->gridLayout_2->addWidget(videoWidget4);
    startTime  = QDateTime::currentDateTime();
    FreshPlayer();
    qDebug()<<"startTime"<<startTime;
    danmuSocket = new WebSocket
            ("ws://175.178.85.36:10010/interaction/websocket", studyRoomId, MainWindow::userName);
    qDebug()<<danmuSocket->whaturl;
    danmuSocket->connectToServer();
}
void MainStudyRoom::FreshPlayer()
{
    request.setUrl(QUrl("http://175.178.85.36:10010/studyRoom/getDeskMate"));                           //修改成服务器url
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("authentication",MainWindow::token.toLatin1());
    request.setRawHeader("userId",MainWindow::userId.toLatin1());
    request.setRawHeader("studyRoomId",studyRoomId.toLatin1());
    qDebug()<<studyRoomId;
    preplay=manager->get(request);
    QEventLoop eventLoop;
    connect(preplay, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();//等待请求返回
    QByteArray byteArray=preplay->readAll();
    jsonObject=jsonManager.fromJson(byteArray).object();
    qDebug()<<jsonObject;
}
MainStudyRoom::~MainStudyRoom()
{
    delete ui;
}
void MainStudyRoom::closeEvent(QCloseEvent* event)
{
    QDateTime nowTime=QDateTime::currentDateTime();
    qDebug()<<startTime.secsTo(nowTime)*1.0/3600;
}

void MainStudyRoom::on_fleshBtn_clicked()
{
    FreshPlayer();
}

void MainStudyRoom::on_alarmBtn_clicked()
{
    alarmNow->show();
}
