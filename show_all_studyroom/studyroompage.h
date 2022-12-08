#ifndef STUDYROOMPAGE_H
#define STUDYROOMPAGE_H

#include <QWidget>
namespace Ui {
class StudyRoomPage;
}

class StudyRoomPage : public QWidget
{
    Q_OBJECT

public:
    explicit StudyRoomPage(QJsonObject jsonObject ,QWidget *parent = nullptr);
    ~StudyRoomPage();
    QString studyRoomId;
    QString studyRoomImageName;
    QString studyRoomIntroduction;
    QString studyRoomMemberNumber;
    QString studyRoomName;
    QString studyRoomPassword;
    QString studyRoomType;
private:
    Ui::StudyRoomPage *ui;
private slots:
    void DeleteStudyRoom();
signals:
    void change();
};

#endif // STUDYROOMPAGE_H
