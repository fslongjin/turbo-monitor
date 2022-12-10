#ifndef CREATEVLOG_H
#define CREATEVLOG_H

#include <QObject>
#include <QWidget>
class QLabel;
class QPushButton;
class QGridLayout;
class QCalendarWidget;
class QLineEdit;
class CreateVlog : public QWidget
{
    Q_OBJECT
public:
    explicit CreateVlog(QWidget *parent = nullptr);

signals:
private slots:
    void ChangeName();
    void ChangeContext();
    void ChangeIcon();
    void ChangeCategory();
    void CreateLiveRoom();
    void UpdateLiveRoom();
    void ChangeAll();
private:
    QCalendarWidget *calendar;
    QWidget *adjust;
    QLabel *hourT,*secT,*minT;
    QLineEdit *hour,*sec,*min;

    QLabel *nameLabelLeft;
    QDate *readyDate;
    QTime *readyTime;
    QDateTime *readyDateTime;
    QLabel *contextLabelLeft;
    QLabel *iconLabelLeft;
    QLabel *categoryLabelLeft;
    QLabel *nameLabelright;
    QLabel *contextLabelright;
    QLabel *iconLabelright;
    QLabel *categoryLabelright;
    QPushButton *nameBtn;
    QPushButton *contextBtn;
    QPushButton *iconBtn;
    QPushButton *categoryBtn;
    QPushButton *createBtn;
    QGridLayout *mainLayout;
public slots:
    void CreateVlogShow();
};

#endif // CREATEVLOG_H
