#include<iostream>
#include"BST.h"
#include<fstream>
#include<string>
#include<cstdlib>

using namespace std;

struct Item
{
	string name;
	string phoneNumber;
	
	Item(string a="",string b=""):name(a),phoneNumber(b){};
	
	bool operator<(const Item &b)
	{
		return name < b.name;
	}
	bool operator==(const Item &b)
	{
		return name == b.name;
	}
	friend ostream& operator<<(ostream &out,const Item &b)
	{
		return out<<"name: "<<b.name<<" phoneNumber: "<<b.phoneNumber;
	}
};

void work(BST<Item> &bst,int choice)
{
	string name,phoneNumber;
	if(choice==1)
	{
		cout<<"请输入要新建的姓名和电话号码，以#号结束.\n";
		while(cin>>name)
		{
			if(name=="#")
				break;
			cin>>phoneNumber;
			bst.Insert(Item(name,phoneNumber));
		}
	}
	else if(choice==2)
	{
		cout<<"请输入要删除的人的姓名，以#号结束.\n";
		while(cin>>name)
		{
			if(name=="#")
				break;
			bst.Remove(Item(name));
		}
	}
	else if(choice==3)
	{
		cout<<"请输入要查询的人的姓名，以#号结束.\n";
		Node<Item> *p;
		while(cin>>name)
		{
			if(name=="#")
				break;
			p=bst.Find(Item(name));
			if(p==NULL)
				cout<<"对不起，数据库中没有这个人的信息.\n";
			else
				cout<<p->value<<endl;
		}
	}
}

int main()
{
	BST<Item> bst;
	cout<<"欢迎光临DD小型通讯录系统.\n\n";
	
	int choice;
	do
	{
		cout<<"新建联系人请按1，删除联系人请按2，查询联系人电话请按3，退出请按0.\n";
		cin>>choice;
		if(choice==0)
			exit(0);
		else
			work(bst,choice);
	}while(1);
	
	ofstream fout("out.txt");
	
	bst.Print(fout);
}
