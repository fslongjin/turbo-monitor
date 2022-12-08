#include "it.h"
#include "ui_it.h"
#include <QMediaPlayer>
#include <QVideoWidget>
it::it(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::it)
{
    ui->setupUi(this);
    player = new QMediaPlayer;
        player3 = new QMediaPlayer;
            player4 = new QMediaPlayer;
    videoWidget = new QVideoWidget();
        videoWidget3 = new QVideoWidget();
            videoWidget4 = new QVideoWidget();
    player->setVideoOutput(videoWidget);
        player3->setVideoOutput(videoWidget3);
            player4->setVideoOutput(videoWidget4);


    videoWidget2 = new QVideoWidget();
    player2 = new QMediaPlayer;
    player2->setVideoOutput(videoWidget2);
  //  player->setMedia(QUrl::fromLocalFile("C:/Users/30985/Documents/Tencent Files/309858144/Video/37D1CDA79618D44B35D8DEF8D1387042.mp4"));
        player->setMedia(QUrl("http://1.12.230.201:8081/live/livestream.flv"));
        player2->setMedia(QUrl("http://43.138.211.210:8081/live1/livestream.flv"));
 // player2->setMedia(QUrl::fromLocalFile("C:/Users/30985/Documents/Tencent Files/309858144/Video/CDC5EC8BA072D247212441CC38638B24.mp4"));
    player3->setMedia(QUrl::fromLocalFile("C:/Users/30985/Documents/Tencent Files/309858144/Video/EB49CC09435391CF58EAC5E2699847CF.mp4"));
    player4->setMedia(QUrl::fromLocalFile("C:/Users/30985/Documents/Tencent Files/309858144/Video/CFDB83A75420BAD7B12850A90EFE651F.mp4"));
    ui->gridLayout->addWidget(videoWidget);
   ui->gridLayout_2->addWidget(videoWidget2);
      ui->gridLayout_5->addWidget(videoWidget3);
         ui->gridLayout_6->addWidget(videoWidget4);

    videoWidget->show();

    player3->play();
    player->play();
    player2->play();
    player4->play();
}

it::~it()
{
    delete ui;
}
