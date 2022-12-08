#include "createvlog.h"
#include "logwidget.h"
#include "mainwindow.h"
#include "messagebox.h"
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QInputDialog>
#include <QDate>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QCalendarWidget>
#include <QEventLoop>
#include <QMessageBox>
#include <QLayout>
#include <QGridLayout>
CreateVlog::CreateVlog(QWidget *parent) : QWidget(parent)
{
    LogWidget::UpdateUserLiveroom();
    QJsonObject jsonObject= LogWidget::GetUserLiveroom();
    qDebug()<<"update here";
    jsonObject= jsonObject["data"].toArray().at(0).toObject();
    this->setFixedSize(800,500);
    setWindowTitle(tr("创建直播间")) ;
    nameLabelLeft =new QLabel;
    nameLabelLeft->setText(tr(" 直播间标题："));
    nameLabelright =new QLabel;
    QString temp=jsonObject["roomName"].toString();
    qDebug()<<temp;
    qDebug()<<"high";
    readyDate = new QDate();
    readyTime = new QTime();
    readyDateTime = new QDateTime();
    nameLabelright->setText(temp) ;
    nameLabelright->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    nameBtn =new QPushButton;
    nameBtn->setText(tr(" 修改直播间标题")) ;
    contextLabelLeft =new QLabel;
    contextLabelLeft->setText(tr(" 简介："));
    contextLabelright =new QLabel;
    temp=jsonObject["roomContent"].toString();
    contextLabelright->setText(temp) ;
    contextLabelright->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    contextBtn =new QPushButton;
    contextBtn->setText(tr(" 修改直播间简介"));
    iconLabelLeft =new QLabel;
    iconLabelLeft->setText(tr(" 日期："));
    iconLabelright =new QLabel;
    temp=jsonObject["startTime"].toString();
    qDebug()<<temp<<"time";
    iconLabelright->setText(temp);
    iconLabelright->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    iconBtn =new QPushButton;
    iconBtn->setText(tr(" 修改日期")) ;

    categoryLabelLeft =new QLabel;
    categoryLabelLeft->setText(tr(" 类别："));
    categoryLabelright =new QLabel;
    temp=jsonObject["roomType"].toString();
    categoryLabelright->setText(temp);
    categoryLabelright->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    categoryBtn =new QPushButton;
    categoryBtn->setText(tr("修改直播间类别")) ;
    createBtn = new QPushButton();
    createBtn->setText("确认");
    mainLayout =new QGridLayout(this);

    mainLayout->addWidget(nameLabelLeft,0,0,1,1);
    mainLayout->addWidget(nameLabelright,0,1,1,3);
    mainLayout->addWidget(nameBtn,0,4,1,1);
    mainLayout->addWidget(contextLabelLeft,1,0,1,1);
    mainLayout->addWidget(contextLabelright,1,1,1,3);
    mainLayout->addWidget(contextBtn,1,4,1,1);
    mainLayout->addWidget(iconLabelLeft,2,0,1,1);
    mainLayout->addWidget(iconLabelright,2,1,1,3);
    mainLayout->addWidget(iconBtn,2,4,1,1);
    mainLayout->addWidget(categoryLabelLeft,3,0,1,1);
    mainLayout->addWidget(categoryLabelright,3,1,1,3);
    mainLayout->addWidget(categoryBtn,3,4,1,1);
    mainLayout->addWidget(createBtn,4,3,1,2);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    connect (nameBtn, SIGNAL (clicked()), this, SLOT (ChangeName()));
    connect (contextBtn, SIGNAL (clicked()), this, SLOT (ChangeContext ()));
    connect (iconBtn, SIGNAL (clicked()), this, SLOT (ChangeIcon ()));
    connect(categoryBtn,SIGNAL(clicked()) ,this,SLOT(ChangeCategory()));
    connect(createBtn,SIGNAL(clicked()),this,SLOT(CreateLiveRoom()));
}
void CreateVlog::CreateVlogShow()
{
    this->show();
}
void CreateVlog::UpdateLiveRoom()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl("http://175.178.85.36:10010/liveRoom/updateRoom"));                           //修改成服务器url
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("authentication",MainWindow::token.toLatin1());
    QJsonDocument jsonManager;
    QJsonObject jsonObject;
    QByteArray byteArray;
    jsonObject["roomName"]=nameLabelright->text();
    jsonObject["roomContent"]=contextLabelright->text();
    jsonObject["roomType"]=categoryLabelright->text();
    jsonObject["roomImage"]="1";
    jsonObject["startTime"]=readyDate->toString()+" "+readyTime->toString();
    jsonObject["roomId"]=MainWindow::roomId;
    jsonManager.setObject(jsonObject);
    byteArray=jsonManager.toJson();
    QNetworkReply *preplay=manager->put(request,byteArray);
    QEventLoop eventLoop;
    connect(preplay, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();//等待请求返回
    QByteArray bytes = preplay->readAll();
    jsonObject =jsonManager.fromJson(bytes).object();
    MessageBox("更新成功");
}
void CreateVlog::CreateLiveRoom()
{
    if(MainWindow::roomId!="null")
    {
       UpdateLiveRoom();
       return ;
    }
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl("http://175.178.85.36:10010/liveRoom/createRoom"));                           //修改成服务器url
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("authentication",MainWindow::token.toLatin1());
    qDebug()<<"CreateLiveRoom";
    QJsonDocument jsonManager;
    QJsonObject jsonObject;
    QByteArray byteArray;
    jsonObject["roomName"]=nameLabelright->text();
    jsonObject["roomContent"]=contextLabelright->text();
    jsonObject["roomType"]=categoryLabelright->text();
    jsonObject["roomImage"]="";
    jsonObject["startTime"]=readyDate->toString();
    jsonManager.setObject(jsonObject);
    byteArray=jsonManager.toJson();
    QNetworkReply *preplay=manager->post(request,byteArray);
    QEventLoop eventLoop;
    connect(preplay, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();//等待请求返回
    QByteArray bytes = preplay->readAll();
    jsonObject =jsonManager.fromJson(bytes).object();
    qDebug() << jsonObject;
    MainWindow::roomId=jsonObject["roomId"].toString();
    MessageBox("创建成功");
}
void CreateVlog::ChangeIcon()
{
    adjust=new QWidget();
    QPushButton *confirm = new QPushButton(adjust);
    hourT=new QLabel(this);
    secT=new QLabel(this);
    minT=new QLabel(this);
    hour=new QLineEdit(this);
    min=new QLineEdit(this);
    sec=new QLineEdit(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(adjust);
    calendar = new QCalendarWidget(adjust); //创建一个日历指针用来使用
    //设置日历的文本格式
    calendar->setFont(QFont("Timers",8,QFont::Bold));
    //设置日历的大小
    calendar->resize(300,200);
    //日历移动
    mainLayout->addWidget(calendar);
   // mainLayout->addStretch(5);
    mainLayout->addWidget(hourT);
    mainLayout->addWidget(hour);
    mainLayout->addWidget(secT);
    mainLayout->addWidget(sec);
    mainLayout->addWidget(minT);
    mainLayout->addWidget(min);
    mainLayout->addWidget(confirm);
    //calendar->move(0,200);
    //日历隐藏，显示用show（）
    hourT->setText("请输入小时");
    secT->setText("请输入秒");
    minT->setText("请输入分钟");
    confirm->setText("确认");
    adjust->show();
    connect(confirm,SIGNAL(clicked()),this,SLOT(ChangeAll()));
    connect(this, SIGNAL(closeEvent()), adjust, SLOT(close()));
}
void CreateVlog::ChangeCategory()
{
    bool ok;
    QString text = QInputDialog::getText(this,"修改直播间类别","请输入直播间类别",
        QLineEdit::Normal,categoryLabelright->text(),&ok);
    if(ok && !text.isEmpty())
        categoryLabelright->setText(text);
}
void CreateVlog::ChangeName()
{
    bool ok;
    QString text = QInputDialog::getText(this,"修改直播间标题","请输入直播间标题",
        QLineEdit::Normal,nameLabelright->text(),&ok);
    if(ok && !text.isEmpty())
        nameLabelright->setText(text);
}
void CreateVlog::ChangeContext()
{
    bool ok;
    QString text = QInputDialog::getText(this,"修改直播间简介","请输入直播间简介",
        QLineEdit::Normal,contextLabelright->text(),&ok);
    if(ok && !text.isEmpty())
        contextLabelright->setText(text);
}
void CreateVlog::ChangeAll()
{
    QDate temp;
    temp = calendar->selectedDate();
    readyDateTime->setDate(temp);
    //if(hour->text().toInt()<0||>24)
    readyTime->setHMS(hour->text().toInt(),min->text().toInt(),sec->text().toInt());
    readyDateTime->setTime(*readyTime);
    iconLabelright->setText(readyDateTime->toString());
    delete adjust;
}
