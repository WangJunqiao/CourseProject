
/*
操作系统大型实验 Unix 文件管理系统
Author: 王俊俏(zjut_DD)
*/
/*
第0块为引导块,存放用户名和密码等
第1块为系统初始化块,存放空闲i节点号栈,空闲盘快号栈等
第2~IB_num+1为i节点块
第IB_num+2~B_numb-1为数据块
*/

#include<iostream>
#include<stdio.h>
#include<string>
#include<time.h>
using namespace std;

#define B_size 1024    //块大小字节数

#define B_num 4096      //盘快数目 调试用128 最后用4096
#define FBS_size 20    //空闲盘快号栈大小

#define IB_num 20      //i节点盘快数
#define FIS_size 20    //空闲i节点号栈大小

//类声明
struct Identifier;     //标识符类
struct File2I;         //文件名对应i节点号类
struct INode;          //i节点类
struct FIStack;        //空闲i节点号栈 类
struct FBStack;        //空闲盘块号栈 类
struct FileSysManager; //主进程类

struct Identifier{     //14字节  标识符类,记录文件名,文件拥有者,密码等 
	char buf[14]; 
	Identifier(){}
	Identifier(char *str){
		int i=0;
		while( str[i] ) buf[i]=str[i], i++;
		buf[i]='\0';
	}
	bool operator==(const Identifier &b)const{ //判断两个名字是否相等
		return strcmp(this->buf, b.buf) == 0;
	}
};

struct File2I{ //16字节  文件->i节点编号 映射关系  
	Identifier fname; //文件名
	short Iid;    //i节点编号
};

struct INode{ //  72字节   可以放 1024*20/72= 300个i节点
	int fsize;        //文件大小(字节)
	short addr[6];    //文件地址,记录块号   4个直接地址,1个一次间址,1一个二次间址
	short Iid;        //i节点编号
	Identifier user;  //用户是谁
	bool isDirection; //是否是目录
	tm edit_t;        //修改时间,引用time.h中的tm类 36字节

	//初始化i节点
	void init(int _fsize, bool _isDir, short _Iid, Identifier _user){  
		fsize=_fsize;
		isDirection=_isDir;
		Iid=_Iid;
		user=_user;
		edit_t=getCurTime();
	}

	//找到文件的第index个字节的地址, 传引用
	void fileIndex(FILE* &fp,int index){ 
		if( index<4*B_size ){ //直接地址
			short block=addr[ index/B_size ] , offset=index%B_size; //块号 和块内偏移量
			fseek(fp,block*B_size+offset,0);
		}else if( index < 4*B_size+B_size/2*B_size ){ //一次间址
			index-=4*B_size;
			short block, offset=index%B_size, temp=index/B_size; //addr[4]->temp->target
			fseek(fp,addr[4]*B_size+2*temp,0);
			fread(&block,sizeof(short),1,fp);
			fseek(fp,block*B_size+offset,0);
		}else{       //两次间址
			index-=(4*B_size+B_size/2*B_size);
			short block, offset=index%B_size, block2=index/B_size, temp1,temp2; //addr[5]->temp1->temp2->target
			temp2=block2%(B_size/2), temp1=block2/(B_size/2); //
			fseek(fp,addr[5]*B_size+2*temp1,0);  //一层一层找...
			fread(&block2,sizeof(short),1,fp);
			fseek(fp,block2*B_size+2*temp2,0);
			fread(&block,sizeof(short),1,fp);
			fseek(fp,block*B_size+offset,0);
		}
	}

	//给文件增加一个盘块号, 需要修改i节点信息中的addr[6]  (调用这个之前,文件大小fsize必须已经更新!!)
	void addBlock(FILE* fp, short Bid);

	//在目录里添加文件项, 需要用到空闲盘快号栈,所以放到后面定义
	void add(FILE* fp, File2I &item); 

	//释放块空间
	void freeBlock(FILE* fp);  

	//给文件写入内容
	void add(FILE* fp, char *ch, int length);  

	//将文件的内容读取出来
	void readContent(FILE* fp,char *ch);

	//将i节点写入磁盘
	void update(FILE* fp){ 
		findIpos(fp,Iid);
		fwrite(this,sizeof(INode),1,fp);
	}

