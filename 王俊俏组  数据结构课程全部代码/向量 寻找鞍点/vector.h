#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
#include<cassert>
using namespace std;


template<typename T>
class vector
{
	private:
		T *head;
		unsigned size;
	public:
		vector(unsigned ele_num=10);
		vector(unsigned ele_num,T ini_value);
		vector(const vector<T> & source);
		virtual ~vector();//虚函数，运行中的多态

		T& operator [] (unsigned index)const;
		vector<T>& operator = (const vector<T> &right);
		bool operator == (const vector<T> &v)const;
		
		unsigned length()const;//原来接口名和数据成员名不能一样的，size不可以

		unsigned set_size(unsigned ele_num);
		unsigned set_size(unsigned ele_num,T ini_value);

		void remove(T value);

		friend ostream& operator << (ostream &o,const vector<T> &v);//友元无const
};

template<typename T>
vector<T>::vector(unsigned ele_num)
{
	head=new T[ele_num];
	assert(head!=NULL);
	size=ele_num;
}

template<typename T>
vector<T>::vector(unsigned ele_num,T ini_value)
{
	head=new T[ele_num];
	assert(head!=NULL);
	size=ele_num;
	for(int i=0;i<size;i++)
		head[i]=ini_value;
}

template<typename T>
vector<T>::vector(const vector<T> &source)
{
	size=source.size;
	head=new T[size];
	assert(head!=NULL);
	memcpy(head,source.head,size*sizeof(T));
}

template<typename T>
vector<T>::~vector()
{
	delete[] head;
	head=NULL;
	size=0;
}

template<typename T>
T& vector<T>::operator [] (unsigned index)const
{
	assert(index<size);
	return head[index];
}

template<typename T>
unsigned vector<T>::length()const
{
	return size;
}

template<typename T>
vector<T>& vector<T>::operator = (const vector<T> &right)
{
	if(size!=right.size)
	{
		size=right.size;
		delete[] head;
		head=new T[size];
		assert(head!=NULL);
	}
	memcpy(head,right.head,size*sizeof(T));
	return *this;
}

template<typename T>
unsigned vector<T>::set_size(unsigned ele_num)
{
	if(size!=ele_num)
	{
		T *temp=new T[ele_num];
		assert(temp!=NULL);
		unsigned t=size<ele_num?size:ele_num;
		memcpy(temp,head,t*sizeof(T));
		delete[] head;
		head=temp;
		size=ele_num;
	}
	return size;
}

template<typename T>
unsigned vector<T>::set_size(unsigned ele_num,T ini_value)
{
	if(size!=ele_num)
	{
		size=ele_num;
		delete[] head;
		head=new T[size];
		assert(head!=NULL);
	}
	for(int i=0;i<size;i++)
		head[i]=ini_value;
	return size;
}
// VC 6.0对某些操作符的重载貌似有bug，都友元了还不能访问私有数据
template<typename T>
ostream& operator << (ostream &o,const vector<T> &v)
{
	o<<v[0];
	for(int i=1;i<v.length();i++)
		o<<' '<<v[i];
	return o;
}
//下面这段在VC 8及以上版本可以通过
/*
template<typename T>
ostream& operator << (ostream &o,const vector<T> &v)
{
	o<<v.head[0];
	for(int i=1;i<v.size;i++)
		o<<' '<<v.head[i];
	return o;
}
*/

template<typename T>
void vector<T>::remove(T value)
{
	int index=0;
	for(int i=0;i<size;i++)
		if(head[i]!=value)
			head[index++]=head[i];
	size=index;
}

template<typename T>
bool vector<T>::operator == (const vector<T> &v)const
{
	if(size!=v.size)
		return false;
	for(int i=0;i<size;i++)
		if(head[i]!=v[i])
			return false;
	return true;
}
#endif