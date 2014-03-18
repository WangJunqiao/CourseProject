/*
problem : 8数码问题
Algorithm: A*算法
Author: 计算机0801 王俊俏  2010.11.27
IDE: Visual Studio 2010
*/
#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;

struct PII{ 
	int r,c; 
	PII(int _r=0,int _c=0):r(_r),c(_c){};
};               //用于存放坐标的

struct EIGHT{	//数码的状态类
	int _d[3][3];
	PII _z;    //0的坐标
	int g,h;
	vector<int> path; //搜到这个状态的路径
	
	int getRev()const{ //逆序数
		int a[8],ind=0,i,j,Rev=0;
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if( _d[i][j]!=0 ) 
					a[ind++]=_d[i][j];
			}
		}
		for(i=1;i<8;i++){
			for(j=0;j<i;j++)
				if( a[j] > a[i] ) 
					Rev++;
		}
		return Rev;
	}
	bool getNext(int dir,EIGHT &ns){//移动，返回移动是否成功(下一个状态在引用中传递)
		memcpy(ns._d,_d,sizeof(_d));
		ns.path=path; ns._z=_z;
		int r=_z.r, c=_z.c, nr,nc;
		if( dir==0 ){                       // down
			if( _z.r==2 ) return false;
			nr=r+1, nc=c;
		}else if( dir==1 ){                // left
			if( _z.c==0 ) return false;
			nr=r, nc=c-1;
		}else if( dir==2 ){               // right
			if( _z.c==2 ) return false;
			nr=r, nc=c+1;
		}else{                             // up
			if( _z.r==0 ) return false;
			nr=r-1, nc=c;
		}
		swap(ns._d[r][c],ns._d[nr][nc]);
		ns._z=PII(nr,nc); 
		ns.path.push_back(dir);
		return true;
	}
	int getH(EIGHT &des){ //估价函数2
		PII b[8];
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if( _d[i][j] )
					b[ _d[i][j]-1 ]=PII(i,j);
			}
		}
		int ret=0;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if( des._d[i][j] ){
					int v=des._d[i][j];
					ret+=abs(i-b[v-1].r)+abs(j-b[v-1].c);
				}
			}
		}
		return ret;
	} 
	/*int getH(EIGHT &des){ //估价函数1
		int ret=0;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if( _d[i][j]==0 ) continue;
				if( _d[i][j] != des._d[i][j] ){ //不在位数
					ret++;
				}
			}
		}
		return ret;
	}*/

	void init(int *d){ //用数组初始化
		for(int i=0;i<9;i++){
			_d[i/3][i%3]=d[i];
			if( d[i]==0 ){
				_z.r=i/3, _z.c=i%3;
			}
		}
		this->path.clear();
	}
	int getHash(){     //全排列的完美哈希,复杂度O(n^2),判重用的
		int a[9];
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++) a[3*i+j]=_d[i][j]; 
		}
		int ret=0,mul=1;
		for(int i=1;i<9;i++){
			int rev=0;
			for(int j=0;j<i;j++) if( a[j] > a[i] ) rev++;
			ret+=mul*rev;
			mul*=(i+1);
		}
		return ret;
	}
	void print(int step){ //打印8数码
		printf("step %d:\n%d %d %d\n%d %d %d\n%d %d %d\n",step,
			_d[0][0],_d[0][1],_d[0][2],_d[1][0],_d[1][1],
			_d[1][2],_d[2][0],_d[2][1],_d[2][2]);
	}
	bool operator<(const EIGHT &b)const{ //优先队列中的比较
		return g+h > b.g+b.h;
	}
	bool operator==(const EIGHT &b)const{ //判相等,这里只要3*3的board相等就ok了
		return memcmp(_d,b._d,9*sizeof(int)) == 0;
	}
	
}src,des;

priority_queue< EIGHT > open;
//queue< EIGHT > close;
void trace(vector<int> path){
	EIGHT s=src,t;
	int step=0;
	s.print(step++);
	for(int i=0;i<(int)path.size();i++){
		cout<<"--->"<<endl;
		s.getNext(path[i],t);
		t.print(step++); s=t;
	}
}

bool hash[500000];
void Astar(){
	if( src.getRev()%2 != des.getRev()%2 ){//判解
		puts("unSolvable");
		return;
	}
	vector<int> path;
	fill(hash,hash+500000,false);
	while( !open.empty()) open.pop();
	//while( !close.empty()) close.pop();
	src.g=0,src.h=src.getH(des);
	open.push(src);
	
	int searched=0, visited=0;
	while( true ){
		EIGHT cur=open.top(),nxt;
		open.pop();
		if( cur==des ){
			puts("I find it!");
			path=cur.path;
			
			break;
		}
		for(int i=0;i<4;i++){ //0往4个方向移动
			if( cur.getNext(i,nxt) ){
				nxt.g=0;
				nxt.g=cur.g+1;    
				nxt.h=nxt.getH(des);//改成nxt.g=0就是普通的广搜了
				//nxt.h=0;
				int hh=nxt.getHash();
				if( hash[ hh ] ) continue;
				hash[ hh ]=true;
				open.push(nxt);
				visited++;   //访问过的节点个数+1
			}
		}
		searched++; //搜索过的节点个数+1
		//cout<<searched<<endl;
	}
	trace(path);         //打印搜索的路径
	printf("最短路径%d,访问了%d个状态,搜索了%d个状态\n",path.size(),visited,searched);
}
int main(){
	int d[9]={1,2,3,8,0,4,7,6,5};
	des.init(d);
	while( cin>>d[0] ){
		for(int i=1;i<9;i++) cin>>d[i];
		src.init(d);
		Astar();
	}
}