	//定位第Iid个i节点的位置
	static void findIpos(FILE* &fp,short Iid){ 
		//i节点从2号块开始放
		fseek(fp, 2*B_size + sizeof(INode)*Iid ,0); //第二块首地址 + 偏移地址
	}

	//获取当前系统时间, 返回一个tm变量
	static tm getCurTime(){ 
		time_t t=time(NULL);
		return *localtime(&t);
	}
};

struct FIStack{ //42字节  空闲节点号 栈  大小要小于INode的大小
	short st[FIS_size], top;  //栈顶
	FIStack(){
		top=0; //空栈
	}

	//放入一个空闲i节点号   采用成组链接法
	void push(FILE* fp, short Iid){ 
		if( top== FIS_size ){ //栈满了
			INode::findIpos(fp,Iid);
			fwrite(st,sizeof(short),top,fp);
			top=0;
			st[top++]=Iid;
		}else{
			st[top++]=Iid;
		}
	}

	//弹出一个空闲i节点号
	short pop(FILE* fp){
		if( top==1 ){ //只剩一个了
			int Iid=st[0];
			INode::findIpos(fp,Iid);
			top=FIS_size;
			fread(st,sizeof(short),top,fp);
			return Iid;
		}else{
			return st[--top];
		}
	}

	//从磁盘上把FIStack读入内存
	void init(FILE* fp){ 
		fseek(fp,B_size,0);
		fread(this,sizeof(FIStack),1,fp);
	}

	//将 空闲i节点号栈 写入磁盘
	void update(FILE* fp){ 
		fseek(fp,B_size,0);
		fwrite(this,sizeof(FIStack),1,fp); 
	}
};

struct FBStack{ //42字节 空闲盘块号 栈
	short st[FBS_size], top; //
	FBStack(){
		top=0;
	}

	//放入一个空闲块编号  采用成组链接法
	void push(FILE* fp, short Bid){ 
		if( top== FIS_size ){ //栈满了
			fseek(fp,Bid*B_size,0);
			fwrite(st,sizeof(short),top,fp);
			top=0;
			st[top++]=Bid;
		}else{
			st[top++]=Bid;
		}
	}

	//弹出一个空闲盘块号
	short pop(FILE* fp){
		if( top==1 ){ //只剩一个了
			int Bid=st[0];
			fseek(fp,Bid*B_size,0);
			top=FIS_size;
			fread(st,sizeof(short),top,fp);
			return Bid;
		}else{
			return st[--top];
		}
	}

	//从磁盘上把FBStack读入内存
	void init(FILE* fp){  
		fseek(fp, B_size + sizeof(FIStack) ,0);
		fread(this,sizeof(FBStack),1,fp);
	}

	//将 空闲盘块号栈 写入磁盘
	void update(FILE* fp){ 
		fseek(fp, B_size + sizeof(FIStack) ,0);
		fwrite(this,sizeof(FBStack),1,fp);
	}
};

struct FileSysManager{
	FILE *fp;           //文件指针
	FIStack FIS;        //空闲节点号栈
	FBStack FBS;        //空闲盘块号栈
	Identifier curUser; //当前用户
	char curDir[50];    //当前目录
	INode curINode;     //当前文件的i节点

	char cmd[50],arg[50]; //命令和参数

