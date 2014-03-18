#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QtCore>
#include "Client.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<MsgStruct>("MsgStruct"); //注册元类型,由于MsgStruct不是元类型，信号和槽连接（queue的）时无法暂存！

    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    //QApplication::setFont(QFont("courier new")); //设置全局字体

    //qDebug()<<"main Thread: "<<QThread::currentThreadId()<<endl;

    Client c;

    return a.exec();
}
