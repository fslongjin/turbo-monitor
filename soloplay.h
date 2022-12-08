#ifndef SOLOPLAY_H
#define SOLOPLAY_H

#include <QObject>
#include <QWidget>

class soloplay : public QWidget
{
    Q_OBJECT
public:
    explicit soloplay(QWidget *parent = nullptr);

signals:
public slots:
    void SoloWindowShow();
};

#endif // SOLOPLAY_H