	FileSysManager(){

	}
	void systemInitial(){
		fp=fopen("disk.txt","rb+");
		//用户登录模块
		int num=0;
		Identifier user[10],psw[10],u,p;
		fread(&num,sizeof(int),1,fp);  //从0#中 读取全部用户名,密码
		fread(user,sizeof(Identifier),num,fp);
		fread(psw,sizeof(Identifier),num,fp);
		printf("请输入用户名 密码登录:\n");
		while( true ){ //循环测试 直到输入正确
			scanf(" %s %s",u.buf, p.buf);
			getchar();
			bool success=false; 
			for(int i=0;i<num;i++){
				if( user[i]==u && psw[i]==p ){
					printf("登录成功\n");
					success=true;
					break;
				}
			}
			if( success ){
				curUser=u; //
				break;
			}
			printf("用户名或密码错误,请重新尝试!\n");
		}
		//
		fseek(fp, B_size ,0);
		fread(&FIS,sizeof(FIStack),1,fp); //读取,这两个常驻内存的
		fread(&FBS,sizeof(FBStack),1,fp);
		//载入home目录（根目录）
		memcpy(curDir,"/home\0",sizeof(char)*6);
		INode::findIpos(fp,0);
		fread(&curINode,sizeof(INode),1,fp);  
	}
	void lsdir(){
		if( curINode.isDirection == false ){
			puts("当前文件不是目录!!");
			return;
		}
		int num=curINode.fsize/sizeof(File2I); //当前目录有几项
		File2I *items=new File2I[num];
		for(int i=0;i<num;i++){  //全部读取出来
			curINode.fileIndex(fp,i*sizeof(File2I));
			fread(items+i,sizeof(File2I),1,fp);
		}
		INode inode;
		for(int i=0;i<num;i++){ //看用户名显示
			INode::findIpos(fp,items[i].Iid);
			fread(&inode,sizeof(INode),1,fp);
			if( inode.user == curUser){
				printf("%-10s %d/%02d/%02d %02d:%02d %7s %5d字节\n",
					items[i].fname.buf,inode.edit_t.tm_year+1900,
					inode.edit_t.tm_mon+1,inode.edit_t.tm_mday,
					inode.edit_t.tm_hour,inode.edit_t.tm_min,
					inode.isDirection?"文件夹":"文件", inode.fsize);
			}
		}
		delete[] items;
	}
	void mkdir(){
		if( curINode.isDirection == false ){
			puts("当前文件不是目录!!");
			return;
		}
		File2I item;
		item.fname=arg;
		item.Iid=FIS.pop(fp); //弹出一个空闲i节点编号
		INode inode; inode.init(0,true,item.Iid, curUser);
		inode.update(fp);           //写入磁盘
		curINode.add(fp, item);     //写入当前文件夹中
		puts("添加目录成功!");
	}
	void mkfile(){
		if( curINode.isDirection == false ){
			puts("当前文件不是目录!!");
			return;
		}
		File2I item;
		item.fname=arg;
		item.Iid=FIS.pop(fp); //弹出一个空闲i节点编号
		INode inode; inode.init(0,false,item.Iid, curUser);
		inode.update(fp);           //写入磁盘
		curINode.add(fp, item);     //写入当前文件夹中
		puts("添加文件成功!");
	}
	void cd(){
		//arg为目录
		if( memcmp(arg,"/home",5) !=0 ){ //内存比较
			puts("Invalid Direction!");
		}else{
			int i=5;
			INode inode, tempNode;
			INode::findIpos(fp,0);
			fread(&inode,sizeof(INode),1,fp); //读取home目录i节点
			bool suc=true;  //设置成功
			while(arg[i]){
				i++;
				int j=0;
				Identifier f;
				while(arg[i] && arg[i]!='/') {
					f.buf[j]=arg[i];
					i++,j++;
				}
				f.buf[j]='\0';   //获得下一级目录f
				if( inode.isDirection == false ){ //当前文件不是目录
					suc=false;
					break;
				}

				int num=inode.fsize/sizeof(File2I); //当前目录有几项
				File2I *items=new File2I[num];
				for(int i=0;i<num;i++){  //全部读取出来
					inode.fileIndex(fp,i*sizeof(File2I));
					fread(items+i,sizeof(File2I),1,fp);
				}
				bool find=false;  //是否找到
				for(int i=0;i<num;i++){
					INode::findIpos(fp,items[i].Iid);
					fread(&tempNode,sizeof(INode),1,fp);
					if( items[i].fname == f && tempNode.user==curUser ){ //判断条件注意有两个**
						find=true;
						inode=tempNode;
						break;
					}
				}
				delete[] items;
				if( find==false ) {
					suc=false;
					break;
				}
			}
			if( suc ){  //找到了要更新当前目录,和当前i节点
				memcpy(curDir,arg,sizeof(arg));
				curINode=inode;
			}else{
				puts("Invalid Direction!");
			}
		}
		puts("当前目录修改成功!");
	}
	void chown(){
		if( memcmp(curDir,"/home\0",6)==0 ) {
			puts("无法更改根目录的拥有者!!");
			return;
		}
		curINode.user=arg;
		curINode.update(fp);  //写入磁盘,固化
		memcpy(curDir,"/home\0",sizeof(char)*6); //重新载入根目录
		INode::findIpos(fp,0);
		fread(&curINode,sizeof(INode),1,fp);  
		puts("文件拥有者修改成功!");
	}
	void back(){
		if( memcmp(curDir,"/home\0",6)==0 ) {
			puts("已经是根目录了,无法返回!!");
			return;
		}
		memcpy(arg,curDir,sizeof(arg));
		int i=strlen(arg)-1;
		while(arg[i]!='/') i--;
		arg[i]='\0';
		cd();    //
		puts("成功返回上一级目录!");
	}
	void rename(){
		if( memcmp(curDir,"/home\0",6)==0 ) {
			puts("无法更改根目录的文件名!!");
			return;
		}
		Identifier curName;
		Identifier nxtName=arg;  //修改后的文件名
		int i=strlen(curDir)-1;
		while( curDir[i]!='/') i--;
		curName=curDir+i+1;   //当前文件名
		back(); //先返回上一级目录

		int num=curINode.fsize/sizeof(File2I); //当前目录有几项
		File2I *items=new File2I[num];
		for(int i=0;i<num;i++){  //全部读取出来
			curINode.fileIndex(fp,i*sizeof(File2I));
			fread(items+i,sizeof(File2I),1,fp);
		}
		for(int i=0;i<num;i++){    //重新写入
			if( items[i].fname == curName ){
				items[i].fname=nxtName;
			}
			curINode.fileIndex(fp,i*sizeof(File2I));
			fwrite(items+i,sizeof(File2I),1,fp);
		}
		delete[] items;

		memcpy(arg,curDir,sizeof(arg));
		i=strlen(arg);
		arg[i]='/';
		memcpy(arg+i+1,nxtName.buf,strlen(nxtName.buf)+1);
		cd();    //回到这个路径
		puts("文件名修改成功!");
	}
	void write(){
		if( curINode.isDirection == true ){
			puts("当前路径是一个目录,无法写入数据!!");
			return;
		}
		FILE* fptr=fopen(arg,"rb");
		if( fptr==NULL ) {
			puts("你所指定的文件不存在!!");
			return;
		}
		fseek(fptr,0,2);
		int len=ftell(fptr);
		if( len > 4*B_size + B_size/2*B_size + B_size/2*B_size/2*B_size ){
			puts("内容太长,无法写入!!");
			return;
		}
		fseek(fptr,0,0);
		char* buf=new char[len+2];
		for(int i=0;i<len;i++){
			fread(buf+i,sizeof(char),1,fptr);
		}
		fclose(fptr); //关闭文件
		curINode.add(fp,buf,len);
		delete[] buf;
		puts("数据写入成功!");
	}
	void show(){
		if( curINode.isDirection==true ){
			puts("当前路径是目录!!");
			return;
		}
		char *buf=new char[ curINode.fsize+2 ];
		curINode.readContent(fp,buf);
		//下面调用系统记事本显示内容
		int i=strlen(curDir)-1;
		while( curDir[i]!='/' ) i--;
		Identifier fname=curDir+i+1;
		FILE *fptr=fopen(fname.buf,"wb");
		for(int i=0;i<curINode.fsize;i++) {
			fwrite(buf+i,sizeof(char),1,fptr);
		}
		fclose(fptr);      //要先关闭文件指针, 强行将内容从缓冲区写入磁盘
		char command[50]="notepad.exe ";
		system(strcat(command,fname.buf) ); //系统调用

		remove(fname.buf); //删除文件

		delete[] buf;
	}
	void removeFile(){ //递归删除
		Identifier target=arg; //要删除的目标
		int num=curINode.fsize/sizeof(File2I); //当前目录有几项
		File2I *items=new File2I[num];
		for(int i=0;i<num;i++){  //全部读取出来
			curINode.fileIndex(fp,i*sizeof(File2I));
			fread(items+i,sizeof(File2I),1,fp);
		}
		INode tempNode;
		int pos=0;
		for(int i=0;i<num;i++){  
			if( items[i].fname == target ){
				INode::findIpos(fp,items[i].Iid);
				fread(&tempNode,sizeof(INode),1,fp);
				_removeFile(tempNode); //删除这个目录
				curINode.fsize-=sizeof(File2I);
			}else{
				curINode.fileIndex(fp,pos);
				fwrite(items+i,sizeof(File2I),1,fp);
				pos+=sizeof(File2I);
			}
		}
		curINode.update(fp);
		puts("文件删除成功!");
	}
	void _removeFile(INode father){
		if( father.isDirection == false ){  //如果就是一个文件了,那么直接删除
			father.freeBlock(fp);  //回收盘块号
			Thread.FIS.push(fp,father.Iid);
			Thread.FIS.update(fp);
		}else{     //如果是一个目录,那么递归删除
			int num=father.fsize/sizeof(File2I); //当前目录有几项
			File2I *items=new File2I[num];
			for(int i=0;i<num;i++){  //全部读取出来
				father.fileIndex(fp,i*sizeof(File2I));
				fread(items+i,sizeof(File2I),1,fp);
			}
			INode tempNode;
			for(int i=0;i<num;i++){  //先删除子目录
				INode::findIpos(fp,items[i].Iid);
				fread(&tempNode,sizeof(INode),1,fp);
				_removeFile(tempNode);
			}
			father.freeBlock(fp);  //回收盘块号
			Thread.FIS.push(fp,father.Iid);
			Thread.FIS.update(fp);
		}
	}
	void run(){ //运行主管理程序，接受用户命令
		puts("Reduced Unix File Manage System [版本 2.1]");
		puts("(C) 版权所有 2010-2011 王俊俏(zjut_DD).");
		while( true ){
			printf("%s ",curDir);  //输出当前所在路径
			char buf[100];
			gets(buf);

			sscanf(buf," %s %s",cmd,arg);  //字符串输入

			if( strcmp(cmd,"exit")==0 ) { //退出系统
				break;
			}else if( strcmp(cmd,"lsdir")==0 ){   //显示目录列表
				lsdir();
			}else if( strcmp(cmd,"mkdir")==0 ){ //添加一个目录
				mkdir();
			}else if( strcmp(cmd,"mkfile")==0 ){ //添加一个文件
				mkfile();
			}else if( strcmp(cmd,"cd")==0 ){  //改变当前目录
				cd();
			}else if( strcmp(cmd,"chown")==0 ){ //改变所有者
				chown();
			}else if( strcmp(cmd,"rename")==0 ){ //对当前目录重命名
				rename();
			}else if( strcmp(cmd,"back") ==0 ){ //返回上一级目录
				back();
			}else if( strcmp(cmd,"write")==0 ){  //将内容写入当前文件
				write();
			}else if( strcmp(cmd,"show") ==0 ){  //显示当前文件的内容
				show();
			}else if( strcmp(cmd,"remove") ==0 ){ //删除当前目录及其子目录
				removeFile();
			}
		}
	}
	~FileSysManager(){  //是否一定会被调用到？？？
		FIS.update(fp);
		FBS.update(fp);
		fclose(fp);     //关闭
		puts("析构函数已调用   文件指针已关闭!!");
	}
}Thread;

