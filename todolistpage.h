#ifndef TODOLISTPAGE_H
#define TODOLISTPAGE_H

#include <QDialog>

namespace Ui {
class ToDoListPage;
}

class ToDoListPage : public QDialog
{
    Q_OBJECT

public:
    explicit ToDoListPage(QWidget *parent = nullptr);
    ~ToDoListPage();

private:
    Ui::ToDoListPage *ui;
};

#endif // TODOLISTPAGE_H
