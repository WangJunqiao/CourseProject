#include "LoginWindow.h"
#include "ui_LoginWindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->IPEdit->setText(QString("127.0.0.1"));
    this->setWindowIcon(QIcon("X.ico"));
}

void LoginWindow::statusBarShow(QString text, int msec){
    this->statusBar()->showMessage(text,msec);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
