#ifndef JUDGE_H
#define JUDGE_H

#include "Problem.h"
#include<QProcess>

class Judge
{
public:
    Judge();

    int judge(Problem* p,QString judge_home, int runID,QString &CEString);


};

#endif // JUDGE_H
