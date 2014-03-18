#ifndef STACK_H
#define STACK_H

template<class T>
class stack
{
public:
	virtual void deleteAllValues()=0;
	virtual int isEmpty()const=0;
	virtual T pop()=0;
	virtual void push(T value)=0;
	virtual T top()const=0;
};

#include<list>
#include<iostream>
using namespace std;

template<class T>
class stackList:public stack<T>
{
protected:
	list<T> data;
public:
	stackList();
	stackList(const stackList<T> &v);

	virtual void deleteAllValues();
	virtual int isEmpty()const;
	virtual T pop();
	virtual void push(T value);
	virtual T top()const;
};


template<class T>
stackList<T>::stackList():data(){};

template<class T>
stackList<T>::stackList(const stackList<T> &v):data(v.data){};

template<class T>
void stackList<T>::deleteAllValues()
{
	while(!data.empty())
		data.pop_front();
}


template<class T>
int stackList<T>::isEmpty()const
{
	return data.empty();
}

template<class T>
T stackList<T>::pop()
{
	T result=data.front();
	data.pop_front();
	return result;
}


template<class T>
void stackList<T>::push(T value)
{
	data.push_front(value);
}

template<class T>
T stackList<T>::top()const
{
	return data.front();
}

#endif