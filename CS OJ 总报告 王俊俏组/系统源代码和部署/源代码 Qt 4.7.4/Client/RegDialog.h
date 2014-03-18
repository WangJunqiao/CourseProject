#ifndef REGDIALOG_H
#define REGDIALOG_H

#include <QDialog>
#include "UserInfo.h"

namespace Ui {
    class RegDialog;
}

class RegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegDialog(QWidget *parent = 0);
    ~RegDialog();

    bool check(UserInfo *userInfo);

public:
    Ui::RegDialog *ui;
};

#endif // REGDIALOG_H
