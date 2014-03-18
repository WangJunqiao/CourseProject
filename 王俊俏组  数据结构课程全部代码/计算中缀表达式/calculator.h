#ifndef CALCULATOR_H
#define CALCULATOR_H

#include"stack.h"
#include<string>
#include<sstream>
using namespace std;

class calculator
{
protected:
	stackList<int> data;
public:
	int currentMemory();
	void pushOperand(int value);
	void doOperator(char theOp);
	friend int calcuInfix(string);
};

int calculator::currentMemory()
{
	return data.top();
}

void calculator::pushOperand(int value)
{
	data.push(value);
}

void calculator::doOperator(char theOp)
{
	int result;
	int right=data.pop();
	int left=data.pop();
	switch(theOp)
	{
	case '+':
		result=left+right;
		break;

	case '-':
		result=left-right;
		break;


	case '*':
		result=left*right;
		break;

	case '/':
		result=left/right;
		break;
	case '^':
		result=1;
		for(int i=1;i<=right;i++)
			result*=left;
		break;
	}
	data.push(result);
}


int calcuInfix(string Infix)
{
	istringstream sin(Infix);
	int intval;
	calculator calc;
	char c;
	while(sin>>c)
	{
		switch(c)
		{
		case '0': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			sin.putback(c);
			sin>>intval;
			calc.pushOperand(intval);
			break;

		case '+':
			calc.doOperator('+');
			break;

		case '-':
			calc.doOperator('-');
			break;

		case '*':
			calc.doOperator('*');
			break;

		case '/':
			calc.doOperator('/');
			break;

		case '^':
			calc.doOperator('^');
			break;
		}
	}
	return calc.data.top();
}



void infixToPostfix(string &infixStr)
{
	stackList<char> opStack;
	string result("");
	char op;
	int i=0;
	while(infixStr[i]!='\0')
	{
		if(isdigit(infixStr[i]))
		{
			while(isdigit(infixStr[i]))
				result+=infixStr[i++];
			result+=" ";
		}
		else
			switch(op=infixStr[i++])
		{
			case '(':
				opStack.push('(');
				break;

			case ')':
				while(opStack.top()!='(')
					result+=opStack.pop();
				opStack.pop();
				break;

			case '+': case '-':
				while((!opStack.isEmpty()) && (opStack.top()!='('))
					result+=opStack.pop();
				opStack.push(op);
				break;

			case '*': case '/':
				while((!opStack.isEmpty()) && ((opStack.top()=='*')||(opStack.top()=='/')||(opStack.top()=='^')))
					result+=opStack.pop();
				opStack.push(op);
				break;

			case '^':
				while((!opStack.isEmpty()) && (opStack.top()=='^') )
					result+=opStack.pop();
				opStack.push(op);
				break;
		}
	}
	while(!opStack.isEmpty())
		result+=opStack.pop();
	infixStr=result;
}
#endif