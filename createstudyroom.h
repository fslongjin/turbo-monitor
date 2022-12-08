#ifndef CREATESTUDYROOM_H
#define CREATESTUDYROOM_H

#include <QDialog>

namespace Ui {
class CreateStudyRoom;
}

class CreateStudyRoom : public QDialog
{
    Q_OBJECT

public:
    explicit CreateStudyRoom(QWidget *parent = nullptr);
    ~CreateStudyRoom();

private slots:


    void on_pushButton_clicked();

    void on_pushButton_3_clicked();



    void on_btnSategory_clicked();
public:
    int state=0;
private:
    Ui::CreateStudyRoom *ui;
    QString studyRoomImageName;
    QString filename;
};

#endif // CREATESTUDYROOM_H
