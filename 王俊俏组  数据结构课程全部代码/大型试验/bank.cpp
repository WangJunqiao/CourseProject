#include<iostream>
#include<queue>//设置队列  两个一班队列  一个优先队列
#include<iomanip>//设置输出格式

using namespace std;

struct Case//有关事件
{
	int arrival,last,money,num;
	Case(int _a=0,int _l=0,int _m=0,int _i=0):arrival(_a),last(_l),money(_m),num(_i){};//构造函数
	friend bool operator<(const Case &a,const Case &b)//用于优先队列的比较
	{
		return a.money < b.money;//取钱为关键值
	}
};


int main()
{
	queue<Case> list;//存放将要发生的事件（人进银行的事件）   和下面的为两个一般队列
	queue<Case> q1;  //银行里的第一个队列（等待被服务）
	priority_queue<Case> q2; //银行里的第二个队列（等待银行贷款）

	int arrival,last,money,num=1; //num记录的是第几号客户
	cout<<"请输入今日银行的事件列表（客户的达到时间，交易时间和钱数）.\n";
	while(cin>>arrival>>last>>money)//读入一整天的业务（按照时间的先后）
		list.push( Case(arrival,last,money,num++) ); //进入银行的顺序

	int currenTime=0;
	int totalMoney=10000;

	Case temp,temp2,temp3;//临时变量
	while(currenTime<600)
	{
		if(list.empty())//如果没有客户从外面进入银行了
			break;
		temp=list.front();//取未进入的银行的第一个人 
		list.pop();//从队首删除
		cout<<"Time "<<setw(3)<<temp.arrival<<": "<<temp.num<<"号客户进入银行."<<endl;

		q1.push(temp);//排到第一个队列后面
		currenTime=temp.arrival;//把当前时间移到这个客户的到达时间（离散）

		while(!q1.empty() && currenTime<600)//只要第一个队列不空且时间还没下班，就可以服务
		{
			temp=q1.front();//取出排在第一个队列最前面的一个（等待被处理的人） 
			q1.pop();
			
			if(temp.money>=0)//如果是存钱的
			{
				cout<<"Time "<<setw(3)<<currenTime<<": 柜台开始为"<<temp.num<<"号客户服务."<<endl;
				currenTime+=temp.last;  //柜台在为他服务，把当前时间移到他结束时

				while(!list.empty() && list.front().arrival <=currenTime)//在服务期间可能有人进入银行
				{
					temp2=list.front();
					list.pop();
					cout<<"Time "<<setw(3)<<temp2.arrival<<": "<<temp2.num<<"号客户进入银行."<<endl;
					q1.push(temp2);
				}//考虑在为前一个人服务期间是否有新人进入银行

				totalMoney+=temp.money;//银行总钱数增加
				cout<<"Time "<<setw(3)<<currenTime<<": "<<temp.num<<"号客户存入银行"<<temp.money<<"元，离开银行"<<endl;

				while(!q2.empty() && q2.top().money+totalMoney>=0 && currenTime<=600)//银行钱多了就看能不能贷款给客户
				{
					temp2=q2.top();
					q2.pop();
					cout<<"Time "<<setw(3)<<currenTime<<": 柜台开始为"<<temp2.num<<"号客户服务"<<endl;

					currenTime+=temp2.last;//银行当前时间跳动
					while(!list.empty() && list.front().arrival <=currenTime)//贷款期间是否有人进银行
					{
						temp3=list.front();
						list.pop();
						cout<<"Time "<<setw(3)<<temp3.arrival<<": "<<temp3.num<<"号客户进入银行."<<endl;
						q1.push(temp3);
					}
					totalMoney+=temp2.money;

					cout<<"Time "<<setw(3)<<currenTime<<": "<<temp2.num<<"号客户从银行取走"<<-temp2.money<<"元，离开银行"<<endl;
				}
			}
			else//如果是要取钱的
			{
				if(totalMoney+temp.money>=0)
				{
					cout<<"Time "<<setw(3)<<currenTime<<": 柜台开始为"<<temp.num<<"号客户服务."<<endl;
					currenTime+=temp.last;

					while(!list.empty() && list.front().arrival <=currenTime)//贷款期间有人进银行吗
					{
						temp2=list.front();
						list.pop();
						cout<<"Time "<<setw(3)<<temp2.arrival<<": "<<temp2.num<<"号客户进入银行."<<endl;
						q1.push(temp2);
					}
					totalMoney+=temp.money;
					cout<<"Time "<<setw(3)<<currenTime<<": "<<temp.num<<"号客户从银行取走"<<-temp.money<<"元，离开银行"<<endl;
				}
				else
				{
					cout<<"Time "<<setw(3)<<currenTime<<": 由于银行钱不够，"<<temp.num<<"号客户排入第二个队列等候."<<endl;
					q2.push(temp);
				}
			}
		}
	}

	while(!q1.empty())
	{
		temp=q1.front();
		q1.pop();
		cout<<"Time "<<setw(3)<<currenTime<<": 由于银行要关闭"<<temp.num<<"号客户离开银行."<<endl;
	}
	while(!q2.empty())
	{
		temp=q2.top();
		q2.pop();
		cout<<"Time "<<setw(3)<<currenTime<<": 由于银行要关闭"<<temp.num<<"号客户离开银行."<<endl;
	}


	return 0;
}
