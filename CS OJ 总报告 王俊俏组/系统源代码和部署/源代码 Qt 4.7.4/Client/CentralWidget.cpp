#include "CentralWidget.h"

CentralWidget::CentralWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(400,300);

    onlineCoders=new QLabel(tr("Online Coders"),this);
    chatArea=new QLabel(tr("Chat Area"),this);
    problemSet=new QLabel(tr("Problem Set"),this);

    onlineCoders->setFont(QFont("Elephant",12)); //字体里面包含大小的
    chatArea->setFont(QFont("Elephant",12));
    problemSet->setFont(QFont("Elephant",12));

    QPalette pal=onlineCoders->palette(); //取得调色板,设置颜色
    pal.setColor(QPalette::Text,QColor(Qt::blue));
    onlineCoders->setPalette(pal);
    onlineCoders->setForegroundRole(QPalette::Text);
    chatArea->setPalette(pal);
    chatArea->setForegroundRole(QPalette::Text);
    problemSet->setPalette(pal);
    problemSet->setForegroundRole(QPalette::Text);

    this->listWidget  =new QListWidget(this);
    this->listWidget2 =new QListWidget(this);
    this->textEdit    =new QTextEdit(this);
    this->lineEdit    =new QLineEdit(this);
    this->sendButton  =new QPushButton(tr("send"),this);

    this->listWidget->setWrapping(true);
    this->listWidget2->setWrapping(true);

    this->textEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->lineEdit->setMinimumWidth(200);
    this->listWidget2->setMaximumWidth(400);
    this->textEdit->setReadOnly(true);
    this->listWidget->setMaximumWidth(150);

    QHBoxLayout *inputL=new QHBoxLayout;
    inputL->addStretch();
    inputL->addWidget(lineEdit);
    inputL->addWidget(sendButton);
    inputL->addStretch();

    QVBoxLayout *leftV=new QVBoxLayout;
    leftV->addWidget(this->onlineCoders);
    leftV->addWidget(this->listWidget);


    QVBoxLayout *midV=new QVBoxLayout;
    midV->addWidget(this->chatArea);
    midV->addWidget(textEdit);
    midV->addLayout(inputL);

    QVBoxLayout *rightV=new QVBoxLayout;
    rightV->addWidget(this->problemSet);
    rightV->addWidget(this->listWidget2);

    QHBoxLayout *layout=new QHBoxLayout;
    layout->addLayout(leftV);
    layout->addLayout(midV);
    layout->addLayout(rightV);

    this->setLayout(layout);
}
