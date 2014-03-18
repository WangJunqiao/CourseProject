#ifndef BST_H
#define BST_H

#include<iostream>
#include<fstream>
using namespace std;

template<class T>
class Node//BST节点类
{
public:
	T value;
	Node *leftptr,*rightptr;

	Node(T val=0);//不能缺省默认构造函数
	Node(T val,Node<T> *l,Node<T>* r);

	Node<T>* copy()const;
	void deleteAll();
	Node<T>* removeTop();
	void print(ofstream &fout)const;
};

template<class T>
Node<T>::Node(T val)
{
	value=val;
	leftptr=rightptr=NULL;
}

template<class T>
Node<T>::Node(T val,Node<T> *l,Node<T> *r)
{
	value=val;
	leftptr=l;
	rightptr=r;
}

template<class T>
Node<T>* Node<T>::copy()const
{
	Node<T> *l=NULL,*r=NULL;
	if(this->leftptr)
		l=this->leftptr->copy();
	if(this->rightptr)
		r=this->rightptr->copy();
	Node<T> *p=new Node<T>(this->value,l,r);
	return p;
}

template<class T>
void Node<T>::deleteAll()
{
	if(this->leftptr)
		this->leftptr->deleteAll();
	if(this->rightptr)
		this->rightptr->deleteAll();
	delete this;
}

template<class T>
void Node<T>::print(ofstream &fout)const
{
	if(this->leftptr)
		this->leftptr->print(fout);
	fout<<this->value<<endl;
	if(this->rightptr)
		this->rightptr->print(fout);
}
template<class T>
Node<T>* Node<T>::removeTop()
{
	Node<T> *l=this->leftptr;
	Node<T> *r=this->rightptr;

	if(l==NULL)
	{
		delete this;
		return r;
	}

	if(r==NULL)
	{
		delete this;
		return l;
	}

	Node<T> *p=this,*next=p->rightptr;
	while(next->leftptr!=NULL)
	{
		p=next;
		next=next->leftptr;
	}
	this->value=next->value;
	if(p==this)
		p->rightptr=next->removeTop();
	else
		p->leftptr=next->removeTop();
	return this;
}
//************************************************

template<class T>
class BST
{
private:
	Node<T> *root;

public:
	BST();
	BST(const BST<T> &source);
	virtual ~BST();

	void Insert(T val);
	void Remove(T val);
	Node<T>* Find(T val)const;
	void Print(ofstream &fout)const;
};

template<class T>
BST<T>::BST():root(NULL){};

template<class T>
BST<T>::BST(const BST<T> &source)
{
	this->root=NULL;
	if(source.root)
		this->root=source.root->copy();
}

template<class T>
BST<T>::~BST()
{
	if(this->root)
		root->deleteAll();
}

template<class T>
void BST<T>::Insert(T val)
{
	if(root==NULL)
	{
		root=new Node<T>(val);
		return;
	}

	Node<T> *current=root;

	while(1)
	{
		if(val < current->value)
		{
			if(current->leftptr == NULL)
			{
				current->leftptr=new Node<T>(val);
				return ;
			}
			else
				current=current->leftptr;
		}
		else
		{
			if(current->rightptr == NULL)
			{
				current->rightptr=new Node<T>(val);
				return;
			}
			else
				current=current->rightptr;
		}
	}
}


template<class T>
void BST<T>::Remove(T val)
{
	if(root==NULL)
		return;
	if(root->value == val)
	{
		root=root->removeTop();
		return;
	}

	Node<T> *p=root,*next;
	while(p!=NULL)
	{
		if(val < p->value)
		{
			next=p->leftptr;
			if(next && next->value == val)
			{
				p->leftptr=next->removeTop();
				return;
			}
		}
		else
		{
			next=p->rightptr;
			if(next && next->value == val)
			{
				p->rightptr=next->removeTop();
				return;
			}
		}
		p=next;
	}
}

template<class T>
Node<T>* BST<T>::Find(T val)const
{
	Node<T> *current=root;
	while(current!=NULL)
	{
		if(current->value == val)
			return current;
		if(val < current->value)
			current=current->leftptr;
		else
			current=current->rightptr;
	}
	return NULL;
}

template<class T>
void BST<T>::Print(ofstream &fout)const
{
	if(this->root)
	{
		root->print(fout);
		return;
	}
}
#endif

