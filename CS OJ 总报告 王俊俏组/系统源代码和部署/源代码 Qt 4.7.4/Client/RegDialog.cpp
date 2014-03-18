#include "RegDialog.h"
#include "ui_RegDialog.h"
#include <QtGui>
#include "ConstData.h"
#include "UserInfo.h"

RegDialog::RegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("用户注册"));
}

RegDialog::~RegDialog()
{
    delete ui;
}

bool RegDialog::check(UserInfo *userInfo){
    QString userName=ui->userNameEdit->text();
    QString password=ui->passwordEdit->text();
    QString cPassword=ui->confPasswordEdit->text();
    QString qqNumber=ui->qqNumberEdit->text();
    if( userName.length()==0 ||
        password.length()==0 ||
        cPassword.length()==0 ||
        qqNumber.length()==0 ){
        QMessageBox::critical(0,tr("填写错误"),tr("请将信息填写完整!"));
        return false;
    }
    for(int i=0;i<userName.length();i++){
        if( userName[i]>='a' && userName[i]<='z' ) continue;
        if( userName[i]>='A' && userName[i]<='Z' ) continue;
        if( userName[i]>='0' && userName[i]<='9' ) continue;
        if( userName[i]=='_' ) continue;
        QMessageBox::critical(0,tr("填写错误"),tr("用户名只能包含字母,数字和下划线!"));
        return false;
    }

    if( userName.length() > MAX_USER_NAME_LEN ){
        QMessageBox::critical(0,tr("填写错误"),tr("用户名太长,不要超过15字节!"));
        return false;
    }

    if( password != cPassword ){
        QMessageBox::critical(0,tr("填写错误"),tr("前后两次密码输入不一致!"));
        return false;
    }

    if(password.length() > MAX_PASSWORD_LEN ){
        QMessageBox::critical(0,tr("填写错误"),tr("密码长度太长,不要超过15字节!"));
        return false;
    }

    for(int i=0;i<qqNumber.length();i++){
        if( qqNumber[i]>='0' && qqNumber[i]<='9' ) continue;
        QMessageBox::critical(0,tr("填写错误"),tr("请填写正确的qq号!"));
        return false;
    }

    if( qqNumber.length() < 5 ){
        QMessageBox::critical(0,tr("填写错误"),tr("请填写正确的qq号!"));
        return false;
    }
    userInfo->userID=userName;
    userInfo->password=password;
    userInfo->qqNumber=qqNumber;
    return true;
}
