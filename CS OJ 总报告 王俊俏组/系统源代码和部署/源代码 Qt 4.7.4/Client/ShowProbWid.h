#ifndef SHOWPROBWID_H
#define SHOWPROBWID_H

#include <QWidget>
#include <QtGui>

class ShowProbWid : public QWidget
{
    Q_OBJECT
public:
    explicit ShowProbWid(QWidget *parent = 0);

signals:

public slots:

public:
    int probID;
    QLabel *label;
    QTextEdit *probTextEdit, *soluTextEdit;
    QPushButton *submitButton;
};

#endif // SHOWPROBWID_H
