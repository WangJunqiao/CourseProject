#ifndef TERM_H
#define TERM_H


#include<iostream>
#include<cmath>
using namespace std;


class term
{
    private:
        int c,p;
    public:
        term(int _c=0,int _p=0);
        term(const term &);

        int get_c()const {return c;}
        int get_p()const {return p;}
        term operator*(const term &right);
        term operator+(const term &right);

        bool operator==(const term &right);

        friend class polynomial;
        friend ostream& operator<<(ostream&,const term&);
};

//************************
term::term(int _c,int _p)
{
    c=_c;
    p=_p;
}

term::term(const term &t)
{
    c=t.c;
    p=t.p;
}
//********************************

term term::operator*(const term &t)
{
	return term(c*t.c,p+t.p);
}

term term::operator+(const term &t)
{
	assert(p==t.p);
	return term(c+t.c,p);
}

bool term::operator==(const term &t)
{
	return c==t.c && p==t.p;
}

ostream& operator<<(ostream &o,const term &t)
{
	if(t.get_c()==0)
		return o;
	if(t.get_c()!=1)
		o<<t.get_c();

	switch(t.get_p())
	{
	case 0:
		break;
	case 1:
		o<<"X";
		break;//每一层的break不要忘记
	default:
		o<<"X^"<<t.get_p();
		break;
	}
	return o;
}

#endif