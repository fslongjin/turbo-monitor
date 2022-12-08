#ifndef IT_H
#define IT_H

#include <QMainWindow>
class QMediaPlayer;
class QVideoWidget;
namespace Ui {
class it;
}

class it : public QMainWindow
{
    Q_OBJECT

public:
    explicit it(QWidget *parent = nullptr);
    ~it();

private:
    Ui::it *ui;
    QMediaPlayer *player;
    QMediaPlayer *player2;
        QMediaPlayer *player3;
            QMediaPlayer *player4;
    QVideoWidget *videoWidget,*videoWidget2,*videoWidget3,*videoWidget4;
    QString pullUrl;
};

#endif // IT_H
