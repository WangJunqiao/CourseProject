#ifndef LIST_H
#define LIST_H

#include"listNode.h"
#include<iostream>
using namespace std;

template<class T>
class listIterator;

template<class T>
class list
{
    protected:
        listNode<T>* head;
    public:
        list();
        list(const list<T> &obj);
        virtual ~list();

        virtual void add(T val);
        virtual void deleteAll();
        T firstElement()const;
        bool isempty()const;
        virtual void removeFirst();
        list<T>* duplicate()const;//传指针节省时间

        friend listIterator<T>;
};


//*********************************
template<class T>
list<T>::list()
{
    head=NULL;
}

template<class T>
list<T>::list(const list<T> &obj)
{
    if(obj.head==NULL)
        head=NULL;
    else
        head=obj.head->duplicate();
}

template<class T>
list<T>::~list()
{
    this->deleteAll();
}
//*****************************************

template<class T>
void list<T>::add(T val)
{
    head=new listNode<T>(val,head);
    assert(head!=NULL);
}

template<class T>
void list<T>::deleteAll()
{
    listNode<T>* p=head;
    while(p!=NULL)
    {
        head=head->next;
        delete p;
        p=head;
    }
    head=NULL;
}

template<class T>
T list<T>::firstElement()const
{
    return head->value;
}

template<class T>
bool list<T>::isempty()const
{
    return head==NULL;
}

template<class T>
void list<T>::removeFirst()
{
    assert(head!=NULL);
    listNode<T>* p=head;
    head=head->next;
    delete p;
}

template<class T>
list<T>* list<T>::duplicate()const
{
    list<T> *temp=new list<T>;//这个是new出来的，这个函数结束后不会被析构掉的
    if(head)
        temp->head=head->duplicate();
    return temp;
}
//*********************************************
#endif