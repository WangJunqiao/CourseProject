//#pragma comment(linker, "/STACK:16777216")
#pragma comment(lib,"psapi.lib")
#pragma comment(lib,"Advapi32.lib")

#include<stdio.h>
#include<Windows.h>
#include<string.h>
#include<memory.h>
#include<assert.h>
#include<time.h>
#include<Psapi.h> //process_memory_counters


#define DEBUG 0
#define BUFSIZE 128
#define TMP_OUTPUT_FILE "_onlinejudge_tmp_output.txt"   //

#define OJ_AC 0
#define OJ_PE 1
#define OJ_TLE 2
#define OJ_MLE 3
#define OJ_RE 4
#define OJ_OLE 5
#define OJ_WA 6

char JUDGE_RESULT[20][50]={ 
	"Accepted",              //0
	"Presentation Error",    //1
	"Time Limit Exceeded",   //2
	"Memory Limit Exceeded", //3
	"Runtime Error",         //4
	"Output Limit Exceeded", //5
	"Wrong Answer"           //6
};


char exec_name[BUFSIZE];    //传入的可执行文件
char input[BUFSIZE];        //测试数据的输入文件
char output[BUFSIZE];       //测试数据的输出文件
unsigned int time_limit;    //时间限制 单位ms
unsigned int memory_limit;  //空间限制 单位kb
int is_spj;                 //是否是special judge
char spj_exec[BUFSIZE];     //spj的可执行文件, 参数应该是 input.txt output.txt _tmp_output.txt
char res_file[BUFSIZE];     //judge结果的输出文件
FILE *res_f;          

//清除一个进程的全部权限 但是它还是可以读写文件,访问网络...
BOOL ClearPrivilege(HANDLE processHandle) { 
	HANDLE hToken;
	if( !OpenProcessToken(processHandle,TOKEN_ADJUST_PRIVILEGES 
		| TOKEN_QUERY | TOKEN_QUERY_SOURCE,&hToken) 
		){
		fprintf(res_f,"OpenProcessToken failed (%d)\n",GetLastError());
	}
    if ( !AdjustTokenPrivileges(
           hToken, 
           TRUE, 
           NULL,
           (DWORD)0, 
           (PTOKEN_PRIVILEGES) NULL, 
           (PDWORD) NULL) )
    { 
          fprintf(res_f,"AdjustTokenPrivileges error: %u\n", GetLastError() ); 
          return FALSE; 
	}
	if( DEBUG ) fprintf(res_f,"Disable All Privileges successfully!\n");
    return TRUE;
}

//比较文件file1和file2的内容,判断是 accepted,wrong answer还是presentation error
int _compare(const char *file1, int filesize1, const char *file2, int filesize2){
	FILE *f1=fopen(file1,"r");
	FILE *f2=fopen(file2,"r");
	if( !f1 || !f2 ) return OJ_WA;
	char c; int i,j;
	char* buf1=new char[(int)filesize1+2];
	char* buf2=new char[(int)filesize2+2];
	
	for(i=0;(c=fgetc(f1))!=EOF;buf1[i++]=c);
	buf1[i]='\0';

	for(i=0;(c=fgetc(f2))!=EOF;buf2[i++]=c);
	buf2[i]='\0';

	//fprintf(res_f,"previous: %d %d\n",filesize1,filesize2);
	filesize1=strlen(buf1);  //为了解决windows系统 换行是\r\n的问题
	filesize2=strlen(buf2);
	//fprintf(res_f,"previous: %d %d\n",filesize1,filesize2);

	fclose(f1);
	fclose(f2);

	if( (filesize1==filesize2) && (strcmp(buf1,buf2)==0) ) {
		delete[] buf1;
		delete[] buf2;
		return OJ_AC;
	} 

	for(i=j=0;i<filesize1 && j<filesize2;){
		while(i<filesize1 && (buf1[i]==' ' || buf1[i]=='\r' || buf1[i]=='\n' || buf1[i]=='\t') ) i++;
		while(j<filesize2 && (buf2[j]==' ' || buf2[j]=='\r' || buf2[j]=='\n' || buf2[j]=='\t') ) j++;
		if( buf1[i]!=buf2[j] ){
			//fprintf(res_f,"buf1[%d]: %d  buf2[%d]: %d\n",i,(int)buf1[i],j,(int)buf2[j]);
			delete[] buf1;
			delete[] buf2;
			return OJ_WA;
		}
		if( i<filesize1 ) i++;
		if( j<filesize2 ) j++;
	}
	while(i<filesize1 && (buf1[i]==' ' || buf1[i]=='\r' || buf1[i]=='\n' || buf1[i]=='\t') ) i++;
	while(j<filesize2 && (buf2[j]==' ' || buf2[j]=='\r' || buf2[j]=='\n' || buf2[j]=='\t') ) j++;
	if( buf1[i]!=buf2[j] ){
		delete[] buf1;
		delete[] buf2;
		//fprintf(res_f,"buf1[%d]: %d  buf2[%d]: %d\n",i,(int)buf1[i],j,(int)buf2[j]);
		return OJ_WA;
	}
	delete[] buf1;
	delete[] buf2;
	//fprintf(res_f,"here\n");
	return OJ_PE;
}


