#include "testwhy.h"
#include "ui_testwhy.h"

Testwhy::Testwhy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Testwhy)
{
    ui->setupUi(this);
}

Testwhy::~Testwhy()
{
    delete ui;
}
