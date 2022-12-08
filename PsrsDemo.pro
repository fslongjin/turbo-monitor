QT       += core gui
QT       += network
QT       += multimedia
QT       += multimediawidgets
QT       += multimedia multimediawidgets
QT       += widgets

QT       += websockets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += $$PWD/head
SOURCES += \
    alarm.cpp \
    alarmnew.cpp \
    batrun.cpp \
    checkerror.cpp \
    createstudyroom.cpp \
    createvlog.cpp \
    it.cpp \
    liveroom.cpp \
    logwidget.cpp \
    main.cpp \
    mainstudyroom.cpp \
    mainwindow.cpp \
    messagebox.cpp \
    show_all_studyroom/studyroompage.cpp \
    show_all_studyroom/studyroomshowwidget.cpp \
    soloplay.cpp \
    testwhy.cpp \
    tjust.cpp \
    todolistpage.cpp \
    watchliveroom.cpp \
    web_socket/websocket.cpp

HEADERS += \
    alarm.h \
    alarmnew.h \
    batrun.h \
    checkerror.h \
    createstudyroom.h \
    createvlog.h \
    it.h \
    liveroom.h \
    logwidget.h \
    mainstudyroom.h \
    mainwindow.h \
    messagebox.h \
    show_all_studyroom/studyroompage.h \
    show_all_studyroom/studyroomshowwidget.h \
    soloplay.h \
    testwhy.h \
    tjust.h \
    todolistpage.h \
    watchliveroom.h \
    web_socket/websocket.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    alarm.ui \
    alarmnew.ui \
    createstudyroom.ui \
    it.ui \
    liveroom.ui \
    mainstudyroom.ui \
    show_all_studyroom/studyroompage.ui \
    show_all_studyroom/studyroomshowwidget.ui \
    testwhy.ui \
    tjust.ui \
    todolistpage.ui
