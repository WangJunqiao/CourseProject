#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H


#include<QThread>
#include"wraptcpsocket.h"
#include<QHostAddress>
struct ClientThread : public QThread{
    Q_OBJECT
public:
    ClientThread(QObject *parent=0);
    ClientThread(QHostAddress addr,quint16 port,QObject *parent=0);

    void run();

    //这是一个传递信号的方法,相当于一个适配器
signals:
    void hadMsg(MsgStruct m);//对上层的借口
    //私有信号
    void toDownSend(MsgStruct m);

public slots:
    void sendMsg(MsgStruct m);//对上层的借口
private slots:
    void fromDownHad(MsgStruct m);

private:
    QHostAddress serverAddr;
    quint16 serverPort;
    WrapTcpSocket *wTcpSocket;
};

#endif // CLIENTTHREAD_H
