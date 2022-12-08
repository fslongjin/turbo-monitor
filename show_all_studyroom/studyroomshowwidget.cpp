#include "studyroomshowwidget.h"
#include "ui_studyroomshowwidget.h"
#include "mainwindow.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtDebug>
StudyRoomShowWidget::StudyRoomShowWidget(QJsonArray jsonArray , QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudyRoomShowWidget)
{
    ui->setupUi(this);
    studyVector.resize(jsonArray.count());
    qDebug()<<jsonArray.count();
    for(int i=0;i<jsonArray.count();i++)
    {
        studyVector[i]=new StudyRoomPage(jsonArray[i].toObject(),this);
        studyVector[i]->setFixedSize(380,200);
        connect(studyVector[i],&StudyRoomPage::change,this,&StudyRoomShowWidget::Flesh);
        ui->verticalLayout->addWidget(studyVector[i],1);
    }

    QJsonObject test;
    test.insert("studyRoomId","test1");
    test.insert("studyRoomImageName","test2");
    test.insert("studyRoomIntroduction","test3");
    test.insert("studyRoomMemberNumber","test4");
    test.insert("studyRoomName","test5");
    test.insert("studyRoomPassword","test6");
    testt=new StudyRoomPage(test,this);
    testt->setFixedSize(380,400);
    ui->verticalLayout->addWidget(testt,1);
    connect(testt,&StudyRoomPage::change,this,&StudyRoomShowWidget::Flesh);

    ui->verticalLayout->addStretch(10);
}

StudyRoomShowWidget::~StudyRoomShowWidget()
{
    delete ui;
}
void StudyRoomShowWidget::Flesh()
{

    QLayoutItem *child;
     while ((child =ui->verticalLayout->takeAt(0)) != 0)
     {
            //setParent为NULL，防止删除之后界面不消失
            if(child->widget())
            {
                child->widget()->setParent(NULL);
                delete child->widget();//释放
            }

            delete child;
     }
    QUrl url("http://175.178.85.36:10010/studyRoom/getAllStudyRoomByUserId");
    QUrlQuery query;
    QNetworkRequest request;
    QJsonDocument jsonManager;
    QJsonObject jsonObject;
    QNetworkReply *preplay;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    query.addQueryItem("userId",MainWindow::userId);
    url.setQuery(query);
    qDebug()<<url;
    request.setUrl(url);
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("authentication",MainWindow::token.toLatin1());
    jsonManager.setObject(jsonObject);
    QByteArray byteArray = jsonManager.toJson();
    preplay=manager->get(request);
    QEventLoop eventLoops;
    connect(preplay, &QNetworkReply::finished,&eventLoops ,&QEventLoop::quit);
    eventLoops.exec();
    QByteArray bytes;
    bytes = preplay->readAll();
    jsonObject = jsonManager.fromJson(bytes).object();
    QJsonValue jsonValue = jsonObject["data"];
    QJsonArray jsonArray = jsonObject["data"].toArray();
    studyVector.resize(jsonArray.count());
    qDebug()<<jsonArray.count();
    for(int i=0;i<jsonArray.count();i++)
    {
        studyVector[i]=new StudyRoomPage(jsonArray[i].toObject(),this);
        studyVector[i]->setFixedSize(380,200);
        connect(studyVector[i],&StudyRoomPage::change,this,&StudyRoomShowWidget::Flesh);
        ui->verticalLayout->addWidget(studyVector[i],1);
    }
    ui->verticalLayout->addStretch(10);
}
