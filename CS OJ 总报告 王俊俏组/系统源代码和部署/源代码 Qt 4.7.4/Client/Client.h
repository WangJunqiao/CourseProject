#ifndef CLIENT_H
#define CLIENT_H
#include "mainwindow.h"
#include "LoginWindow.h"
#include "RegDialog.h"
#include "UserInfo.h"
#include <QList>
#include <QTcpSocket>
#include <QListWidgetItem>
#include "Problem.h"
#include "showprobwin.h"

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    ~Client();

    void sendMsg(MsgStruct msg);
    void processMsg(MsgStruct msg);
private:
    QAction *logOffAction;
    QMenu *mainMenu;

    void addToListWidget(UserInfo user);
    void initMainWindow();


public slots:
    void connectToHost();
    void loginToHost();
    void disconnect();

    void regNewAccount();
    void processReg();
    void readMsg();
    void chat();
    void showUserInfo(QListWidgetItem *item);
    void showProbDesc(QListWidgetItem *item);
    void submitCode(int probID,QString code);

    void logOff();

public:
    LoginWindow *loginWindow;
    MainWindow *mainWindow;
    RegDialog *regDialog;
    ShowProbWin *showProbWin;

    QTcpSocket *tcpSocket;
    quint16 bufLen;

    UserInfo curUserInfo;
    QList<UserInfo> onlineUsers;
    QList<UserInfo>::iterator uit;

    QList<Problem> probs;  //题目数据跟用户无关的,一连接就开始发送
    QList<Problem>::iterator pit;

    bool hadConnectToHost;
    bool hadLoginSuccess;
};

#endif // CLIENT_H
