#include "createstudyroom.h"
#include "mainwindow.h"
#include "ui_createstudyroom.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QJsonObject>
#include "logwidget.h"
#include <QBuffer>
#include <QDebug>
#include <QFile>
CreateStudyRoom::CreateStudyRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateStudyRoom)
{
    ui->setupUi(this);
}

CreateStudyRoom::~CreateStudyRoom()
{
    delete ui;
}



void CreateStudyRoom::on_pushButton_clicked()
{
    filename=QFileDialog::getOpenFileName
            (this,tr("选择图片"),QDir::homePath(),tr("(*.jpg)(*.bmp)(*.png)"));
    if(filename=="")
        return ;
    qDebug()<<filename;
}

void CreateStudyRoom::on_pushButton_3_clicked()//缺结果展示
{
        QJsonObject jsonObject;
        QString imageString=LogWidget::UploadPicture(filename);
        qDebug()<<"picture OK";
        qDebug()<<imageString;
        jsonObject.insert("studyRoomName",ui->lineName->text());
        jsonObject.insert("studyRoomIntroduction",ui->lineContent->text());
        jsonObject.insert("userId",MainWindow::userId);
        jsonObject.insert("userName",MainWindow::userName);
        qDebug()<<"here";
        jsonObject.insert("studyRoomType",ui->btnSategory->text());
        qDebug()<<"here1";
        jsonObject.insert("studyRoomImageName",imageString);
        qDebug()<<"here2";
        jsonObject.insert("studyRoomPassword",ui->linePassword->text());
        qDebug()<<"noquestion";
        LogWidget::CreateStudyRoomLog(jsonObject);
    //    this->close();
}

void CreateStudyRoom::on_btnSategory_clicked()
{
    QStringList items; //ComboBox 列表的内容
    items <<"公共自习室"<<"团体自习室"<<"情侣自习室";
    QString dlgTitle="";
    QString txtLabel="请选择类型";
    int     curIndex=0; //初始选择项
    bool    editable=true; //ComboBox是否可编辑
    bool    ok=false;
    QString text = QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
    if (ok && !text.isEmpty())
        ui->btnSategory->setText(text);
}