void INode::addBlock(FILE* fp, short Bid){ 
	short Bnum=(fsize-1)/B_size; //要添加的这个盘快是这个文件的第Bnum个盘快, base0
	if(Bnum < 4 ){ //直接地址, 无需修改磁盘,只要更新addr就行了
		addr[Bnum]=Bid;
		this->update(fp);   //内存中i节点要和磁盘上的保持一致****
	}else if( Bnum < 4+B_size/2 ){ //一次间址, 需要修改磁盘了
		Bnum-=4;
		if( Bnum==0 ){
			short nBid=Thread.FBS.pop(fp); //这里注意要再申请一个盘块!!!!!!!
			Thread.FBS.update(fp);
			addr[4]=nBid; //
			this->update(fp);
		}
		fseek(fp, addr[4]*B_size+Bnum*2, 0);
		fwrite(&Bid,sizeof(short),1,fp);
	}else {    //二次间址, 需要修改磁盘
		Bnum-=(4+B_size/2);
		if( Bnum==0 ){
			short nBid=Thread.FBS.pop(fp); //这里注意要再申请一个盘块!!!!!!!
			Thread.FBS.update(fp);
			addr[5]=nBid; //
			this->update(fp);
		}
		short temp1=Bnum/(B_size/2) ,temp2=Bnum%(B_size/2) , B=addr[5];
		if( temp2==0 ){
			short nBid=Thread.FBS.pop(fp); //这里注意要再申请一个盘块!!!!!!!
			Thread.FBS.update(fp);
			fseek(fp,B*B_size+temp1*2,0);
			fwrite(&nBid,sizeof(short),1,fp);
		}
		fseek(fp,B*B_size+temp1*2,0);
		fread(&B,sizeof(short),1,fp);
		fseek(fp,B*B_size+temp2*2,0);
		fwrite(&Bid,sizeof(short),1,fp);   //
	}
}

