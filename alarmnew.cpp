#include "alarmnew.h"
#include "ui_alarmnew.h"
#include <QDebug>
AlarmNew::AlarmNew(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmNew)
{
    ui->setupUi(this);
    ui->lineEdit->setText("45");
    fTimer=new QTimer(this);
    fTimer->stop();
    fTimer->setInterval (45000) ;//设置定时周期，单位：毫秒
    connect(fTimer,SIGNAL(timeout()),this,SLOT(TimeOut()));
}

AlarmNew::~AlarmNew()
{
    delete ui;
}

void AlarmNew::on_pushButton_clicked()
{
    qDebug()<<"here is clicked";
    fTimer->setInterval(ui->lineEdit->text().toDouble()*60000);
    if(ui->checkBox->isChecked()&&flag==0)
    {fTimer->start();flag=1;qDebug()<<"open";}
    if(!(ui->checkBox->isChecked()))
    {fTimer->stop();flag=0;qDebug()<<"Stop";}
}
void AlarmNew::TimeOut()
{
    QApplication::beep();
}
