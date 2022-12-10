#include "mainwindow.h"
#include "logwidget.h"
#include <QDebug>
#include <QLayout>
#include <QJsonObject>
#include <QPushButton>
#include <QUrl>
#include <QJsonArray>
#include <QJsonValue>
#include <QUrlQuery>
#include <QEventLoop>
#include <QMessageBox>
bool MainWindow::onLine=0;
QString MainWindow::userId="1";
QString MainWindow::pushUrl="null";
QString MainWindow::token="null";
QString MainWindow::pullUrl="null";
QString MainWindow::userName="null";
QString MainWindow::roomId="null";
QString MainWindow::imageUrl="null";
QString MainWindow::key="null";
void MainWindow::init()
{
    manager=new QNetworkAccessManager(this);

    joinWidget = new QWidget();
    joinCentreLay = new QVBoxLayout(joinWidget);
    joinLabel = new QLabel ();
    mulJoinBtn = new QPushButton();
    joinLineEdit = new QLineEdit();
    joinCentreLay->addWidget(joinLabel);
    joinCentreLay->addWidget(joinLineEdit);
    joinCentreLay->addWidget(mulJoinBtn);
    joinLabel->setText("请输入房间号");
    mulJoinBtn->setText("确认加入");

    createStudyRoomDialog = new CreateStudyRoom();
    showStudyRoomBtn = new QPushButton();
    showStudyRoomBtn->setText("展示个人创建自习室");

    centreLay = new QVBoxLayout();
    mainFuncLay = new QHBoxLayout();
    bottomFuncLay = new QHBoxLayout();
    this->setFixedSize(800,800);
    QWidget *centreWid = new QWidget();
    this->setCentralWidget(centreWid);
    QVBoxLayout *centreLay = new QVBoxLayout (centreWid);
    QHBoxLayout *mainFuncLay = new QHBoxLayout ();
    centreLay->addStretch(1);
    centreLay->addLayout(mainFuncLay,1);
    centreLay->addStretch(8);
    mainFuncLay->setMargin(10);
    soloPlayButton = new QPushButton();
    mulPlayButton = new QPushButton();
    pointPlayButton = new QPushButton();
//    joinLiveBtn = new QPushButton();
//    joinLiveBtn->setText("加入直播");
    mainFuncLay->addStretch();
    soloPlayButton->setFixedSize(100,50);
    mulPlayButton->setFixedSize(100,50);
    soloPlayButton->setText("开始直播");
    mulPlayButton->setText("加入直播");
    pointPlayButton->setText("加入自习室");
    pointPlayButton->setFixedSize(100,50);
    mainFuncLay->addWidget(soloPlayButton);
    mainFuncLay->addWidget(mulPlayButton);
    mainFuncLay->addWidget(pointPlayButton);
    mainFuncLay->addStretch();
    mainFuncLay->setSpacing(50);
    createVlog= new QPushButton ();
    createVlog->setFixedSize(200,50);
    centreLay->addLayout(bottomFuncLay,2);
    bottomFuncLay->addStretch(5);
    createStudyRoomBtn = new QPushButton();
    showJoinedStudyRoomBtn = new QPushButton();
    showJoinedStudyRoomBtn->setText("展示个人加入自习室");
    showJoinedStudyRoomBtn->setFixedSize(200,50);
    createStudyRoomBtn->setFixedSize(200,50);
    showStudyRoomBtn->setFixedSize(200,50);
    bottomFuncLay->addWidget(createStudyRoomBtn);
    bottomFuncLay->addWidget(showJoinedStudyRoomBtn);
    bottomFuncLay->addWidget(showStudyRoomBtn);
    bottomFuncLay->addWidget(createVlog);
    createVlog->setText("创建直播间");
    createStudyRoomBtn->setText("创建自习室");
}
void MainWindow::Connect()
{
    connect(soloPlayButton,&QPushButton::clicked,this,&MainWindow::InitSoloWindow);
   // connect(soloPlayButton,SIGNAL(clicked()),solowindow,SLOT(SoloWindowShow()));
    connect(createVlog,&QPushButton::clicked,this,&MainWindow::InitCreateVlog);
    connect(mulPlayButton,&QPushButton::clicked,this,&MainWindow::InitJoinLive);
    connect(createStudyRoomBtn,&QPushButton::clicked,this,&MainWindow::InitCreateStudyRoom);
    connect(mulJoinBtn,&QPushButton::clicked,joinWidget,&QWidget::close);
    connect(mulJoinBtn,&QPushButton::clicked,this,&MainWindow::CreateJoinLive);
    connect(showStudyRoomBtn,&QPushButton::clicked,this,&MainWindow::GetAllUserStudyRoom);
    connect(showJoinedStudyRoomBtn,&QPushButton::clicked,this,&MainWindow::GetAllJoinedStudyRoom);
    connect(pointPlayButton,&QPushButton::clicked,this,&MainWindow::InitJoinStudyRoom);
  //  connect(createStudyRoomBtn,&QPushButton::clicked,this,&MainWindow::InitCreateStudyRoom);

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
    Connect();
}
MainWindow::~MainWindow()
{

}
void MainWindow::show_mainwindow()
{
    LogWidget::UpdateUserMessage();
    this->show();
}
void MainWindow::InitSoloWindow()
{

    LogWidget::CheckLogState();
    if(MainWindow::pushUrl=="null")
    {
        QMessageBox msgbox;
        msgbox.setIcon(QMessageBox::Information);
        msgbox.setText("请您先创建直播间");
        msgbox.setFixedSize(200,200);
        msgbox.exec();
        return ;
    }
    else
    {
        QMessageBox msgbox;
        msgbox.setIcon(QMessageBox::Information);
        msgbox.setTextInteractionFlags(Qt::TextSelectableByMouse);
        msgbox.setText("请使用obs向"+MainWindow::pushUrl+"推流 密匙为 "+key+" 房间号为 "+
                       MainWindow::userId+"准备结束后关闭此窗口");
        msgbox.setFixedSize(200,200);
        msgbox.exec();
    }
    liveRoom = new LiveRoom();
    liveRoom->show();

}
void MainWindow::InitCreateStudyRoom()
{
    LogWidget::CheckLogState();

    createStudyRoomDialog->show();
}
void MainWindow::InitJoinLive()
{
    LogWidget::CheckLogState();
    joinWidget->show();

}
void MainWindow::InitJoinStudyRoom()
{
      QWidget * temp = new QWidget();
      QVBoxLayout *vLayout = new QVBoxLayout(temp);
      labeltemp=new QLabel();
        lineEdit = new QLineEdit();
        QPushButton *pushBtn = new QPushButton();
        labeltemp->setText("输入自习室id");
        pushBtn->setText("确定加入");
        vLayout->addWidget(labeltemp);
        vLayout->addWidget(lineEdit);
        vLayout->addWidget(pushBtn);
        temp->show();
        connect (pushBtn,&QPushButton::clicked,this,&MainWindow::JoinStudyRoom);
        connect (pushBtn,&QPushButton::clicked,temp,&QWidget::close);

}
void MainWindow::JoinStudyRoom()
{
    QJsonObject jsonObject = getStudyRoomIdMessage(lineEdit->text());
   if(jsonObject["msg"]=="该自习室不存在")
   {
       QMessageBox msgbox;
       msgbox.setIcon(QMessageBox::Critical);
       msgbox.setText("自习室不存在 请重新输入ID");
       msgbox.setFixedSize(200,200);
       msgbox.exec();
       return ;

   }

   JoinStudyRoomFun(lineEdit->text());
   mainStudyRoom = new MainStudyRoom(lineEdit->text());
   mainStudyRoom->show();
}
void MainWindow::CreateJoinLive()
{
    QJsonObject jsonObject = LogWidget::GetPullUrl(joinLineEdit->text());
    watchLiveRoom = new LiveRoom(jsonObject["data"].toString(),nullptr);
    watchLiveRoom->show();
}
void MainWindow::InitCreateVlog()
{
    LogWidget::CheckLogState();
    createVlogWindow = new CreateVlog();
    createVlogWindow->show();

}
void MainWindow::GetAllUserStudyRoom()
{
    qDebug()<<"get study room";
    QUrl url("http://175.178.85.36:10010/studyRoom/getAllStudyRoomByUserId");
    QUrlQuery query;
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
    studyRoomShowWidget = new StudyRoomShowWidget(jsonArray);
    studyRoomShowWidget->show();
}
void MainWindow::GetAllJoinedStudyRoom()
{
    qDebug()<<"get study room";
    QUrl url("http://175.178.85.36:10010/studyRoom/getAllJoinedStudyRoomByUserId");
    QUrlQuery query;
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
    qDebug()<<jsonObject<<"joinedroom";
    QJsonValue jsonValue = jsonObject["data"];
    QJsonArray jsonArray = jsonObject["data"].toArray();
    studyRoomShowWidget = new StudyRoomShowWidget(jsonArray);
    studyRoomShowWidget->show();
}
QJsonObject MainWindow::getStudyRoomIdMessage(QString studyRoomIds)
{
    qDebug()<<"get study room message";
    QUrl url("http://175.178.85.36:10010/studyRoom/getStudyRoomMessage");
    QUrlQuery query;
    qDebug()<<studyRoomIds;
    query.addQueryItem("studyRoomId",studyRoomIds);
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
    qDebug()<<jsonObject;
    return jsonObject;
}

void MainWindow::JoinStudyRoomFun(QString studyRoomIds)
{
    qDebug()<<"JoinStudyRoomFun";
    QUrl url("http://175.178.85.36:10010/studyRoom/addStudyRoom");
    QUrlQuery query;
    url.setQuery(query);
    qDebug()<<url;
    request.setUrl(url);
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("authentication",MainWindow::token.toLatin1());

    QJsonObject param;
    param["userId"]=MainWindow::userId;
    param["userName"]=MainWindow::userName;
    param["studyRoomId"]= studyRoomIds;
    jsonManager.setObject(param);
    QByteArray byteArray = jsonManager.toJson();
    preplay=manager->post(request,byteArray);
    QEventLoop eventLoops;
    connect(preplay, &QNetworkReply::finished,&eventLoops ,&QEventLoop::quit);
    eventLoops.exec();
    QByteArray bytes;
    bytes = preplay->readAll();
    jsonObject = jsonManager.fromJson(bytes).object();
    qDebug()<<jsonObject;

}