void INode::add(FILE* fp, File2I &item){ //在目录里添加文件项
	int num1=fsize/B_size, num2=(fsize+sizeof(item))/B_size;
	if( fsize%B_size ) num1++;
	if( (fsize+sizeof(item))%B_size ) num2++;
	if( num1==num2 ){ //不需要申请新盘快
		fileIndex(fp,fsize);
		fwrite(&item,sizeof(File2I),1,fp);
		fsize+=sizeof(item);
	}else{
		short Bid=Thread.FBS.pop(fp); //申请一个新盘快
		Thread.FBS.update(fp);      //
		fsize+=sizeof(item);       //这里注意执行顺序!!!!  要先申请新盘快,才能写入!!
		addBlock(fp,Bid);
		fileIndex(fp,fsize-sizeof(item));
		fwrite(&item,sizeof(File2I),1,fp);
	}
	this->update(fp);  //写磁盘   因为fsize改变了
}

void INode::freeBlock(FILE* fp){
	int block=fsize/B_size;
	if( fsize%B_size ) block++; //block 为文件所占的盘块数
	fsize=0;  //文件大小设置为0

	for(int i=0;i<4 && block>0;i++){ //直接地址
		Thread.FBS.push(fp,addr[i]);
		block--;
	}
	if( block>0 ){    //一次间址
		for(int i=0;i<B_size/2 && block>0;i++){
			short Bid;
			fseek(fp,addr[4]*B_size+i*2,0);
			fread(&Bid,sizeof(short),1,fp);
			Thread.FBS.push(fp,Bid);
			block--;
		}
		Thread.FBS.push(fp,addr[4]); //**
	}
	if( block>0 ){  //二次间址
		short temp1,temp2;
		for(int i=0;i<B_size/2 && block>0;i++){
			fseek(fp,addr[5]*B_size+i*2,0);
			fread(&temp1,sizeof(short),1,fp);
			for(int j=0;j<B_size/2 && block>0;j++){
				fseek(fp,temp1*B_size+j*2,0);
				fread(&temp2,sizeof(short),1,fp);
				Thread.FBS.push(fp,temp2);
				block--;
			}
			Thread.FBS.push(fp,temp1);
		}
		Thread.FBS.push(fp,addr[5]); //**
	}
	this->update(fp);
	Thread.FBS.update(fp);  //更新下
}

