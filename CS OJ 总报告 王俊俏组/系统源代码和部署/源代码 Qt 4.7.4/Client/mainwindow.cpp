#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "msgstruct.h"
#include "showprobwin.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui=new CentralWidget(this);
    this->setCentralWidget(ui);
    this->setWindowIcon(QIcon("X.ico"));
}


void MainWindow::statusBarShow(QString text, int msec){
    this->statusBar()->showMessage(text,msec);
}

MainWindow::~MainWindow()
{
    delete ui;
}
