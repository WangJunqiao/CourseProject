#include "ClientThread.h"
#include<QtCore>
#include<QtGui>
#include<QHostAddress>
#include"MsgStruct.h"
#include"wraptcpsocket.h"
ClientThread::ClientThread(QObject *parent)
    : QThread(parent)
{
}

ClientThread::ClientThread(QHostAddress addr, quint16 port,QObject *parent)
    : QThread(parent)
{
    this->serverAddr=addr;
    this->serverPort=port;

    qDebug()<<"ClientThread constructor: "<<QThread::currentThreadId()<<endl;
}
/*
查了查，原因应该是，在QThread中定义的所有东西都属于创建该QThread的线程。
所以在构造函数中初始化的mTcpClient应该是属于父线程的，那么在run中调用时就属于跨线程调用。
所以把mTcpClient放到run中初始化就属于线程的了，调用时就不会出现跨线程调用的问题。
  */
/*
 zjut_DD对线程中信号-槽机制的理解：
 首先，一个对象在那个线程中创建，那么它的资源（堆区的？）就是属于那个线程的，
 由于信号-槽是一个对象连接到另外一个对象的机制，那么当两个对象的资源属于不同对象时，Qt::AutoConnection 就是Qt::QueueConnection
 如果是在同一个线程中的，那么就是Qt::DirectConnection

 不过在两个线程中时，是可以强制DirectConnection的，这样就可以换个线程来执行了，

 理解这个是避免   跨线程调用资源（函数）   的关键
 */

void ClientThread::run(){
    qDebug()<<"clientThread run :"<<QThread::currentThreadId()<<endl;

    if( this->serverAddr.isNull() ){
        QMessageBox::about(NULL,tr("error occur!"),tr("no host ip address!"));
        return;
    }
    wTcpSocket=new WrapTcpSocket;

    connect(wTcpSocket,SIGNAL(hadMsg(MsgStruct)),this,SLOT(fromDownHad(MsgStruct)),Qt::QueuedConnection);
    connect(this,SIGNAL(toDownSend(MsgStruct)),wTcpSocket,SLOT(sendMsg(MsgStruct)),Qt::QueuedConnection);

    wTcpSocket->connectToHost(serverAddr,serverPort);
    qDebug()<<"connect to host success!\n";
    exec(); //进入事件循环
    qDebug()<<"got out of event loop!"<<endl;
}
void ClientThread::sendMsg(MsgStruct m){
    emit toDownSend(m);
}
void ClientThread::fromDownHad(MsgStruct m){
    emit hadMsg(m);
}
/*
void ClientThread::readContent(){
    qDebug()<<"clientThread readContent :"<<QThread::currentThreadId()<<endl;
    QDataStream in(tcpSocket);
    if( len==0 ){
        if( tcpSocket->bytesAvailable()>=sizeof(quint16)){
            in>>len;
        }else{
            return;
        }
    }
    if( tcpSocket->bytesAvailable()<len ){
        return;
    }
    QString msg;
    in>>msg;
    len=0;

    qDebug()<<msg<<"\n";

    tcpSocket->write("I love you!");
    qDebug()<<"had send I love you"<<endl;
}

void ClientThread::sendMessage(QString msg){
//    QByteArray cont;
//    QDataStream out(&cont,QIODevice::WriteOnly);
//    MsgStruct m;
//    m.msgType=MsgStruct::chat;
//    m.content=msg;
//    quint16 len=0;
//    out<<len<<m;
//    out.device()->seek(0);
//    out<<quint16(out.device()->bytesAvailable() - sizeof(quint16));

//    tcpSocket->write(cont);
//    tcpSocket->close();

    qDebug()<<"clientThread sendMessage: "<<QThread::currentThreadId()<<endl;

    qDebug()<<"ready to send a msg \n";
    QByteArray cont;
    QDataStream out(&cont,QIODevice::WriteOnly);

    out<<quint16(0)<<QString("I love you!");
    out.device()->seek(0);
    out<<quint16(cont.size() - sizeof(quint16));


    tcpSocket->write(cont);
    qDebug()<<"had send a msg \n";
    this->quit();
}
*/
