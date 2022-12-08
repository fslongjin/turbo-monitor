#ifndef LIVEROOM_H
#define LIVEROOM_H

#include <QWidget>
#include <QPushButton>
class QMediaPlayer;
class QVideoWidget;
namespace Ui {
class LiveRoom;
}

class LiveRoom : public QWidget
{
    Q_OBJECT

public:
    explicit LiveRoom(QWidget *parent = nullptr);
    explicit LiveRoom(QString tempPullUrl,QWidget *parent=nullptr);
    ~LiveRoom();


private slots:
    void on_fleshBtn_clicked();

    void on_pauseBtn_clicked();

private:
    Ui::LiveRoom *ui;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QPushButton *fleshBtn,*pauseBtn;
    QString pullUrl;
    void closeEvent(QCloseEvent *event);
};

#endif // LIVEROOM_H
