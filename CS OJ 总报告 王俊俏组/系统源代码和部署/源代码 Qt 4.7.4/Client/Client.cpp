#include <QtGui>
#include <QtNetwork>
#include <QString>
#include "Client.h"
#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "ConstData.h"
#include "ui_RegDialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "showprobwin.h"
#include "ShowProbWid.h"

Client::Client(){
    loginWindow=new LoginWindow(0);
    connect(loginWindow->ui->connectButton,SIGNAL(clicked()),
            this,SLOT(connectToHost()));
    connect(loginWindow->ui->goButton,SIGNAL(clicked()),
            this,SLOT(loginToHost()));
    connect(loginWindow->ui->regButton,SIGNAL(clicked()),
            this,SLOT(regNewAccount()));
    loginWindow->setWindowTitle(tr("DD Arena   -login"));
    loginWindow->show();

    mainWindow=NULL;
    regDialog=NULL;
    showProbWin=NULL;

    //hostAddr=NULL;  //需要初始化,不然后面乱delete就要崩溃了

    tcpSocket=new QTcpSocket;
    bufLen=0;
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMsg()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnect()));

    hadConnectToHost=false;
    hadLoginSuccess=false;
}


void Client::connectToHost(){
    QHostAddress *hostAddr=new QHostAddress(loginWindow->ui->IPEdit->text());

    if( hostAddr->isNull() ){
        loginWindow->statusBar()->showMessage(tr("invalid IP address!"),2000);
        return;
    }
    tcpSocket->connectToHost(*hostAddr,HOSTPORT,QTcpSocket::ReadWrite);
    loginWindow->statusBarShow(tr("Trying to connect to host ").append(loginWindow->ui->IPEdit->text()),10000);
    delete hostAddr;
}

void Client::sendMsg(MsgStruct m){
    if( hadConnectToHost==false ){
        loginWindow->statusBarShow(tr("Please connect to server first(input server IP address,then click Connect!)"),5000);
        return;
    }
    QByteArray byteArray;
    QDataStream in(&byteArray,QIODevice::WriteOnly);
    in<<quint16( sizeof(m) ) << m;
    tcpSocket->write(byteArray);
    //qDebug()<<"had send confirm msg";
}

void Client::loginToHost(){
    if( hadConnectToHost==false ){
        loginWindow->statusBarShow(tr("Please connect to server first(input server IP address,then click Connect!)"),5000);
        return;
    }
    QString userName=loginWindow->ui->UserNEdit->text();
    QString password=loginWindow->ui->PwdEdit->text();
    if( userName.length()==0 || password.length()==0 ){
        QMessageBox::critical(0,tr("login failed"),tr("please input username and password completely!"));
        return;
    }
    curUserInfo.userID=userName;
    curUserInfo.password=password;
    curUserInfo.qqNumber="12345678"; //无用的值
    MsgStruct msg;
    msg.msgType=MSG_TYPE_LOGIN;
    msg.msg=curUserInfo.toQString();
    this->sendMsg(msg);
    loginWindow->statusBar()->showMessage(tr("login...)"),5000);
}

void Client::regNewAccount(){
    if( hadConnectToHost==false ){
        loginWindow->statusBarShow(tr("Please connect to server first(input server IP address,then click Connect!)"),5000);
        return;
    }
    if( regDialog ==0 ){
        regDialog=new RegDialog();
        connect(regDialog->ui->regButton,SIGNAL(clicked()),
            this,SLOT(processReg()));
    }
    regDialog->show();
}

void Client::processReg(){
    if( regDialog->check(&curUserInfo) == false ){
        return;
    }
    MsgStruct msg;
    msg.msgType=MSG_TYPE_REGISTER;
    msg.msg=curUserInfo.toQString();
    sendMsg(msg);
    loginWindow->statusBarShow(tr("send register message successfully"),5000);
}

