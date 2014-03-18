#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "msgstruct.h"
#include <QtGui>
#include "CentralWidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void statusBarShow(QString text,int msec);

public:
    CentralWidget *ui;
};

#endif // MAINWINDOW_H
