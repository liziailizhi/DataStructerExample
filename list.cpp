#include<iostream>
using namespace::std;

typedef class sequence_list
{
public:
	int length;		//已存数据长度
	int *head;		//首数据地址
	int ListSize;	//申请的总长度
}SeqList;	//顺序表

int SeqList_init(SeqList &L,int ListSize)	//只能通过引用/指针传参，才能修改L
{
	L.head = new int[ListSize];
	if (!L.head)
		return 1;	//内存申请失败
	L.length = 0;
	L.ListSize = ListSize;
	return 0;	//成功
}

int SeqList_insert(SeqList &L, int pos, int elem)//插入元素
{
	//插入位置pos：取值[0,length];第一个位置为0
	//插入值elem
	if (L.length >= L.ListSize)
		return 1;	//表已满
	if (pos<0 || pos>length)
		return 2;	//位置错误
	for (int i = length - 1; i >= pos; i--)
	{
		L.head[i + 1] = L.head[i];
	}
	L.head[pos] = elem;
	return 0;	//成功
}

int SeqList_erase(SeqList &L, int pos)//删除元素
{
	if (L.length <= 0)
		return 1;	//空表
	if (pos<0 || pos>L.length - 1)
		return 2;	//指向空元素
	for (int i = pos; i < length - 1; i++)
	{
		L.head[i] = L.head[i + 1];	//最后一个不用改
	}
	L.length -= 1;
	return 0;	//成功
}

//线性链表
typedef class LNode
{
public:
	int data;
	LNode *next;
}ListNode,*LinkedListHead;

int LinkedList_init(LinkedListHead head)	//head是个指针，指向链表的第一个元素
{
	ListNode *head = 0;

}


int LinkedList_insert(LinkedListHead &head, int pos, int elem)
{//在第pos的位置（0开始），插入elem
	ListNode *q = head;
	ListNode *last = q;
	if (pos < 0)
		return 1;		//插入位置超范围
	while (pos)
	{
		if (q == NULL)
			return 1;		//插入位置超范围
		last = q;
		q = q->next;
		pos--;
	}//此时head指向要插入的node,last指向要插入的前一个node
	ListNode * p = new ListNode;
	if (p == NULL)
		return 2;	//内存申请失败
	p->data = elem;
	p->next = q;
	if (head == NULL)	//空表，last==head==NULL
		head = p;
	else
		last->next = p;
	return 0;
}

int LinkedList_erase(LinkedListHead &head, int pos)
{
	ListNode *q = head;
	ListNode *last = head;
	if (head == NULL)
		return 1;	//空表
	if (pos < 0)
		return 2;	//删除位置错误
	while (pos)
	{
		if (q == NULL)
			return 2;	//删除位置错误
		last = q;
		q = q->next;
		pos--;
	}//此时head指向待删除元素,last指向待删的上一个node
	if (last == q)	//此时，表只有一个结点，删除后需要给head赋值NULL
		head = NULL;
	else
		last->next = q->next;		
	delete q;
	return 0;
}