#ifndef PROBLEM_H
#define PROBLEM_H

#include <QString>

class Problem
{
public:
    Problem();

    //
    int probID;
    QString probName,probFileAddr,inputFileAddr,outputFileAddr;  //probName ²»ÄÜ°üº¬$·ûºÅ
    int runTimeLimit,runMemoryLimit,totalTry,totalSolved;

    QString toString();
    void initWithString(QString str);
};
#endif // PROBLEM_H
