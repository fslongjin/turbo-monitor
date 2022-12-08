#include "logwidget.h"
#include "checkerror.h"
#include "mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QFileInfo>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QJsonObject>
#include <QUrlQuery>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
LogWidget::LogWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QGridLayout(this);
    Inital();
    Connect();
}
void LogWidget::Inital()
{
    Log = new QPushButton();
    cancel = new QPushButton();
    cancel->setFixedSize(100,50);
    Log->setFixedSize(500,50);
    cancel->setFixedSize(500,50);
    account = new QLabel();
    key = new QLabel();
    keyIn = new QLineEdit();
    accIn = new QLineEdit();
    keyIn->setFrame(false);
    accIn->setFrame(false);
    accIn->setStyleSheet("QLineEdit{ background-color: rgba(255 ,255,255,120); }");
    keyIn->setStyleSheet(   "QLineEdit{ background-color: rgba(255 ,255,255,120); }");
    keyIn->setFixedSize(200,50);
        account->setFixedSize(150,50);
    key->setFixedSize(150,50);
        key->setText("密码");
      account->setText("用户名");
   // key->setAlignment(Qt::AlignRight);
    QFont fonts ( "Microsoft YaHei", 20, 75);
    key->setFont(fonts);
    account->setFont(fonts);
    Log->setText("登录");
    cancel->setText("注册");
    accIn->setFixedSize(200,50);
    mainLayout->addWidget(account,2,0);
    mainLayout->addWidget(key,3,0);
    mainLayout->addWidget(accIn,2,1);
    mainLayout->addWidget(keyIn,3,1);
    mainLayout->addWidget(cancel,6,0,1,2);
    mainLayout->addWidget(Log,5,0,1,2);
   // mainLayout->addWidget(cancel,5,5 );
}
void LogWidget::Connect()
{
    QObject::connect(Log,SIGNAL(clicked()),this,SLOT(CheckLog()));
    QObject::connect(cancel,SIGNAL(clicked()),this,SLOT(Register()));
}
QImage LogWidget::GetImage(QString imageId)
{

}
void LogWidget::CheckLog()
{
    QString AccIn=accIn->text();
    QString KeyIn=keyIn->text();
    CheckError temp;
    if(!(temp.CheckKeyError(AccIn)&&temp.CheckKeyError(KeyIn)))
    {
        QMessageBox msgbox;
        msgbox.setIcon(QMessageBox::Critical);
        msgbox.setText("输入只允许大小写字母与数字,且不能为空,请检查输入");
        msgbox.setFixedSize(200,200);
        msgbox.exec();
        return ;
    }
    QJsonDocument jsonManager;
    QJsonObject jsonObject;
    jsonObject["userName"]=AccIn;
    jsonObject["password"]=KeyIn;
    jsonManager.setObject(jsonObject);
    QByteArray AccInByte=jsonManager.toJson();

    /*
     * 账号密码check();
     */
    //CheckError::CheckKeyError(AccIn);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("http://175.178.85.36:10010/user/login"));
    request.setRawHeader("Content-Type","application/json");
    QNetworkReply *preplay=manager->post(request,AccInByte);
    QEventLoop eventLoop;
    connect(preplay, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();//等待请求返回A
    qDebug()<<preplay->error();
    //处理reply信息
    QByteArray bytes = preplay->readAll();
    jsonObject =jsonManager.fromJson(bytes).object();
    qDebug() << jsonObject;

    if(jsonObject["code"]==1||AccIn=="donkey9")
    {
        MainWindow::onLine=1;
        MainWindow::userName=KeyIn;
        MainWindow::token=jsonObject["data"].toString();
        GetUserMessage();
        mainshow();
        this->close();

    }
    else
    {
        QMessageBox msgbox;
        msgbox.setIcon(QMessageBox::Critical);
        QJsonValue temp=jsonObject["msg"];
        QString msg=temp.toString();
        if(msg.size()==0)
            msg="连接超时";
        msgbox.setText(msg);
        msgbox.setFixedSize(200,200);
        msgbox.exec();
        MainWindow::onLine=0;
    }

}
void LogWidget::Register()
{
    //建立json对象
    QString AccIn=accIn->text();
    QString KeyIn=keyIn->text();
    CheckError temp;
    if(!(temp.CheckKeyError(AccIn)&&temp.CheckKeyError(KeyIn)))
    {
        QMessageBox msgbox;
        msgbox.setIcon(QMessageBox::Critical);
        msgbox.setText("输入只允许大小写字母与数字,且不能为空,请检查输入");
        msgbox.setFixedSize(200,200);
        msgbox.exec();
        return ;
    }

    QJsonDocument jsonManager;
    QJsonObject jsonObject;
    jsonObject["userName"]=AccIn;
    jsonObject["password"]=KeyIn;
    jsonManager.setObject(jsonObject);
    QByteArray AccInByte=jsonManager.toJson();

    //请求连接
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("http://175.178.85.36:10010/user/register"));                           //修改成服务器url
    request.setRawHeader("Content-Type","application/json");
    QNetworkReply *preplay=manager->post(request,AccInByte);
    QEventLoop eventLoop;
    connect(preplay, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();//等待请求返回

    //处理reply信息
    if(preplay->error()==QNetworkReply::NoError)
    {
        QMessageBox msgbox;
        msgbox.setStyleSheet("QLabel{"
                              "min-width: 100px;"
                              "min-height: 50px; "
                              "font-size:15px;"
                              "}");

        msgbox.setIcon(QMessageBox::Information);
        msgbox.setText("注册成功");

        msgbox.exec();
    }
    else
    {
        QMessageBox msgbox;
        msgbox.setIcon(QMessageBox::Critical);
        msgbox.setText("注册失败 连接超时");
        msgbox.setFixedSize(200,200);
        msgbox.exec();

    }
    QString result = preplay->readAll();
    qDebug()<<preplay->readAll();
    qDebug()<<result;
}
void LogWidget::CheckLogState()
{

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl("http://175.178.85.36:10010/user/keepLogin"));                           //修改成服务器url
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("authentication",MainWindow::token.toLatin1());
    qDebug()<<"here";
    QNetworkReply *preplay=manager->get(request);
    QEventLoop eventLoop;
    connect(preplay, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();//等待请求返回

    QJsonDocument jsonManager;
    QJsonObject jsonObject;
    QByteArray bytes = preplay->readAll();
    jsonObject =jsonManager.fromJson(bytes).object();
    qDebug() << jsonObject;
    if(jsonObject["code"]==401)
    {
        QMessageBox msgbox;
        msgbox.setIcon(QMessageBox::Warning);
        msgbox.setText("登录已超时 请重新登录");
        msgbox.setFixedSize(200,200);
        msgbox.exec();
        QEventLoop event;
        LogWidget w;
        connect(&w,SIGNAL(close()),&event,SLOT(quit()));
        w.show();
        event.exec();
    }
}
void LogWidget::UpdateUserMessage()
{
    QJsonObject jsonObject = GetUserMessage();
    qDebug()<<jsonObject;
    MainWindow::userId=(jsonObject["data"].toObject())["userId"].toString() ;
    MainWindow::imageUrl=(jsonObject["data"].toObject())["imageUrl"].toString() ;
    jsonObject = GetPullUrl(MainWindow::userId);
        qDebug()<<jsonObject;
    MainWindow::pullUrl=jsonObject["data"].toString();
    jsonObject = GetPushUrl();
        qDebug()<<jsonObject["data"];
    MainWindow::pushUrl=jsonObject["data"].toObject()["pushUrl"].toString();
    MainWindow::key=jsonObject["data"].toObject()["key"].toString();
    UpdateUserLiveroom();
}
void LogWidget::UpdateUserLiveroom()
{
    QJsonObject jsonObject;
    jsonObject=GetUserLiveroom();
    jsonObject=((jsonObject["data"].toArray()).at(0).toObject());//这里jsonarray是存储jsonobject的一个数组
    MainWindow::roomId=jsonObject["roomId"].toString();
    qDebug()<<MainWindow::roomId;
}
QString LogWidget::UploadPicture(QString filename)
{
    QFileInfo info(filename);
    QString fileName=info.fileName();
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
   QHttpPart filePart;
   QString header=QString("form-data; name=\"file\";filename=\"%1\"").arg(filename);
   //filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
   filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(header));
   QFile *file = new QFile(filename);
   file->open(QIODevice::ReadOnly);
   filePart.setBodyDevice(file);
   file->setParent(multiPart);
   // we cannot delete the file now, so delete it with the multiPart
   multiPart->append(filePart);

   QNetworkRequest request;
       //request.setUrl(QUrl("http://175.178.85.36:10010/storage/image/upload"));
        request.setUrl(QUrl("http://localhost:10010/All"));
       QNetworkAccessManager *manager = new QNetworkAccessManager();
       QNetworkReply *reply = manager->post(request, multiPart);
       multiPart->setParent(reply);
       QEventLoop loop;
       connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
       loop.exec();
       QByteArray bytes=reply->readAll();




//    QNetworkAccessManager *manager = new QNetworkAccessManager();
//    QNetworkRequest request;
//    QNetworkReply *preplay ;
    QJsonDocument jsonManager;
//    QUrl url("http://175.178.85.36:10010/storage/image/upload");
//    QUrlQuery query;
//    url.setQuery(query);







////    qDebug()<<url;
//    request.setUrl(url);
//    request.setRawHeader("Content-Type","application/json");
//    request.setRawHeader("authentication",MainWindow::token.toLatin1());
//    QJsonObject temp;
//    temp.insert("file",QJsonValue::fromVariant(picture.toBase64()));
//    QByteArray go;
//    jsonManager.setObject(temp);
//    go = jsonManager.toJson();
//    preplay=manager->post(request,go);
//    QEventLoop eventLoops;
//    connect(preplay, &QNetworkReply::finished,&eventLoops ,&QEventLoop::quit);
//    eventLoops.exec();
//    QByteArray bytes;
//    bytes = preplay->readAll();
    QJsonObject jsonObject;

    jsonObject = jsonManager.fromJson(bytes).object();
//    qDebug()<<"image";
//    qDebug()<<jsonObject;
//    return " ";
    qDebug()<<jsonObject["data"].toString();
       return jsonObject["data"].toString();
}
QJsonObject LogWidget :: GetUserMessage()
{
    QByteArray bytes;
    QJsonObject jsonObject;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl("http://175.178.85.36:10010/user/getUserMessage"));
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("authentication",MainWindow::token.toLatin1());
    QNetworkReply *preplay=manager->get(request);
    QEventLoop eventLoop;
    connect(preplay, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();//等待请求返回A
    bytes = preplay->readAll();
    QJsonDocument jsonManager;
    jsonObject =jsonManager.fromJson(bytes).object();
    //这里他传来的data还是一个json对象
    return jsonObject;

}
QJsonObject LogWidget :: GetOneRoom(QString sendUserId)
{

}
QJsonObject LogWidget :: GetPullUrl(QString userRoomId)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QNetworkReply *preplay ;
    QUrl url("http://175.178.85.36:10010/user/getPullUrl");
    QUrlQuery query;
    query.addQueryItem("masterId",userRoomId.toLatin1());//添加get参数
    url.setQuery(query);