void _init_args(int argc,char **argv){
	for(int i=1;i<argc;i+=2) {
		if( strcmp(argv[i],"-E")==0 ){
			strcpy_s(exec_name,argv[i+1]);
		}else if( strcmp(argv[i],"-I")==0 ){
			strcpy_s(input,argv[i+1]);
		}else if( strcmp(argv[i],"-O")==0 ){
			strcpy_s(output,argv[i+1]);
		}else if( strcmp(argv[i],"-T")==0 ){
			sscanf_s(argv[i+1],"%u",&time_limit);
		}else if( strcmp(argv[i],"-M")==0 ){
			sscanf_s(argv[i+1],"%u",&memory_limit);
		}else if( strcmp(argv[i],"-SPJ")==0 ){
			is_spj=1;
			strcpy_s(spj_exec,argv[i+1]);
		}else if( strcmp(argv[i],"-R")==0 ){
			strcpy_s(res_file,argv[i+1]);
		}else{
			break;
		}
	}
}

bool _check_args(){
	if( strlen(exec_name)==0 ) return false;
	if( strlen(input)==0 ) return false;
	if( strlen(output)==0 ) return false;
	if( strlen(res_file)==0 ) return false;
	return true;
}

//获得内存的使用情况  kb
int getMemoryUseage(HANDLE hProcess){
	PROCESS_MEMORY_COUNTERS pmc;
	if( GetProcessMemoryInfo(hProcess,&pmc,sizeof(pmc)) ) {
		//...
	}else{
		return -1;
	}
	return pmc.PeakPagefileUsage/1024;
}

//获得文件的大小 bytes
__int64 getFileSize(LPSTR szPath){ 
	WIN32_FILE_ATTRIBUTE_DATA wfad;
	//printf("文件：%s\n",szPath);
	WCHAR w_e[BUFSIZE];
	MultiByteToWideChar( CP_ACP, 0, szPath,
        strlen(szPath)+1, w_e,   
     sizeof(w_e)/sizeof(w_e[0]) );

	if(!GetFileAttributesEx( w_e,
		GetFileExInfoStandard,
		&wfad))
	{
		fprintf(res_f,"File Size Retrieve failed：%d\n",GetLastError());
		return -1;
	}
	return wfad.nFileSizeHigh*( (__int64)1<<32 ) + wfad.nFileSizeLow;
}


__int64 _getTime(FILETIME ft){
	SYSTEMTIME sysT;
	FileTimeToSystemTime(&ft,&sysT);
	return sysT.wMinute*60000+sysT.wSecond*1000+sysT.wMilliseconds;
}

int getExecuteTime(HANDLE hProcess){
	FILETIME creationT, exitT, kernelT, userT;
	if( !GetProcessTimes(hProcess, 
			&creationT, &exitT,
			&kernelT, &userT ) ){
		fprintf(res_f,"failed to get execute time\n");
		return -1;
	}
	//__int64 cT=creationT.dwHighDateTime*((__int64)1<<32) + creationT.dwLowDateTime;
	//__int64 eT=exitT.dwHighDateTime*((__int64)1<<32) + exitT.dwLowDateTime;

	__int64 res=_getTime(kernelT)+_getTime(userT);

	//if( DEBUG ) 
		//fprintf(res_f,"cT: %I64d  eT: %I64d  res: %I64d\n",cT,eT, res); 
	return (int)res;
}

