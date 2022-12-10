#ifndef TJUST_H
#define TJUST_H

#include <QDialog>

namespace Ui {
class Tjust;
}

class Tjust : public QDialog
{
    Q_OBJECT

public:
    explicit Tjust(QWidget *parent = nullptr);
    ~Tjust();

private:
    Ui::Tjust *ui;
};

#endif // TJUST_H
