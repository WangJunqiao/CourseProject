#include "ShowProbWin.h"
#include <QtGui>
#include <QSplitter>
#include <QPushButton>
#include "MsgStruct.h"
ShowProbWin::ShowProbWin(QWidget *parent) :
    QWidget(parent)
{
    this->setFont(QFont("Courier New"));
    this->setWindowTitle(tr("Show Problem"));
    QSplitter *sp=new QSplitter(Qt::Vertical,this);

    label=new QLabel(tr("problem description"),this);
    probTextEdit=new QTextEdit(this);
    probTextEdit->setReadOnly(true);
    soluTextEdit=new QTextEdit(this);
    soluTextEdit->setText(tr("//You can edit your code here. If done click the submit button!"));
    submitButton=new QPushButton(tr("submit"),this);

    this->probTextEdit->setMinimumSize(50,20);
    this->soluTextEdit->setMinimumSize(50,20);

    this->setMinimumSize(600,400);


//    QHBoxLayout *hLayout=new QHBoxLayout(this);
//    hLayout->addStretch();
//    hLayout->addWidget(submitButton);
//    hLayout->addStretch();



    sp->addWidget(probTextEdit);
    sp->addWidget(soluTextEdit);

    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(sp);
    layout->addWidget(submitButton);

    this->setLayout(layout);

    connect(this->submitButton,SIGNAL(clicked()),this,SLOT(submitClicked()));

//    QVBoxLayout *pLayout=new QVBoxLayout(this);
//    pLayout->addWidget(probLabel);
//    pLayout->addWidget(probTextEdit);

//    QVBoxLayout *sLayout=new QVBoxLayout(this);
//    sLayout->addWidget(soluLabel);
//    sLayout->addWidget(soluTextEdit);


//    QHBoxLayout *probLayout=new QHBoxLayout(this);
//    probLayout->addStretch();// 增加一个弹簧
//    probLayout->addWidget(probLabel);
//    probLayout->addStretch();

//    QHBoxLayout *soluLayout=new QHBoxLayout(this);
//    soluLayout->addStretch();// 增加一个弹簧
//    soluLayout->addWidget(soluLabel);
//    soluLayout->addStretch();

//    QVBoxLayout *layout=new QVBoxLayout(this);
//    //layout->addLayout(probLayout);
//    layout->addWidget(probLabel);
//    layout->addWidget(probTextEdit);
//    //layout->addLayout(soluLayout);
//    layout->addWidget(soluLabel);
//    layout->addWidget(soluTextEdit);
//    layout->addWidget(submitButton);

//    this->setLayout(layout);
//    sp->addWidget(probLabel);
//    sp->addWidget(probTextEdit);
//    sp->addWidget(soluLabel);
//    sp->addWidget(soluTextEdit);
//    sp->addWidget(submitButton);

//    QHBoxLayout *layout=new QHBoxLayout(this);
//    layout->addWidget(sp);

//    this->setLayout(layout);
}

void ShowProbWin::submitClicked(){
    emit( submit(this->probID,this->soluTextEdit->toPlainText()));
}
