#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<iostream>
#include"term.h"
using namespace std;

class polynomial
{
private:
	list<term> exp;
public:
	polynomial();
	polynomial(const polynomial &p);

	list<term> get_exp()const {return exp;}
	void operator+=(const term &t);
	polynomial operator+(polynomial &p2);//不能用引用的，返回就析构了，实体不存在了

	friend ostream& operator<<(ostream &o,polynomial &p);
};

polynomial::polynomial()
{};

polynomial::polynomial(const polynomial &p):exp(p.exp)
{};

void polynomial::operator+=(const term &t)
{
	listIterator<term> it(exp);
	for(it.init();!it;it++)
	{
		if(it().p==t.p)
		{
			it().c+=t.c;
			return;
		}
		else if(it().p>t.p)
		{
			it.addBefore(t);
			return;
		}
	}
	it.addBefore(t);
	return;
}

polynomial polynomial::operator+(polynomial &p2)
{
	polynomial p3;
	listIterator<term> it1(exp),it2(p2.exp);
	term temp;
	for(it1.init();!it1;it1++)
	{
		temp=it1();//引用可以再次用来做参数传递吗？？？
		p3+=temp;
	}
	for(it2.init();!it2;it2++)
	{
		temp=it2();
		p3+=temp;
	}
	return p3;
}                    //p3在这里就被析构了

ostream& operator<<(ostream &o,polynomial &p)
{
	//listIterator<term> it(p.get_exp());//这个是不行的，p.get_exp()返回的是一个临时链表，这句执行完后就被析构了，这样it就成了无根之树了
	
	listIterator<term> it(p.exp);
	o<<it();
	it++;
	for(;!it;it++)
		o<<"+"<<it();
	return o;
}
#endif