#include "alarm.h"
#include "ui_alarm.h"
#include <QTimer>
#include <QDebug>
alarm::alarm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alarm)
{
    ui->setupUi(this);
    ui->lineEdit->setText("45");
    fTimer=new QTimer(this);
    fTimer->stop();
    fTimer->setInterval (45000) ;//设置定时周期，单位：毫秒
    connect(fTimer,SIGNAL(timeout()),this,SLOT(on_timer_timeout()));
}

alarm::~alarm()
{
    delete ui;
}



void alarm::on_pushButton_clicked()
{
    qDebug()<<"here is clicked";
    fTimer->setInterval(ui->lineEdit->text().toInt()*60000);
    if(ui->checkBox->isChecked()&&flag==0)
    {fTimer->start();flag=1;qDebug()<<"open";}
    if(!(ui->checkBox->isChecked()))
    {fTimer->stop();flag=0;}
}
void alarm::on_timer_timeout()
{
   QApplication::beep();
}
