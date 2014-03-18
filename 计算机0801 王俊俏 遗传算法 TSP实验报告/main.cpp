/*
Problem: TSP
Algorithm: Genetic Algorithm
Ahthor: 计算机0801 王俊俏
*/
#include<glut.h>   //需要配置好glut才能编译运行这段代码
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<algorithm>
#include<vector>
using namespace std;

typedef pair<double,double> Point;
typedef vector< Point > VP; 
VP city;           //TSP问题的点
vector<int> permut;//结果排列

///********************************************************
void draw(){  //glut 回调函数
	double maxX=-100000,minX=-maxX;  
	double maxY=-100000,minY=-maxY;
	for(int i=0;i<city.size();i++){
		maxX=max(maxX,city[i].first);
		minX=min(minX,city[i].first);
		maxY=max(maxY,city[i].second);
		minY=min(minY,city[i].second);
	}
	double aveX=(minX+maxX)/2, _X=1.2*(aveX-minX);
	double aveY=(minY+maxY)/2, _Y=1.2*(aveY-minY);  //等比例缩放

	glClearColor(1.0, 1.0 , 1.0, 0); //白板
	glClear(GL_COLOR_BUFFER_BIT); //清位
	glPointSize(10); //设置点的大小,这个必须在模式选择之前
	glLineWidth(5);  //设置线宽

	glBegin(GL_POINTS);    //画点
	for(int i=0;i<city.size();i++){
		glColor3f(1,0,0);
		double x=(city[i].first-aveX)/_X;
		double y=(city[i].second-aveY)/_Y;
		glVertex2f(x,y);
	}
	glEnd();

	glBegin(GL_LINE_LOOP); //画线
	for(int i=0;i<city.size();i++){
		glColor3f(0,1,0);
		double x=(city[ permut[i] ].first- aveX)/_X; //permutation
		double y=(city[ permut[i] ].second-aveY)/_Y;
		glVertex2f(x,y);
	}
	glEnd();

	glutSwapBuffers();
}
void OpenGLInit(){ //初始化OpenGL
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutInitDisplayString("double rgb depth>=24");//depth>=24不能有空格
	glutCreateWindow("OpenGL绘图界面 --TSP问题");
}////***********************以上是计算机图像相关***********************

double getDouble(int len=2){ //获得一个长度为len的double,0~1
	double ret=0, mul=1;
	for(int i=1;i<=len;i++){
		mul*=0.1;
		ret+=rand()%10 * mul;
	}
	return ret;
}
inline double getDis(const Point &p1,const Point &p2){ //计算两点距离
	return sqrt( (p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second) );
}
void roll(vector<int> &v,int src,int des){//把下标为src的翻到des后面一个
	if( src>des ){
		while( src!=des+1 ){
			swap(v[src],v[src-1]);
			src--;
		}
	}else{
		while( src!=des ){ //因为前面一位空了
			swap(v[src],v[src+1]);
			src++;
		}
	}
}

struct Individual{ //个体类
	vector<int> v; //染色体,是0~n-1的一个全排列
	double dis, fit; //适应度函数值
	Individual(){}
	Individual(vector<int> v){
		this->v=v;	
	}
	void calFitness(){ //适应度函数值为距离和的倒数
		dis=0;
		for(int i=0;i<v.size();i++){
			int id1=v[i],id2=v[(i+1)%v.size()];
			dis+=getDis(city[id1],city[id2]);
		}
		fit=1.0/dis;
	}
	Individual cross(Individual &b)const{ //交叉,产生下一代个体,这里交叉采用顺序插入交叉算子
		vector<int> nxt=v;
		for(int i=0;i<b.v.size();i++){
			int val1=b.v[i], val2=b.v[ (i+1)%b.v.size() ];
			int j=0,m=0;
			while( nxt[j] != val1 ) j++;
			while( nxt[m] != val2 ) m++;
			//下面判断m是不是应该在j后面一位   这里无论怎么选择都用到了双亲的优质基因*****
			Point pj=city[nxt[j]] ,pj1, pm=city[nxt[m]],pm1,pm_1;
			if( j==nxt.size()-1 ) pj1=city[nxt[0]]; else pj1=city[nxt[j+1]];
			if( m==nxt.size()-1 ) pm1=city[nxt[0]]; else pm1=city[nxt[m+1]];
			if( m==0 ) pm_1=city[nxt[ nxt.size()-1]]; else pm_1=city[nxt[m-1]];
			double cur=getDis(pj,pj1)+getDis(pm_1,pm)+getDis(pm,pm1);
			double xor=getDis(pj,pm)+getDis(pm,pj1)+getDis(pm_1,pm1);
			if( cur > xor ) roll(nxt,m,j); //如果确实比现在的要好
		}
		return Individual(nxt);
	}
	void mutate(double pm){ //变异,传入变异概率
		for(int i=0;i<v.size()/2;i++){ //次数***
			if( getDouble(4) < pm ){
				int id1,id2;  //随机选两个交换下
				do{
					id1=rand()%v.size();
					id2=rand()%v.size();
				}while( id1==id2 );
				swap(v[id1],v[id2]);
			}
		}
	}
	bool operator<(const Individual &b)const{ //比较
		return dis < b.dis;
	}
};

