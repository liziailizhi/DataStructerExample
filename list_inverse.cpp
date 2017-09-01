#include<iostream>
using namespace std;

typedef struct ListNode
{
	int data;
	ListNode* next;
}*List;

int List_push(List& L, int elem)
{
	ListNode* p = L;
	ListNode* q = new ListNode;
	if (q == NULL)
		return 1;	//申请失败
	q->data = elem;
	q->next = 0;
	if (L == NULL)
	{
		L = q;
		return 0;
	}
	while (p->next)
		p = p->next;
	p->next = q;
	return 0;
}

int List_inverse(List& L)
{

	ListNode* p1 = L;
	if (p1->next == NULL)
		return 0;	//一个元素
	ListNode* p2 = p1->next;
	if (p2->next == NULL)
	{
		L = p2;
		p2->next = p1;
		p1->next = 0;
		return 0;
	}
	ListNode* p3 = p2->next;
	p1->next = 0;
	while (p3->next)
	{
		L = p2;
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p2->next;
	}
	L = p3;
	p3->next = p2;
	p2->next = p1;
	return 0;
}

int List_print(List L)
{
	ListNode*p = L;
	while (p->next)
	{
		cout << p->data << endl;
		p = p->next;
	}
	if (L)
		cout << p->data;
	return 0;
}

int main()
{
	List L = NULL;
	for (int i = 0; i<5; i++)
	{
		List_push(L, i);
	}
	List_print(L);

	List_inverse(L);
	List_print(L);
	return 0;
}