void INode::add(FILE* fp, char *ch, int length){ //将文本ch写入文件
	freeBlock(fp);
	while( length>0 ){
		int temp;
		if( length<B_size ) temp=length;
		else temp=B_size;
		short Bid=Thread.FBS.pop(fp);
		fseek(fp,Bid*B_size,0);
		for(int i=0;i<temp;i++){
			fwrite(ch,sizeof(char),1,fp);
			ch++;
		}
		fsize+=temp;
		length-=temp;
		addBlock(fp,Bid);
	}
	this->update(fp);
	Thread.FBS.update(fp);
}

void INode::readContent(FILE* fp,char *ch){
	for(int h=0;h<this->fsize; ){
		int r;
		if( fsize - h >= B_size ) r=B_size;
		else r=fsize - h;
		fileIndex(fp,h);
		for(int i=0;i<r;i++){
			fread(ch,sizeof(char),1,fp);
			ch++;
		}
		h+=r;
	}
}

struct formatting{ //格式化
	void addUser(){
		FILE *fp=fopen("disk.txt","rb+");
		printf("初始化几个用户,用end end结束\n");
		int num=0;
		Identifier user[10],psw[10];
		while( scanf(" %s %s",user[num].buf, psw[num].buf)!=EOF ){
			if( user[num]=="end" && psw[num]=="end") {
				break;
			}
			num++;
		}
		fwrite(&num,sizeof(int),1,fp);
		fwrite(user,sizeof(Identifier),num,fp);
		fwrite(psw,sizeof(Identifier),num,fp);
		fclose(fp);      //注意要fclose!!!!!!!!!!!!!!!!!!!!否则缓冲区可能各种runtime error!!!!
		puts("写入用户名密码成功");
	}
	void testAddUser(){
		FILE *fp=fopen("disk.txt","rb+");
		int num=0;
		Identifier user[10],psw[10];
		fread(&num,sizeof(int),1,fp);
		fread(user,sizeof(Identifier),num,fp);
		fread(psw,sizeof(Identifier),num,fp);
		fclose(fp);
	}
	void initFIStack(){
		FILE *fp=fopen("disk.txt","rb+");
		FIStack FIS;
		int num=IB_num*B_size / sizeof(INode);
		for(int i=num-1;i>=0;i--){
			FIS.push(fp,i);
		}
		fseek(fp, B_size ,0);
		fwrite(&FIS,sizeof(FIStack),1,fp);
		fclose(fp);
		printf("空闲i节点号栈初始化结束!\n");
	}
	void testFIStack(){ //不改变文件内容的
		FILE *fp=fopen("disk.txt","rb+");
		FIStack FIS;
		fseek(fp, B_size ,0);
		fread(&FIS,sizeof(FIStack),1,fp);
		int num=IB_num*B_size / sizeof(INode);
		int trace,count=0;
		while( true ){
			trace=FIS.pop(fp);
			printf("%3d got! ",trace);
			count++;
			if( count%8==0 ) puts("");
			if( trace==num-1) break;
		}
		fclose(fp);
		puts("");
	}
	void initFBStack(){
		FILE *fp=fopen("disk.txt","rb+");
		FBStack FBS;
		for(int i=B_num-1;i>=2+IB_num;i--){
			FBS.push(fp,i);
		}
		fseek(fp, B_size+sizeof(FIStack) ,0);
		fwrite(&FBS,sizeof(FBStack),1,fp);
		fclose(fp);
		printf("空闲盘块号栈初始化结束!\n");
	}
	void testFBStack(){  //不改变文件内容的
		FILE *fp=fopen("disk.txt","rb+");
		FBStack FBS;
		fseek(fp, B_size+sizeof(FIStack) ,0);
		fread(&FBS,sizeof(FBStack),1,fp);
		int trace,count=0;
		while( true ){
			trace=FBS.pop(fp);
			printf("%3d got! ",trace);
			count++;
			if( count%8==0 ) puts("");
			if( trace==B_num-1) break;
		}
		fclose(fp);
		puts("");
	}
	void initHomeDir(){
		FILE *fp=fopen("disk.txt","rb+");
		FIStack fis;
		fis.init(fp);
		INode val;
		val.init(0,true,0,"");
		int id=fis.pop(fp);
		val.update(fp);
		//printf("home目录i节点编号为： %d\n",id);
		fis.update(fp);
		fclose(fp);
	}
	void testHomeDir(){
		FILE *fp=fopen("disk.txt","rb+");
		INode val;
		fseek(fp,2*B_size,0);
		fread(&val,sizeof(INode),1,fp);
		fclose(fp);
	}
}format;

void TestDisk(){
	bool needC=false; //need creat a disk ?
	FILE *fp=fopen("disk.txt","rb+");
	if( fp==NULL ) needC=true;
	else{
		fseek(fp,0,2);
		if( ftell(fp) != B_num*B_size) needC=true;
		fclose(fp);
	}
	if( needC ){
		puts("Creating a virtual disk! Please wait a minute...");
		fp=fopen("disk.txt","wb");
		char ch='0';
		for(int i=0;i<B_num*B_size;i++) fwrite(&ch,sizeof(char),1,fp);
		fclose(fp);
		puts("Done");
	}
}

void again(){
	TestDisk();
	format.addUser();
	format.testAddUser();
	format.initFIStack();

	format.initFBStack();

	format.initHomeDir();
	format.testHomeDir();
}

int main(){
	//again();
	format.testFIStack();
	format.testFBStack();
	Thread.systemInitial();
	Thread.run();
	return 0;
}