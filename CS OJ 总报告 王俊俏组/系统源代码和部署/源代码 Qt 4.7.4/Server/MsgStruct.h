#ifndef MSGSTRUCT_H
#define MSGSTRUCT_H

#include<QtCore>
#include<QDataStream>
#include<QByteArray>
#include"ConstData.h"
#include"UserInfo.h"

struct MsgStruct{
public:
    //数据成员
    int msgType;
    QString msg;
    int probID; //这个在提交代码时有用
    UserInfo user; //用于提取消息来源

    MsgStruct();

    QByteArray toByteArray();
    void initWithByteArray(QByteArray *byteArray);
    void initWithQIODevice(QIODevice *device);

    friend QDataStream& operator<<(QDataStream& out,const MsgStruct& obj);
    friend QDataStream& operator>>(QDataStream& in ,MsgStruct& obj);
};

#endif // MSGSTRUCT_H
