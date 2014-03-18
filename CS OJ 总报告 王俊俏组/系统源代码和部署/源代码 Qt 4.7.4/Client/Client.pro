#-------------------------------------------------
#
# Project created by QtCreator 2011-12-16T13:50:59
#
#-------------------------------------------------

QT       += core gui network

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    wraptcpsocket.cpp \
    UserInfo.cpp \
    showprobwin.cpp \
    ShowProbWid.cpp \
    RegDialog.cpp \
    Problem.cpp \
    MsgStruct.cpp \
    LoginWindow.cpp \
    ClientThread.cpp \
    Client.cpp \
    CentralWidget.cpp

HEADERS  += mainwindow.h \
    wraptcpsocket.h \
    UserInfo.h \
    showprobwin.h \
    ShowProbWid.h \
    RegDialog.h \
    Problem.h \
    MsgStruct.h \
    LoginWindow.h \
    ConstData.h \
    ClientThread.h \
    Client.h \
    CentralWidget.h

FORMS    += mainwindow.ui \
    RegDialog.ui \
    loginwindow.ui


OTHER_FILES += \
    X.ico
