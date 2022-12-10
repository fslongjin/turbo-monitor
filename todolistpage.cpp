#include "todolistpage.h"
#include "ui_todolistpage.h"

ToDoListPage::ToDoListPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToDoListPage)
{
    ui->setupUi(this);
}

ToDoListPage::~ToDoListPage()
{
    delete ui;
}
