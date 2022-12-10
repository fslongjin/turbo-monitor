#ifndef ALARM_H
#define ALARM_H

#include <QWidget>
#include <QTime>
#include <QTimer>
namespace Ui {
class alarm;
}

class alarm : public QWidget
{
    Q_OBJECT

public:
    explicit alarm(QWidget *parent = nullptr);
    ~alarm();
    void on_timer_timeout () ; //定时溢出处理槽函数private:
    QTimer *fTimer; //定时器
    QTime fTimeCounter;//计时器
    int flag=0;
    Ui::alarm *ui;
    void on_pushButton_clicked();
};

#endif // ALARM_H
