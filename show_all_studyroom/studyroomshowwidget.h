#ifndef STUDYROOMSHOWWIDGET_H
#define STUDYROOMSHOWWIDGET_H

#include <QWidget>
#include "studyroompage.h"
namespace Ui {
class StudyRoomShowWidget;
}

class StudyRoomShowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudyRoomShowWidget(QJsonArray jsonArray , QWidget *parent = nullptr);
    ~StudyRoomShowWidget();
    QVector<StudyRoomPage*>studyVector;
    StudyRoomPage *testt;
private:
    Ui::StudyRoomShowWidget *ui;
private slots:
    void Flesh();
};

#endif // STUDYROOMSHOWWIDGET_H
