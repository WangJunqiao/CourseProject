#ifndef SHOWPROBWIN_H
#define SHOWPROBWIN_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>

class ShowProbWin : public QWidget
{
    Q_OBJECT
public:
    explicit ShowProbWin(QWidget *parent = 0);

signals:
    void submit(int probID,QString code);
public slots:
    void submitClicked();
public:
    int probID;
    QLabel *label;
    QTextEdit *probTextEdit, *soluTextEdit;
    QPushButton *submitButton;
};

#endif // SHOWPROBWIN_H
