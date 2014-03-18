
#include "MsgStruct.h"
#include<QtCore>
#include "ConstData.h"

MsgStruct::MsgStruct(){
    this->msgType=MSG_TYPE_CHAT;
    this->msg="";
    this->probID=0;
    user=UserInfo();
}
QByteArray MsgStruct::toByteArray(){
    QByteArray ret;
    QDataStream out(&ret,QIODevice::WriteOnly);
    out<<msgType<<msg<<probID<<user; //***
    return ret;
}

void MsgStruct::initWithByteArray(QByteArray *byteArray){
    QDataStream in(byteArray,QIODevice::ReadOnly);
    in>>msgType>>msg>>probID>>user; //***
}

void MsgStruct::initWithQIODevice(QIODevice *device){
    QDataStream in(device);
    in>>msgType>>msg>>probID>>user; //***
}

QDataStream& operator<<(QDataStream& out,const MsgStruct& obj){
    return out<<obj.msgType<<obj.msg<<obj.probID<<obj.user;
}
QDataStream& operator>>(QDataStream& in ,MsgStruct& obj){
    return  in>>obj.msgType>>obj.msg>>obj.probID>>obj.user;
}
