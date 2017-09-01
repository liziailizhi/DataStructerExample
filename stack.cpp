#include<iostream>
using namespace std;

#define MAX_NUM 10
class SeqStack{
public:
	int *top;
	int *bottom;
	int size; 
};

int SeqStack_init(SeqStack &S,int size)
{
	S.bottom = new int[size];
	if (S.bottom == NULL)
		return 1;	//申请内存失败
	S.size = size;
	S.top = S.bottom;	//空栈
	return 0;	//成功
}

int SeqStack_push(SeqStack &S,int elem)
{
	if(S.top-S.bottom>=S.size)
		return 1;	//满栈
	*(S.top) = elem;
	S.top += 1;
	return 0;		//成功
}


int SeqStack_pop(SeqStack &S,int& out_elem)
{
	if(S.top==S.bottom)
		return 1;	//空栈
	S.top--; 
	out_elem = *(S.top);
	return 0;		//成功
}

int SeqStack_print(SeqStack &S)
{
	for(auto p = S.bottom;S.top - p>0;p++)
	{
		cout<<*p<<endl;
	}
	return 0;		//成功
}


void main()
{
	SeqStack S;
	SeqStack_init(S,MAX_NUM);
	for(int i=0;i<MAX_NUM;i++)
		SeqStack_push(S,i);
	SeqStack_print(S);
}

