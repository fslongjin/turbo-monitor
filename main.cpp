#include "mainwindow.h"
#include "logwidget.h"
#include "liveroom.h"
#include "mainstudyroom.h"
#include "createstudyroom.h"
#include "show_all_studyroom/studyroomshowwidget.h"
#include "show_all_studyroom/studyroompage.h"
#include "it.h"
#include <QApplication>
// 直播间日期没写输入检测 日期格式不对
// delete等待更新
//roomImage没有修改 于createvlog
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogWidget log;
//    MainStudyRoom test;
//    test.show();
//
  //  StudyRoomPage test1;
   // test1.show();
   // StudyRoomShowWidget test2;
  //  test2.show();
    log.show();
    MainWindow *w;
    w=new MainWindow();
    QObject::connect(&log,SIGNAL(mainshow()),w,SLOT(show_mainwindow()));
    return a.exec();
}
