#include"listNode.h"
#include"list.h"
#include"listIterator.h"
#include"polynomial.h"
#include<iostream>
using namespace std;
int main()
{
    polynomial p1;
    int c,p,n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
          cin>>c>>p;
          p1+=term(c,p);
    }

    polynomial p2;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
          cin>>c>>p;
          p2+=term(c,p);
    }

    polynomial ans_p(p1+p2);

    cout<<ans_p<<endl;
}