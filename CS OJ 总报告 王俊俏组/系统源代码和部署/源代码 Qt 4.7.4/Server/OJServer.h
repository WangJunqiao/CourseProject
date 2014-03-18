#ifndef OJSERVER_H
#define OJSERVER_H

#include <QtNetwork>
#include <QtSql>
#include "MsgStruct.h"
#include "LinkedUser.h"
#include "Problem.h"
#include <QList>
#include "Judge.h"
class OJServer : public QObject{
    Q_OBJECT
public:
    OJServer(QObject *parent=NULL);
    ~OJServer();
    void startServer();
    void readAllProb();

    void insertUserInfoToDB(UserInfo user);

public slots:
    void addConnection();
    void processMsg(MsgStruct m);
    void disConnected();
private:
    int judgeRunID; //
    QString judge_home;
    QSqlDatabase db;
    Judge coreJudge;
    QSqlQuery query;
    QTcpServer tcpServer;
    QList<LinkedUser*> linkedUsers;
    QList<LinkedUser*>::iterator uit;
    QList<Problem> probs;
    QList<Problem>::iterator pit;
};

#endif // OJSERVER_H
