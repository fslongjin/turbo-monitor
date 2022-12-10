#ifndef ALARMNEW_H
#define ALARMNEW_H

#include <QWidget>
#include <QTimer>
#include <QTime>
namespace Ui {
class AlarmNew;
}

class AlarmNew : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmNew(QWidget *parent = nullptr);
    ~AlarmNew();
    QTimer *fTimer; //定时器
    QTime fTimeCounter;//计时器
    int flag=0;
private slots:
    void on_pushButton_clicked();
    void TimeOut();


private:
    Ui::AlarmNew *ui;
};

#endif // ALARMNEW_H
