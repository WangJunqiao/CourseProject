#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<vector>
#include"sort.h"
using namespace std;

#define maxn 5000
#define NeedPrint 0


template<class T>
void print(vector<T> &v)//打印输出数组的元素
{
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<' ';
}

template<class T>
void get_date(vector<T> &v)//生成数据
{
	int n=v.size();
	for(int i=0;i<n;i++)
		v[i]=(rand()*rand())%(10*maxn);
	return;
}


template<class T>
void test_Bubble_sort(vector<T> v)
{
	cout<<"Bubble Sort :\n";

	clock_t t=clock();
	Bubble_sort(v);

	cout<<"time used : "<<(clock()-t)<<"ms"<<endl;
	//cout<<"swap times : "<<swap_t<<endl;

	if(NeedPrint)
		print(v);
	cout<<endl;
}

template<class T>
void test_Select_sort(vector<T> v)
{
	cout<<"Select Sort :\n";

	clock_t t=clock();
	Select_sort(v);

	cout<<"time used : "<<(clock()-t)<<"ms"<<endl;

	if(NeedPrint)
		print(v);
	cout<<endl;
}

template<class T>
void test_Insert_sort(vector<T> v)
{
	cout<<"Insert Sort :\n";

	clock_t t=clock();
	Insert_sort(v);

	cout<<"time used : "<<(clock()-t)<<"ms"<<endl;

	if(NeedPrint)
		print(v);
	cout<<endl;
}

template<class T>
void test_Shell_sort(vector<T> v)
{
	cout<<"Shell Sort :\n";

	clock_t t=clock();
	Shell_sort(v);

	cout<<"time used : "<<(clock()-t)<<"ms"<<endl;

	if(NeedPrint)
		print(v);
	cout<<endl;
}


template<class T>
void test_Count_sort(vector<T> v)
{
	cout<<"Count Sort :\n";

	clock_t t=clock();
	Count_sort(v);

	cout<<"time used : "<<(clock()-t)<<"ms"<<endl;

	if(NeedPrint)
		print(v);
	cout<<endl;
}

template<class T>
void test_Merge_sort(vector<T> v)
{
	cout<<"Merge Sort :\n";

	clock_t t=clock();
	Merge_sort(v);

	cout<<"time used : "<<(clock()-t)<<"ms"<<endl;

	if(NeedPrint)
		print(v);
	cout<<endl;
}


template<class T>
void test_Quick_sort(vector<T> v)
{
	cout<<"Quick Sort :\n";

	clock_t t=clock();
	Quick_sort(v);

	cout<<"time used : "<<(clock()-t)<<"ms"<<endl;

	if(NeedPrint)
		print(v);
	cout<<endl;
}


template<class T>
void test_Radix_sort(vector<T> v)
{
	cout<<"Radix Sort :\n";

	clock_t t=clock();
	Radix_sort(v);

	cout<<"time used : "<<(clock()-t)<<"ms"<<endl;

	if(NeedPrint)
		print(v);
	cout<<endl;
}


template<class T>
void test_Heap_sort(vector<T> v)
{
	cout<<"Heap Sort :\n";

	clock_t t=clock();
	Heap_sort(v);

	cout<<"time used : "<<(clock()-t)<<"ms"<<endl;

	if(NeedPrint)
		print(v);
	cout<<endl;
}

int main()
{
	cout<<"测试数据的数组大小为"<<maxn<<"\n\n";

	vector<int> v(maxn);

	cout<<"test 1: 对完全无序的数组进行排序:"<<endl;    
	get_date(v);
	test_Bubble_sort(v);
	test_Select_sort(v);
	test_Insert_sort(v);
	test_Shell_sort(v);
	test_Count_sort(v);
	test_Merge_sort(v);
	test_Quick_sort(v);
	test_Radix_sort(v);
	test_Heap_sort(v);
	return 0;
}