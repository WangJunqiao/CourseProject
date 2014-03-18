#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include"list.h"

template<class T>
class listIterator
{
    private:
        list<T> &obj;//由于是引用，所以必须用初始化列表的方式进行初始化
        listNode<T> *cur,*pre;
    public:
        listIterator(list<T> &_obj);

        virtual bool init();
        virtual T& operator()();//返回引用，要修改的
        virtual bool operator!();
        virtual bool operator++();
        virtual void operator=(T val);

        void removeCurrent();
        void addBefore(T val);
        void addAfter(T val);
};
//***********************
template<class T>
listIterator<T>::listIterator(list<T> &_obj):obj(_obj)//*****
{
    //obj=_obj;
    cur=obj.head;
    pre=NULL;
}
//*******************************

template<class T>
bool listIterator<T>::init()
{
    cur=obj.head;
    pre=NULL;
    return cur!=NULL;
}

template<class T>
T& listIterator<T>::operator()()
{
    assert(cur!=NULL);//这里就表明了如果刚刚执行了removeCurrent操作就不能马上执行这个取值操作
    return cur->value;
}

template<class T>
void listIterator<T>::operator=(T val)
{
    assert(cur!=NULL);
    cur->value=val;
}

template<class T>
void listIterator<T>::removeCurrent()
{
    assert(cur!=NULL);
    if(pre==NULL)//如果删除的是首节点
        obj.head=obj.head->next;
    else         //删除的是中间的节点
        pre->next=cur->next;

    delete cur;
    cur=NULL;
}

template<class T>
bool listIterator<T>::operator++()
{
    if(cur==NULL)
    {
        if(pre==NULL)
            cur=obj.head;
        else
            cur=pre->next;
    }
    else
    {
        pre=cur;
        cur=cur->next;
    }
    return cur!=NULL;
}

template<class T>
bool listIterator<T>::operator!()
{
    if(cur!=NULL)
        return true;
    else if(pre!=NULL)
        return pre->next!=NULL;
    else
        return obj.head!=NULL;
}

template<class T>
void listIterator<T>::addBefore(T val)
{
    if(pre!=NULL)
        pre=pre->insert(val);//insert函数为插到其后，然后返回这个节点的地址
    else //pre为NULL时，则必须是在首节点之前
    {
        obj.list<T>::add(val);//obj.add(val);
        pre=obj.head;
    }
}

template<class T>
void listIterator<T>::addAfter(T val)
{
    if(cur!=NULL)//cur在的时候
        cur->insert(val);
    else if(pre!=NULL)//pre在的时候
        pre->insert(val);
    else
        obj.list<T>::add(val);
}

#endif