void Client::readMsg(){
    QDataStream in(tcpSocket);
    if( bufLen==0 ){
        if( tcpSocket->bytesAvailable()<sizeof(quint16))
            return;
        in>>bufLen;
    }
    if( tcpSocket->bytesAvailable()<bufLen )
        return;
    MsgStruct m;
    in>>m;
    bufLen=0;
    processMsg(m);
    if( tcpSocket->bytesAvailable() ) readMsg();
    //qDebug()<<m.msg<<"\n";
}

void Client::addToListWidget(UserInfo user){
    QListWidgetItem *item=new QListWidgetItem(user.userID);
    QColor c;
    if( user.rating<=400 ){
        c=QColor(Qt::darkGray);
    }else if( user.rating<=800 ){
        c=QColor(Qt::gray);
    }else if( user.rating<=1200 ){
        c=QColor(Qt::green);
    }else if( user.rating<=1500 ){
        c=QColor(Qt::cyan);
    }else if( user.rating<=1800 ){
        c=QColor(Qt::magenta);
    }else if( user.rating<=2200 ){
        c=QColor(Qt::darkRed);
    }else{
        c=QColor(Qt::red);
    }
    item->setForeground(QBrush(c));
    mainWindow->ui->listWidget->addItem(item);
}

void Client::initMainWindow(){
    mainWindow=new MainWindow(0);
    mainWindow->setMinimumSize(600,500);

    mainWindow->ui->textEdit->setReadOnly(true);
    mainWindow->ui->lineEdit->setFocus();
    mainWindow->setWindowTitle(tr("OnlineArena for ZJUTACM Team -Developed by zjut_DD"));
    connect(mainWindow->ui->sendButton,SIGNAL(clicked()),
            this,SLOT(chat()));
    connect(mainWindow->ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this,SLOT(showUserInfo(QListWidgetItem*)));

    for(pit=probs.begin();pit!=probs.end();++pit){
        Problem p=*pit;
        QListWidgetItem *item=new QListWidgetItem(p.print());
        mainWindow->ui->listWidget2->addItem(item);
    }
    connect(mainWindow->ui->listWidget2,SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this,SLOT(showProbDesc(QListWidgetItem*)));

    logOffAction=new QAction(tr("logout"),0);
    connect(logOffAction,SIGNAL(triggered()),this,SLOT(logOff()));

    mainMenu=new QMenu(tr("Main Menu"),0);

    mainMenu->addAction(logOffAction);
    mainWindow->menuBar()->addMenu(mainMenu);
}



