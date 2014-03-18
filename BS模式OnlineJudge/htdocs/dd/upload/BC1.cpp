#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<algorithm>
#include<stdio.h>
#include<stdarg.h>   // char *fmt,... 支持
#include<set>
//#include"BC3.cpp"
//#include<pthread.h>
using namespace std;

//C语言学习

/*
void add(char* fm,...){
	va_list args;
	va_start(args,fm);
	
	vaend(args);
}
*/
/*
把局部变量改变为静态变量后是改变了它的存储方式即改变了它的生存期
把全局变量改变为静态变量 后是改变了它的作用域，限制了它的使用范围
*/

void exit1(){
	puts("exit function 1 called");
}
void exit2(){
	puts("exit function 2 called");
}

void* f(void *intval){
	printf("这个数是%d\n",*(int*)intval);
	return NULL;
}

void myPrintf(int n,...){ //需要 <stdarg.h>来支持
	va_list ap; //va_list是指向堆栈中地址的指针类型
	va_start(ap,n); //让ap指向堆栈中n(第一个个可变参数)的地址
	//vprintf(fmt,args);
	for(int i=0;i<n;i++){
		char *buf=va_arg(ap,char*); //指向下一个地址,并返回值
		printf("%d %s\n",i+1,buf);
	}
	va_end(ap);  //结束
}


union myUnion{
	char ch;
	int val;
	short s;
	long long L;
};

void test_union(){
	myUnion u;
	u.L=0x12131415161718LL;
	printf("int: %x\n",u.val);
	printf("char: %x\n",(int)u.ch);
	printf("short: %x\n",(int)u.s);
	printf("long long: %llx\n",u.L);
	u.s=(short)0x2222;  printf("changed u.s scope!\n");
	printf("int: %x\n",u.val);
	printf("char: %x\n",(int)u.ch);
	printf("short: %x\n",(int)u.s);
	printf("long long: %llx\n",u.L);
	//union结构体的各个变量共享一块内存,都是从同一个低位开始占据一定的字节数
	//这个test说明内存里存放一个long long的时候是 (高位在内存的高位,低位在内存的低位) 这样子存放的.
}

#define SRC_LOCATION  __FILE__,__LINE__
void printLine(char *file,int line){
	printf("文件定位测试:  file:%s line:%d\n",file,line);
}

int main(){
	test_union();
	
	//printf("%s\n",getenv("path"));  获取环境变量的值
	cout<<sizeof(char*)<<endl;
	cout<<sizeof(char )<<endl;
	
	atexit(exit1);//堆栈式添加的
	atexit(exit2);
	
	int s=3;
	f(&s);
	
	printLine(SRC_LOCATION);
	
	myPrintf(4,"arg1","arg2","arg3","arg4");
	
	#if defined DDD
	printf("已经定义了DDD\n");
	#else
	printf("没有定义DDD\n");
	#endif
}

/*
	char buf[1000],*ptr=buf;
	gets(buf);
	int a,n;
	while( sscanf(ptr,"%d%n",&a,&n)!=EOF ){
		printf("%d\n",a); ptr+=n;
	}
*/













