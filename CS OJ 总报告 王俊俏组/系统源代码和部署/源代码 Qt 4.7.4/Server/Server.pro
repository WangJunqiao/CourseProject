#-------------------------------------------------
#
# Project created by QtCreator 2011-12-15T19:04:46
#
#-------------------------------------------------

QT       += core \
            network \
            sql

QT       -= gui

TARGET = Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    UserInfo.cpp \
    Problem.cpp \
    OJServer.cpp \
    MsgStruct.cpp \
    LinkedUser.cpp \
    Judge.cpp

HEADERS += \
    UserInfo.h \
    Problem.h \
    OJServer.h \
    MsgStruct.h \
    LinkedUser.h \
    Judge.h \
    ConstData.h
