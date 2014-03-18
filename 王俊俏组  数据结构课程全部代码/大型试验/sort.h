#ifndef SORT_H
#define SORT_H

#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;

//冒泡排序，思想：两两比较，大的往后
template<class T>
void Bubble_sort(vector<T> &v)
{
	int num=v.size();
	for(int c=1;c<num;c++)
	{
		for(int i=0;i<num-c;i++)
		{
			if(v[i]>v[i+1])
			{
				swap(v[i],v[i+1]);
			}
		}
	}
}

//选择排序，思想：选最小的放在“首位”
template<class T>
void Select_sort(vector<T> &v)
{
	int ind,mi,n=v.size(),inf=0x7fffffff;
	for(int i=0;i<n-1;i++)//要处理的位置
	{
		mi=inf;
		for(int j=i;j<n;j++)//选择最小值的位置
		{
			if(v[j]<mi)
			{
				ind=j;
				mi=v[j];
			}
		}
		swap(v[i],v[ind]);//调换
	}
}

//插入排序，思想：前面k个数是排好了的，插入第k+1个
template<class T>
void Insert_sort(vector<T> &v)
{
	int n=v.size();
	T temp;
	for(int i=1;i<n;i++)//把第k个插入到前面k-1个排好的队列
	{
		temp=v[i];
		int j;
		for(j=i-1;j>=0 && v[j]>temp;j--)//K元素插入的过程
		{
			v[j+1]=v[j];
		}
		v[j+1]=temp;
	}
}


//希尔排序 思想：变跨度插入排序，对跨度二分，每次交换减少多个逆序对
template<class T>
void Shell_sort(vector<T> &v)
{
	int n=v.size();
	T temp;
	for(int len=n>>1;len>0;len>>=1)//跨度当跨度为1的时候就是一般的插入排序
	{
		for(int i=len;i<n;i++)
		{
			temp=v[i];
			int j;
			for(j=i-len;j>=0 && v[j]>temp;j-=len)//插入的过程
			{
				v[j+len]=v[j];
			}
			v[j+len]=temp;
		}
	}
}


//计数排序 思想：计算某个数值的排名
template<class T>
void Count_sort(vector<T> &v)
{

	int ma=0,i;
	for(i=0;i<v.size();i++)//算最大的数值
		ma=(ma>v[i]?ma:v[i]);

	vector<int> sum(ma+3,0);//计算排名的向量
	vector<T> temp(v);

	int len=v.size();
	for(i=0;i<len;i++)//计算放入相应的位置+1
	{
		//if(v[i]>=ma)
			//system("pause");
		sum[v[i]]++;
	}
	for(i=1;i<=ma;i++)//计算排名
		sum[i]=sum[i]+sum[i-1];

	for(i=len-1;i>=0;i--)//从后往前按照排名放入
	{
		v[ sum[temp[i]]-1  ]=temp[i];
		sum[temp[i]]--;
	}
}


//归并排序 思想：分治
template<class T>
void Merge_sort(vector<T> &v,int left=-1,int right=-1)
{
	if(left==-1)
		left=0,right=v.size()-1;
	if(left==right)
		return;
	int mid=(left+right)>>1;

	//分治
	Merge_sort(v,left,mid);
	Merge_sort(v,mid+1,right);

	//一下是合并操作
	vector<T> L(mid-left+1);
	vector<T> R(right-mid);
	int ind=0,i;
	for(i=left;i<=mid;i++)
		L[ind++]=v[i];
	ind=0;
	for(i=mid+1;i<=right;i++)
		R[ind++]=v[i];

	ind=left;
	int lp=0,rp=0;
	while(lp<L.size() || rp<R.size())
	{
		if(lp>=L.size())
			v[ind++]=R[rp++];
		else if(rp>=R.size())
			v[ind++]=L[lp++];
		else if(L[lp]<=R[rp])
			v[ind++]=L[lp++];
		else
			v[ind++]=R[rp++];
	}
}


//快速排序 思想：选取一个基准点，每次把待拍数据几近二分
template<class T>
void Quick_sort(vector<T> &v,int low=-1,int high=-1)
{
	if(low==-1)//是不是第一次调用，如果是第一次调用使用默认参数，以后调用非负的整数，-1是负数的代表
		low=0,high=v.size()-1;
	if(low>=high)
		return ;
	int midIndex=partion(v,low,high);
	Quick_sort(v,low,midIndex-1);//调用自己 递归
	Quick_sort(v,midIndex+1,high);
}

template<class T>//左右分   左小右大
int partion(vector<T> &v,int low,int high)
{
	int _ind=low+rand()%(high-low);
	swap(v[low],v[_ind]);
	int pivot=v[low];

	while(low<high)
	{
		while(low<high && v[high]>=pivot)
			high--;
		if(low<high)
		{
			v[low]=v[high];
			low++;
		}

		while(low<high && v[low]<=pivot)
			low++;
		if(low<high)
		{
			v[high]=v[low];
			high--;
		}
	}
	v[low]=pivot;
	return low;
}


//基数排序 思想：每次用其他排序方法按照某一位进行排序（这里采用计数排序）
template<class T>
void Radix_sort(vector<T> &v)
{
	int d[10];
	d[0]=1;
	for(int i=1;i<10;i++)
		d[i]=10*d[i-1];

	int num,len=v.size(),sum[10],_time=1;
	while(1)
	{
		vector<T> temp(v);
		memset(sum,0,sizeof(sum));
		for(int i=0;i<len;i++)
		{
			num=temp[i]%d[_time]/d[_time-1];
			sum[num]++;
		}
		for(int i=1;i<10;i++)
			sum[i]+=sum[i-1];

		if(sum[0]==len)
			break;
		for(int i=len-1;i>=0;i--)
		{
			num=temp[i]%d[_time]/d[_time-1];
			v[ --sum[num] ]=temp[i];//减掉1的
		}
		_time++;
	}
}

//堆排序 思想：利用最大堆的性质
template<class T>
void max_Heapify(vector<T> &v,int maxIndex,int i)//使之最大堆化
{
	int largest=i;

	int left= (i<<1)+1;   //left是乘以2+1，因为起点是0，注意下
	int right= (i<<1) +2;

	if(left<=maxIndex && v[left]>v[largest])
		largest=left;
	if(right<=maxIndex && v[right]>v[largest])
		largest=right;

	if(largest!=i)
	{
		swap(v[i],v[largest]); //传地址******************
		max_Heapify(v,maxIndex,largest);
	}
}

template<class T>
void Heap_sort(vector<T> &v)
{
	int len=v.size();
	for(int i=len/2+1;i>=0;i--)
		max_Heapify(v,len-1,i);

	for(int _time=1;_time<len;_time++)
	{
		swap(v[len-_time],v[0]);
		max_Heapify(v,len-_time-1,0);
	}
}

#endif
