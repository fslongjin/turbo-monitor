#include "liveroom.h"
#include "mainwindow.h"
#include "ui_liveroom.h"
#include <QUrl>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDebug>
LiveRoom::LiveRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LiveRoom)
{
    ui->setupUi(this);
    player = new QMediaPlayer;
    videoWidget = new QVideoWidget();
    player->setVideoOutput(videoWidget);
    pullUrl=MainWindow::pullUrl;
    player->setMedia(QUrl(pullUrl));
    ui->gridLayout->addWidget(videoWidget);
    videoWidget->show();
    player->play();
}
LiveRoom::LiveRoom(QString tempPullUrl,QWidget *parent):QWidget(parent),ui(new Ui::LiveRoom)
{
    ui->setupUi(this);
    player = new QMediaPlayer;
    videoWidget = new QVideoWidget();
    player->setVideoOutput(videoWidget);
    pullUrl=tempPullUrl;
    player->setMedia(QUrl(pullUrl));
    ui->gridLayout->addWidget(videoWidget);
    videoWidget->show();
    player->play();
}
void LiveRoom::closeEvent(QCloseEvent *event)
{
    player->deleteLater();
    videoWidget->deleteLater();
}
LiveRoom::~LiveRoom()
{
    delete ui;
}

void LiveRoom::on_fleshBtn_clicked()
{
    player->setMedia(QUrl(pullUrl));
        player->play();
        qDebug()<<"here";
}

void LiveRoom::on_pauseBtn_clicked()
{

        if(player->state()== QMediaPlayer::PlayingState){
               player->pause();
           }else{
               player->play();
           }
}
