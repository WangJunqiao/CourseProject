#include "Judge.h"
#include<QProcess>
#include<QStringList>
#include<QtCore>
#include<stdio.h>
//#include<QtGui>
#include<QString>
#include<stdio.h>
#include<time.h>
#include<QFile>
#include "ConstData.h"
Judge::Judge()
{

}

int Judge::judge(Problem* p,QString judge_home, int runID,QString &CEString){
    QProcess process;
    process.setProcessEnvironment(QProcessEnvironment::systemEnvironment());

    QStringList arg;
    QString exe_name=(judge_home+QString("/exe_file/tmp.exe"));

    QFile exe_old(exe_name);
    if( exe_old.exists() ) {
        if( !exe_old.remove()) {
            qDebug()<<"remove tmp.exe failed!";
            return JUDGE_RES_INT_ERR;
        }
    }
    arg<<(judge_home+QString("/submitted_code/")+QString::number(runID)+QString(".cpp"));
    arg<<QString("-o");
    arg<<exe_name;
    //arg<<QString("-ansi");
    //arg<<QString("-fno");
    //arg<<QString("-asm");
    arg<<QString("-O2");
    arg<<QString("-Wall");
    arg<<QString("-lm");
    arg<<QString("--static");
    arg<<QString("-D");
    arg<<QString("ONLINE_JUDGE");

    clock_t _time=clock();

    process.start(QString("g++.exe"),arg);
    if( !process.waitForFinished(10000) ){ //等待10秒
        return JUDGE_RES_INT_ERR;
    }
    if( OJ_DEBUG ) qDebug()<<"compile time: "<<clock()-_time<<" ms";

    QFile exe_new(exe_name);
    if( !exe_new.exists() ){  //compile error
        CEString=QString( process.readAllStandardError() );
        return JUDGE_RES_CE;
    }

    arg.clear();
    arg<<"-E";
    arg<<exe_name;
    arg<<"-I";
    arg<<p->inputFileAddr;
    arg<<"-O";
    arg<<p->outputFileAddr;
    arg<<"-T";
    arg<<QString::number(p->runTimeLimit);
    arg<<"-M";
    arg<<QString::number(p->runMemoryLimit);
    arg<<"-R"<<(judge_home+"/OJCore/__result.txt");


    _time=clock();
    process.start(judge_home+"/OJCore/Judge_Core.exe",arg); //开始执行
    process.waitForFinished(600000);
    process.kill();
    if( OJ_DEBUG ) qDebug()<<"Judge_Core used time: "<<clock()-_time<<" ms";

    QFile _res_f(judge_home+"/OJCore/__result.txt");
    if( !_res_f.open(QIODevice::ReadOnly) ){
        qDebug()<<"failed to open __result.txt\n";
    }
    QString res(_res_f.readLine(100));
    res=res.trimmed();

    QFile rem(exe_name);
    if( rem.exists() ) rem.remove();

    if( res=="Accepted" ) return JUDGE_RES_AC;
    else if( res=="Wrong Answer" ) return JUDGE_RES_WA;
    else if( res=="Time Limit Exceeded" ) return JUDGE_RES_TLE;
    else if( res=="Memory Limit Exceeded" ) return JUDGE_RES_MLE;
    else if( res=="Presentation Error" ) return JUDGE_RES_PE;
    else if( res=="Runtime Error" ) return JUDGE_RES_RE;
    else if( res=="Output Limit Exceeded" ) return JUDGE_RES_OLE;
    else return JUDGE_RES_INT_ERR;
}
