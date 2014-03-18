#include <QtCore/QCoreApplication>
#include<QByteArray>
#include<UserInfo.h>
#include<iostream>
#include<QThread>
//#include<qnetwork.h>
//#include<QNetworkConfiguration>
#include<QDataStream>
#include<QDebug>
#include<QList>
#include<OJServer.h>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    OJServer ojserver;
    ojserver.startServer();

    return a.exec();
}
