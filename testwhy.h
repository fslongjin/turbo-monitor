#ifndef TESTWHY_H
#define TESTWHY_H

#include <QWidget>

namespace Ui {
class Testwhy;
}

class Testwhy : public QWidget
{
    Q_OBJECT

public:
    explicit Testwhy(QWidget *parent = nullptr);
    ~Testwhy();

private:
    Ui::Testwhy *ui;
};

#endif // TESTWHY_H
