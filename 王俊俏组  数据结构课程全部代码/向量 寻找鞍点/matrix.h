#ifndef TEMPLATE_H
#define TEMPLATE_H

#include<iostream>
#include"vector.h"
#include<assert.h>
using namespace std;

template<class T>
class matrix
{
	private:
		vector< vector<T>* > R;
	public:
		
		matrix(unsigned int rows,unsigned int cols);
		matrix(unsigned int rows,unsigned int cols,T init);
		matrix();
		~matrix();

		vector<T>& operator[] (unsigned int index)const;
		int get_rows()const;
		int get_cols()const;

		friend matrix<T> operator*(const matrix<T> &,const matrix<T> &);
};

template<class T>
matrix<T>::matrix(unsigned int rows,unsigned int cols):R(rows)
{
	for(int i=0;i<rows;i++)
	{
		R[i]=new vector<T>(cols);
		assert(R[i]!=NULL);
	}
}

template<class T>
matrix<T>::matrix(unsigned int rows,unsigned int cols,T init):R(rows)
{
	for(int i=0;i<rows;i++)
	{
		R[i]=new vector<T>(cols,init);
		assert(R[i]!=NULL);
	}
}

template<class T>
matrix<T>::matrix():R(1)
{
	R[0]=new vector<T>(1);
	assert(R[0]!=NULL);
}

template<class T>
matrix<T>::~matrix()
{
	unsigned int len=R.length();
	vector<T>* p;
	for(int i=0;i<len;i++)
	{
		p=R[i];
		R[i]=NULL;
		delete p;
	}
}


template<class T>
int matrix<T>::get_rows()const
{
	return R.length();
}

template<class T>
int matrix<T>::get_cols()const
{
	return R[0]->length();
}

template<class T>
vector<T>& matrix<T>::operator [](unsigned int index)const
{
	return *(R[index]);
}

template<class T>
matrix<T> operator*(const matrix<T> &left,const matrix<T> &right)
{
	int n=left.get_rows(),m=left.get_cols(),p=right.get_cols();
	assert(m==right.get_rows());

	matrix<T> temp(n,p,0);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<p;j++)
		{
			for(int k=0;k<m;k++)
				res[i][j]+=left[i][k]*right[k][j];
		}
	}
	return temp;
}

#endif