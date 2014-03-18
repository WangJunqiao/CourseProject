#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QtGui>

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0);

signals:

public slots:
public:

    QListWidget *listWidget,*listWidget2; //user   prob
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QPushButton *sendButton;
    QLabel *onlineCoders,*chatArea, *problemSet;
};

#endif // CENTRALWIDGET_H