void Client::processMsg(MsgStruct msg){
    if( msg.msgType == MSG_TYPE_CONFIRM ){
        loginWindow->statusBar()->showMessage(tr("Connect to Server successfully!")
                                              .append(loginWindow->ui->IPEdit->text()),10000);
        hadConnectToHost=true;
    }else if( msg.msgType == MSG_TYPE_REGISTER_SUC ){
        QMessageBox::information(0,tr("Register Infomation"),tr("Register Successfully!"));
        delete regDialog;
        regDialog=NULL;
    }else if( msg.msgType == MSG_TYPE_REGISTER_FAIL ){
        QMessageBox::critical(0,tr("Register Failed"),tr("This username has already exist!"));
    }else if( msg.msgType == MSG_TYPE_LOGIN_SUC ){
        curUserInfo.initWithQString(msg.msg);
        hadLoginSuccess=true;
        initMainWindow(); //初始化主窗口组件
        loginWindow->hide();
        mainWindow->showNormal();
    }else if( msg.msgType == MSG_TYPE_LOGIN_FAIL ){
        QMessageBox::critical(0,tr("login failed"),tr("Wrong Username and Password Combination!"));
    }else if( msg.msgType == MSG_TYPE_USERLOGIN ){
        onlineUsers.push_back(msg.user);
        this->addToListWidget(msg.user);
    }else if( msg.msgType == MSG_TYPE_CHAT ){
        mainWindow->ui->textEdit->append(msg.user.userID.append(": ").append(msg.msg));
    }else if( msg.msgType == MSG_TYPE_USERLOGOFF ){
        if( this->hadLoginSuccess == false ) return;

        for(QList<UserInfo>::iterator it=onlineUsers.begin();it!=onlineUsers.end();++it){
            if( (*it) == msg.user ){
                onlineUsers.erase(it);
                break;
            }
        }
        //QListWidget里要删除一个item,必须使用take,然后要手动delete
        QListWidgetItem *item=(mainWindow->ui->listWidget->findItems(msg.user.userID,Qt::MatchCaseSensitive)).at(0);
        int row=mainWindow->ui->listWidget->row(item);
        mainWindow->ui->listWidget->takeItem(row);
        delete item;
    }else if( msg.msgType == MSG_TYPE_GET_PROB ){ //题目数据发送过来了
        Problem p;
        p.initWithString(msg.msg);
        probs.push_back(p);
        //QListWidgetItem *item=new QListWidgetItem(p.print());
        //mainWindow->ui->listWidget2->addItem(item);
        qDebug()<<p.toString();
    }else if( msg.msgType == MSG_TYPE_PROB_DES ){
        delete showProbWin;
        showProbWin=new ShowProbWin();
        showProbWin->probID=msg.probID;
        showProbWin->probTextEdit->setText(msg.msg);
        connect(showProbWin,SIGNAL(submit(int,QString)),this,SLOT(submitCode(int,QString)));
        showProbWin->show();
    }else if( msg.msgType == MSG_TYPE_SHOWMSG ){
        QMessageBox::information(0,tr("information"),msg.msg);
    }
}

void Client::submitCode(int probID, QString code){
    MsgStruct m;
    m.msgType=MSG_TYPE_CODE;
    m.user=this->curUserInfo;
    m.probID=probID;
    m.msg=code;
    this->sendMsg(m);
}

void Client::showProbDesc(QListWidgetItem *item){
    MsgStruct m;
    m.msgType=MSG_TYPE_PROB_DES;
    m.probID=item->text().left(4).toInt();
    this->sendMsg(m);
}

void Client::chat(){
    MsgStruct msg;
    msg.msgType=MSG_TYPE_CHAT;
    msg.msg=mainWindow->ui->lineEdit->text();
    mainWindow->ui->lineEdit->setText("");
    mainWindow->ui->lineEdit->setFocus();
    this->sendMsg(msg);
}

void Client::logOff(){
    delete mainWindow;
    mainWindow=NULL;  // 避免重复delete
    delete showProbWin;
    showProbWin=NULL;

    this->onlineUsers.clear();
    this->hadLoginSuccess=false; //
    //probs.clear();
    loginWindow->show();

    if( tcpSocket->state() ==QTcpSocket::ConnectedState ){ //如果是自己按了注销的话,要告诉服务器
        MsgStruct m;
        m.msgType=MSG_TYPE_USERLOGOFF;
        this->sendMsg(m);
    }

}

void Client::disconnect(){
    qDebug()<<"disConnected with server!";
    if( QMessageBox::warning(0,tr("Logout Prompt"),tr("You are logged off!")) == QMessageBox::Ok ){

    }
    this->logOff();
}

void Client::showUserInfo(QListWidgetItem *item){
    UserInfo user;
    for(QList<UserInfo>::iterator it=onlineUsers.begin();it!=onlineUsers.end();++it){
        if( (*it).userID == item->text() ){
            user=(*it);
            break;
        }
    }
    QString m=tr("UserName: ").append(user.userID)
              .append("\nqq Number: ").append(user.qqNumber)
              .append("\nSolved: ").append(QString::number(user.solved))
              .append("\nRating: ").append(QString::number(user.rating));
    QMessageBox::information(0,tr("User Infomation"),m);
}

Client::~Client(){
    qDebug()<<"~Client called! "<<endl;
    delete loginWindow;
    delete mainWindow;
    delete regDialog;
    delete showProbWin;
    //~QObject();
}
