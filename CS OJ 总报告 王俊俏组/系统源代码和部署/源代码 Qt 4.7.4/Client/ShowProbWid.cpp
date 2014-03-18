#include "ShowProbWid.h"

ShowProbWid::ShowProbWid(QWidget *parent) :
    QWidget(parent)
{
    this->setFont(QFont("Courier New"));
    this->setWindowTitle(tr("Show Problem"));



    label=new QLabel(tr("problem description"),this);
    probTextEdit=new QTextEdit(this);
    probTextEdit->setReadOnly(true);
    soluTextEdit=new QTextEdit(this);
    soluTextEdit->setText(tr("//You can edit your code here. Then click the 'submit' button to submit your code!"));
    submitButton=new QPushButton(tr("submit"),this);

//    QHBoxLayout *hLayout=new QHBoxLayout(this);
//    hLayout->addStretch();
//    hLayout->addWidget(submitButton);
//    hLayout->addStretch();

    //this->probTextEdit->setMinimumSize(50,20);
    //this->soluTextEdit->setMinimumSize(50,20);

    this->setMinimumSize(600,400);


//    QHBoxLayout *hLayout=new QHBoxLayout(this);
//    hLayout->addStretch();
//    hLayout->addWidget(submitButton);
//    hLayout->addStretch();


    QSplitter *sp=new QSplitter(Qt::Vertical,this);
    sp->addWidget(probTextEdit);
    sp->addWidget(soluTextEdit);

    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(sp);
    //layout->addStretch();
    layout->addWidget(submitButton);
    this->setLayout(layout);
}
