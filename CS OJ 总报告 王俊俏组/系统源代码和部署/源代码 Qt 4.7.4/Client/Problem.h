#ifndef PROBLEM_H
#define PROBLEM_H

#include <QString>
#include <string>
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

    QString print(){
        std::string _ID=QString::number(probID).toStdString();
        std::string _name=probName.toStdString();
        std::string _sol=QString::number(totalSolved).toStdString();
        std::string _try=QString::number(totalTry).toStdString();
        std::string _ret=std::string(48,' ');
        for(unsigned int i=0;i<_ID.length();i++)_ret[i]=_ID[i];
        for(unsigned int i=0;i<_name.length();i++) _ret[i+5]=_name[i];
        for(unsigned int i=0;i<_sol.length();i++) _ret[i+37]=_sol[i];
        _ret[42]='/';
        for(unsigned int i=0;i<_try.length();i++) _ret[i+43]=_try[i];
        return QString::fromStdString(_ret);
    }
};
#endif // PROBLEM_H
