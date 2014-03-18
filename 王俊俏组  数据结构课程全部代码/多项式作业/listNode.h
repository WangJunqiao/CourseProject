#ifndef LISTNODE_H
#define LISTNODE_H

#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
class list;

template<class T>
class listIterator;

template<class T>
class listNode
{
	private:
		T value;
		listNode<T> *next;
	public:
		//listNode();
		listNode(T val=0,listNode<T>* p=NULL);
		listNode(const listNode<T> &obj);

        listNode<T>* duplicate()const;
        listNode<T>* insert(T val);//在某个节点后插入一个值为val的节点，返回插入节点的地址

		friend class list<T>;
		friend class listIterator<T>;
};


//*****************************************
template<class T>
listNode<T>::listNode(T val,listNode<T>* p)
{
	value=val;
	next=p;
}

template<class T>
listNode<T>::listNode(const listNode<T> &obj)
{
	value=obj.value;
	next=obj.next;
}

//**************************************

template<class T>
listNode<T>* listNode<T>::duplicate()const
{
    listNode<T>* p;
    if(next!=NULL)
        p=new listNode<T>(value,next->duplicate());
    else
        p=new listNode<T>(value,NULL);
    assert(p!=NULL);
    return p;
}

template<class T>
listNode<T>* listNode<T>::insert(T val)
{
    next=new listNode<T>(val,next);
    assert(next!=NULL);
    return next;
}
//***************************
#endif