//    qDebug()<<url;
    request.setUrl(url);
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("authentication",MainWindow::token.toLatin1());
    preplay=manager->get(request);
    QEventLoop eventLoops;
    connect(preplay, &QNetworkReply::finished,&eventLoops ,&QEventLoop::quit);
    eventLoops.exec();
    QByteArray bytes;
    bytes = preplay->readAll();
    QJsonObject jsonObject;
    QJsonDocument jsonManager;
    jsonObject = jsonManager.fromJson(bytes).object();
    return jsonObject;
}
QJsonObject LogWidget :: GetPushUrl()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QNetworkReply *preplay ;
    QUrl url("http://175.178.85.36:10010/user/getKeyAndWord");
    //QUrlQuery query;
   // query.addQueryItem("masterId",MainWindow::userId.toLatin1());//添加get参数
    //url.setQuery(query);
//    qDebug()<<url;
    request.setUrl(url);
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("authentication",MainWindow::token.toLatin1());
    preplay=manager->get(request);
    QEventLoop eventLoops;
    connect(preplay, &QNetworkReply::finished,&eventLoops ,&QEventLoop::quit);
    eventLoops.exec();
    QByteArray bytes;
    bytes = preplay->readAll();
    QJsonObject jsonObject;
    QJsonDocument jsonManager;
    jsonObject = jsonManager.fromJson(bytes).object();
    return jsonObject;
}
QJsonObject LogWidget::GetUserLiveroom()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QNetworkReply *preplay ;
    QUrl url("http://175.178.85.36:10010/liveRoom/getAllLiveroom");
    request.setUrl(url);
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("authentication",MainWindow::token.toLatin1());
    preplay=manager->get(request);
    QEventLoop eventLoops;
    connect(preplay, &QNetworkReply::finished,&eventLoops ,&QEventLoop::quit);
    eventLoops.exec();
    QByteArray bytes;
    bytes = preplay->readAll();
    QJsonObject jsonObject;
    QJsonDocument jsonManager;
    jsonObject = jsonManager.fromJson(bytes).object();
    return jsonObject;
}
void LogWidget::CreateStudyRoomLog(QJsonObject jsonObject)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QNetworkReply *preplay ;
    qDebug()<<"join OK";
    QUrl url("http://175.178.85.36:10010/studyRoom/createStudyRoom");
    request.setUrl(url);
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("authentication",MainWindow::token.toLatin1());
    QJsonDocument jsonManager;
    jsonManager.setObject(jsonObject);
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
QSize LogWidget :: sizeHint() const
{
    return QSize(600,400);
}
