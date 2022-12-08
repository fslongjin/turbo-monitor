#ifndef LOGWIDGET_H
#define LOGWIDGET_H
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QGridLayout>
class LogWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogWidget(QWidget *parent = nullptr);
    void Inital();
    void Connect();
    static void CheckLogState();
    static void UpdateUserMessage();
    static void UpdateUserLiveroom();
    static QImage GetImage(QString imageId);
    static QJsonObject GetUserMessage();
    static QJsonObject GetPushUrl();
    static QJsonObject GetPullUrl(QString userRoomId);
    static QJsonObject GetOneRoom(QString sendUserId);
    static QJsonObject GetUserLiveroom();
    static QString UploadPicture(QString picture);
    static void CreateStudyRoomLog(QJsonObject jsonObject);
public:
    QPushButton *Log,*cancel;//cancel=register
    QLabel *account,*key;
    QLineEdit *accIn,*keyIn;
    QGridLayout *mainLayout;
    virtual QSize sizeHint() const;
signals:
    void mainshow();
private slots:
     void CheckLog();
     void Register();
};

#endif // LOGWIDGET_H
