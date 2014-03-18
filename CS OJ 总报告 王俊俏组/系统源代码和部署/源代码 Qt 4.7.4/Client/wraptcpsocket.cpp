
#include "WrapTcpSocket.h"
#include <QtCore>
#include "msgstruct.h"
WrapTcpSocket::WrapTcpSocket(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(readMsg()));
    bufLen=0; //
}

void WrapTcpSocket::readMsg(){
    qDebug()<<"WrapTcpSocket::readMsg "<<QThread::currentThreadId();
    QDataStream in(this);
    if( bufLen==0 ){
        if( this->bytesAvailable() < sizeof(quint16) )
            return;
        in>>bufLen;
    }
    if( this->bytesAvailable()<bufLen )
        return;
    MsgStruct m;
    in>>m;
    bufLen=0; //重新归零
    emit hadMsg(m); //发射信号
}
void WrapTcpSocket::sendMsg(MsgStruct m){
    qDebug()<<"WrapTcpSocket::sendMsg "<<QThread::currentThreadId();
    QByteArray byteArray;
    QDataStream in(&byteArray,QIODevice::WriteOnly);
    in<<quint16(sizeof(m))<<m;
    this->write(byteArray);
}
