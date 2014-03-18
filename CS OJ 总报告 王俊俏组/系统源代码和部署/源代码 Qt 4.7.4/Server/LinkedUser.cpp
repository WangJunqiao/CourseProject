#include "LinkedUser.h"
#include <QDataStream>
#include <QIODevice>
#include "MsgStruct.h"

LinkedUser::LinkedUser(QObject *parent) :
    QObject(parent)
{
    loginSuc=false;

    tcpSocket=NULL;
    bufLen=0;
}

void LinkedUser::readMsg(){
    QDataStream in(tcpSocket);
    if( bufLen==0 ){
        if( tcpSocket->bytesAvailable()<sizeof(quint16))
            return;
        in>>bufLen;
    }
    if( tcpSocket->bytesAvailable()<bufLen )
        return;
    MsgStruct m;
    in>>m;
    bufLen=0;
    //qDebug()<<m.msg<<"\n";
    emit( hadMsg(m) );
    if( tcpSocket->bytesAvailable() ) readMsg();
}

void LinkedUser::sendMsg(MsgStruct m){
    QByteArray byteArray;
    QDataStream in(&byteArray,QIODevice::WriteOnly);
    in<<quint16( sizeof(m) ) << m;
    tcpSocket->write(byteArray);
}

LinkedUser::~LinkedUser(){
    delete tcpSocket;
}
