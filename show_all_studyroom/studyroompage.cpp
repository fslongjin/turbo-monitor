#include "studyroompage.h"
#include "ui_studyroompage.h"
#include <QJsonObject>
#include <QtDebug>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
StudyRoomPage::StudyRoomPage(QJsonObject jsonObject, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudyRoomPage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    qDebug()<<jsonObject;
    studyRoomId=jsonObject["studyRoomId"].toString();
    studyRoomImageName=jsonObject["studyRoomImageName"].toString();
    studyRoomIntroduction=jsonObject["studyRoomIntroduction"].toString();
    studyRoomMemberNumber=jsonObject["studyRoomMemberNumber"].toString();
    studyRoomName=jsonObject["studyRoomName"].toString();
    studyRoomPassword=jsonObject["studyRoomPassword"].toString();
    studyRoomType=jsonObject["studyRoomType"].toString();
    ui->roomId->setText("自习室ID:"+studyRoomId);
    ui->roomId->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->roomName->setText("自习室名字"+studyRoomName);
    ui->memberNumber->setText("自习室人数:"+studyRoomMemberNumber);
    ui->introduction->setText("自习室简介:"+studyRoomIntroduction);
    connect(ui->deleteBtn,&QPushButton::clicked,this,&StudyRoomPage::DeleteStudyRoom);
}

StudyRoomPage::~StudyRoomPage()
{
    delete ui;
}
void StudyRoomPage::DeleteStudyRoom()
{
    QString RoomId;
        RoomId=studyRoomId;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QString url="http://175.178.85.36:10010/studyRoom/deleteStudyRoom/";
    url+=RoomId;
    request.setUrl(QUrl(url));
    request.setRawHeader("Content-Type","application/json");
    QNetworkReply *preplay=manager->deleteResource(request);
    QByteArray bytes = preplay->readAll();
    QJsonObject jsonObject;
    QJsonDocument jsonManager;
    jsonObject =jsonManager.fromJson(bytes).object();
    qDebug() << jsonObject;
    qDebug()<<"DELETE"<<studyRoomId;
    emit change();
}
