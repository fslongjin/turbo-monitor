#include "messagebox.h"
# include <QMessageBox>
MessageBox::MessageBox()
{
    QMessageBox msgbox;
    msgbox.setIcon(QMessageBox::Critical);
    msgbox.setText("");
    msgbox.setFixedSize(200,200);
    msgbox.exec();
}
MessageBox::MessageBox(QString temp)
{
    QMessageBox msgbox;
    msgbox.setIcon(QMessageBox::Information);
    msgbox.setText(temp);
    msgbox.setFixedSize(200,200);
    msgbox.exec();
}