struct Population{ //种群类
	vector<Individual> pop;
	double pc,pm;
	Population(int N=10,int S=20,double pc=0.85, double pm=0.05){ //城市数目, 种群数目
		this->pc=pc, this->pm=pm; //参数***
		vector<int> v(N);
		for(int i=0;i<N;i++) v[i]=i;
		for(int i=0;i<S;i++){ //初始化种群S个
			for(int j=0;j<30*N;j++){ //随机交换下
				int id1=rand()%N;
				int id2=rand()%N;
				swap(v[id1],v[id2]);
			}
			pop.push_back(Individual(v));
			pop[i].calFitness();
		}
	}
	/*
	void getNext(){ //下一代,采用轮盘赌选择
		vector<Individual> npop;
		double sumFit=0,last=0;
		//sort(pop.begin(),pop.end());
		for(int i=0;i<pop.size();i++){ //产生下一代,2倍数量
			int a=i,b=(i+1)%pop.size(); 
			if( getDouble(4) < pc ) //以一定的概率交叉
				npop.push_back(pop[a].cross(pop[b]));
			else 
				npop.push_back(pop[a]);
			npop[ npop.size()-1 ].calFitness();
			sumFit+=npop[ npop.size()-1 ].fit;

			if( getDouble(4) < pc ) //以一定的概率交叉
				npop.push_back(pop[b].cross(pop[a]));
			else 
				npop.push_back(pop[b]);
			npop[npop.size()-1].calFitness();
			sumFit+=npop[npop.size()-1].fit;
		}
		for(int i=0;i<npop.size();i++){ //轮盘
			npop[i].fit/=sumFit;
			npop[i].fit+=last;
			last=npop[i].fit;
		}
		int S=pop.size(); pop.clear();
		for(int i=0;i<S;i++){  //轮盘赌选择
			double t=getDouble(4);
			int sel=0;
			while( npop[sel].fit < t ) sel++;
			pop.push_back(npop[sel]);
		}
	}
	*/
	void getNext(){ //下一代,采用爆炸性繁殖,选择优质后代
		int mul=20;
		vector<Individual> npop(mul*pop.size());
		for(int i=0;i<pop.size()*mul;i++){ //产生下一代
			int a,b; 
			do{
				a=rand()%pop.size();
				b=rand()%pop.size();
			}while( a==b );
			if( getDouble(4) < pc ) //以一定的概率交叉
				npop[i]=pop[a].cross(pop[b]);
			else 
				npop[i]=pop[a];
			npop[i].calFitness();
		}
		sort(npop.begin(),npop.end());
		//选择最好的
		int S=pop.size(); pop.clear();
		for(int i=0;i<S;i++){
			pop.push_back(npop[i]);
		}
	}
	Individual getBest(){ //获得最好的个体
		int sel; double ma=0;
		for(int i=0;i<pop.size();i++){
			pop[i].calFitness();
			if( pop[i].fit > ma ){
				ma=pop[i].fit;
				sel=i;
			}
		}
		return pop[sel];
	}
};

int main(){
	srand(time(NULL)); //没有这个每次的运行结果将相同
	int N,T,S;
	double pc,pm;
	printf("注意: 此系统数据都是随机生成的,所以每次运行的城市坐标可能不同,结果也可能不同!!\n\n");
	printf("请输入TSP问题城市数目,GA算法迭代次数,种群大小,交叉概率,变异概率\n");
	while(cin>>N>>T>>S>>pc>>pm){ 
		clock_t Time=clock();
		city.clear();
		printf("城市坐标如下:\n");
		for(int i=0;i<N;i++){ //坐标随机生成
			double a=rand()%5000, b=rand()%5000;
			city.push_back(Point(a,b));
			printf("(%5.0lf,%5.0lf)\n",a,b);
		}
		double mi=1000000000.0; //记录最小距离和
		Population p(N,S,pc,pm); //产生种群
		for(int i=0;i<T;i++){   //迭代T次
			p.getNext();
			mi=min(mi,p.getBest().dis); //更新最小距离和
		}
		permut=p.getBest().v;  //终止状态种群的最佳个体
		printf("路径为: ");
		for(int i=0;i<permut.size();i++){
			if( i!=0 ) printf("-->");
			printf("%d",permut[i]);
			if( i==permut.size()-1 ) puts("");
		}
		printf("计算中出现过的最小距离和为: %.1lf  最终距离和为: %.1lf\n",mi,p.getBest().dis);
		printf("计算耗时: %.3lf 秒\n",(clock()-Time)/1000.0);

		OpenGLInit();
		glutDisplayFunc(draw);
		glutMainLoop();
	}
}
/*
测试数据: (一行一组,分别表示城市数,迭代次数,种群规模,交叉率,变异率)
10 50 50 0.9 0.05
20 100 50 0.9 0.05
30 300 50 0.9 0.05
40 400 50 0.9 0.05
50 500 100 0.9 0.05
75 500 100 0.9 0.05
75 1000 100 0.9 0.05
*/