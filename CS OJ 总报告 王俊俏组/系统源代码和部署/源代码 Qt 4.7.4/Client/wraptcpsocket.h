#ifndef WRAPTCPSOCKET_H
#define WRAPTCPSOCKET_H

#include "msgstruct.h"
#include <QTcpSocket>
//必须创建包装的Tcp类，不然多线程里面会访问出错
class WrapTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit WrapTcpSocket(QObject *parent = 0);

signals:
    void hadMsg(MsgStruct m);
public slots:
    void sendMsg(MsgStruct m);
private slots:
    void readMsg();
private:
    quint16 bufLen;
};

#endif // WRAPTCPSOCKET_H
