#include "Problem.h"
#include<QStringList>

Problem::Problem()
{
}

QString Problem::toString(){
    return QString::number(probID)+'$'+
            probName+'$'+probFileAddr+'$'+
            inputFileAddr+'$'+outputFileAddr+'$'+
            QString::number(runTimeLimit)+'$'+
            QString::number(runMemoryLimit)+'$'+
            QString::number(totalTry)+'$'+
            QString::number(totalSolved);
}

void Problem::initWithString(QString str){
    QStringList L=str.split('$');
    //assert(L.length()==9,tr("Problem::initWithString stringlist's length not enough!") );
    probID=L[0].toInt();
    probName=L[1];
    probFileAddr=L[2];
    inputFileAddr=L[3];
    outputFileAddr=L[4];
    runTimeLimit=L[5].toInt();
    runMemoryLimit=L[6].toInt();
    totalTry=L[7].toInt();
    totalSolved=L[8].toInt();
}
