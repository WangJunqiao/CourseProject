#include"stack.h"
#include"calculator.h"
#include<iostream>
#include<string>
using namespace std;


int main()
{
	string s;
	while(getline(cin,s))
	{
		infixToPostfix(s);
		cout<<calcuInfix(s)<<endl;
	}
}