/*
Judge_Core.exe  -I in.txt -O out.txt -T 1000 -M 32768 -R result.txt -E a+bpe.exe
*/

char developer[55][150]={
	"                                                    ",
	"               -------------------------------------",
	"               |    Developed by zjut_DD(王俊俏)    |",
	"               | Zhejiang University of Technology |",
	"               |    Bug Report: 774367334@qq.com   |",
	"               -------------------------------------"
};

int main(int argc,char** argv){ 

	_init_args(argc,argv);
	if( !_check_args() ) return 1; //argments error

	res_f=fopen(res_file,"w");
	freopen(input,"r",stdin);
	freopen(TMP_OUTPUT_FILE,"w",stdout);

	SetErrorMode(SEM_FAILCRITICALERRORS);
	SetErrorMode(SEM_NOGPFAULTERRORBOX); //让进程(包括子进程)出错后不要弹出dialog!!!

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si,sizeof(si));
	si.cb=sizeof(si);
	ZeroMemory(&pi,sizeof(pi));

	WCHAR w_exec[BUFSIZE];
	MultiByteToWideChar( CP_ACP, 0, exec_name,
        strlen(exec_name)+1, w_exec,   
     sizeof(w_exec)/sizeof(w_exec[0]) );

	if( !CreateProcess( w_exec,
		NULL,
		NULL,
		NULL,
		false,
		DWORD(0),
		NULL,
		NULL,
		&si,  //cha,这个startupinfo必须要的!!! 不然error=87;
		&pi) ){
			fprintf(res_f,"Create Process failed (%d).\n",GetLastError());
			fclose(res_f);
			return 2; //
	}

	ClearPrivilege(pi.hProcess); 
	__int64 ofsize=getFileSize(output), o2fsize;
	int res_id=-1, exec_time=-1, memory_useage=-1;
	DWORD exitCode;

	while( true ){
		if( (exec_time=getExecuteTime(pi.hProcess)) > time_limit ) {
			TerminateProcess(pi.hProcess,999);
			res_id=2;
			break;
		}
		if( (memory_useage=getMemoryUseage(pi.hProcess)) > memory_limit ) {
			TerminateProcess(pi.hProcess,999);
			res_id=3;
			break;
		}
		if( getFileSize(TMP_OUTPUT_FILE) > ofsize+1048576 ) { //多出1Mb
			TerminateProcess(pi.hProcess,999);
			res_id=5;
			break;
		}
		if ( !GetExitCodeProcess(pi.hProcess,&exitCode) ){
			fprintf(res_f,"GetExitCodeProcess failed (%d)\n",GetLastError());
			fclose(res_f);
			return 3;
		}
		if( exitCode != STILL_ACTIVE ) {  //执行完了
			break;
		}
	}
	fflush(stdout);

	if( exec_time<0 ) 
		exec_time=getExecuteTime(pi.hProcess);
	if( memory_useage<0 ) 
		memory_useage=getMemoryUseage(pi.hProcess);
	if( memory_useage > memory_limit ) {
		res_id=3;
	}

	if ( !GetExitCodeProcess(pi.hProcess,&exitCode) ){
		fprintf(res_f,"GetExitCodeProcess failed (%d)\n",GetLastError());
		fclose(res_f);
		return 3;
	}

	if( res_id>=0 ){
		//...
	}else if( exitCode != 0 ){
		res_id=4;  //re
	}else {
		o2fsize=getFileSize(TMP_OUTPUT_FILE);
		res_id=_compare(output,ofsize,TMP_OUTPUT_FILE,o2fsize);
	}

	fprintf(res_f,"%s\n",JUDGE_RESULT[res_id]);

	//if( res_id==OJ_AC ){
		fprintf(res_f,"Execute Time:  %d ms\n",getExecuteTime(pi.hProcess));
		fprintf(res_f,"Memory Useage: %d kb\n",getMemoryUseage(pi.hProcess));
	//}
	for(int i=0;i<6;i++) fprintf(res_f,"%s\n",developer[i]);

	fclose(res_f);
	return 0;
}
