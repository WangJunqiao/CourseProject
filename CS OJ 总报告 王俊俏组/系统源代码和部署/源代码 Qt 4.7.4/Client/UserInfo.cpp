
#include "UserInfo.h"
#include <QtCore>

UserInfo::UserInfo(){
    userID=password=qqNumber="";
    solved=rating=0;
}

QByteArray UserInfo::toByteArray(){
    QByteArray ret;
    QDataStream out(&ret,QIODevice::WriteOnly);
    out<<userID<<password<<qqNumber<<solved<<rating;
    return ret;
}

void UserInfo::initWithByteArray(QByteArray *byteArray){
    QDataStream in(byteArray,QIODevice::ReadOnly);
    in>>userID>>password>>qqNumber>>solved>>rating;
}

bool UserInfo::operator ==(const UserInfo &b)const{
    return userID == b.userID;
}

QString UserInfo::toQString(){
    return userID+"$"+password+"$"+qqNumber+"$"+QString::number(solved)+"$"+QString::number(rating);
}
void UserInfo::initWithQString(QString str){ //5个属性都不能为空串！！
    QStringList L=str.split(QChar('$'));
    userID=L[0];
    password=L[1];
    qqNumber=L[2];
    solved=L[3].toInt();
    rating=L[4].toInt();
}


QDataStream& operator<<(QDataStream &out,const UserInfo &obj){
    return out<<obj.userID<<obj.password<<obj.qqNumber<<obj.solved<<obj.rating;
}

QDataStream& operator>>(QDataStream &in ,UserInfo &obj){
    return in>>obj.userID>>obj.password>>obj.qqNumber>>obj.solved>>obj.rating;
}
