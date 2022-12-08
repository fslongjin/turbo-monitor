#include "tjust.h"
#include "ui_tjust.h"

Tjust::Tjust(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tjust)
{
    ui->setupUi(this);

}

Tjust::~Tjust()
{
    delete ui;
}
