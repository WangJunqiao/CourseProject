#ifndef USERINFO_H
#define USERINFO_H

#include<QString>
#include<QDataStream>
struct UserInfo{

    UserInfo();

    QByteArray toByteArray();
    void initWithByteArray(QByteArray *byteArray);

    QString toQString();
    void initWithQString(QString str);

    bool operator==(const UserInfo &b)const;

    friend QDataStream& operator<<(QDataStream &out,const UserInfo &obj);
    friend QDataStream& operator>>(QDataStream &in ,UserInfo &obj);

    //数据成员
    QString userID,password,qqNumber;
    int solved,rating;
};

#endif // USERINFO_H
