#include<iostream>
using namespace::std;

typedef class sequence_list
{
public:
	int length;		//�Ѵ����ݳ���
	int *head;		//�����ݵ�ַ
	int ListSize;	//������ܳ���
}SeqList;	//˳���

int SeqList_init(SeqList &L,int ListSize)	//ֻ��ͨ������/ָ�봫�Σ������޸�L
{
	L.head = new int[ListSize];
	if (!L.head)
		return 1;	//�ڴ�����ʧ��
	L.length = 0;
	L.ListSize = ListSize;
	return 0;	//�ɹ�
}

int SeqList_insert(SeqList &L, int pos, int elem)//����Ԫ��
{
	//����λ��pos��ȡֵ[0,length];��һ��λ��Ϊ0
	//����ֵelem
	if (L.length >= L.ListSize)
		return 1;	//������
	if (pos<0 || pos>length)
		return 2;	//λ�ô���
	for (int i = length - 1; i >= pos; i--)
	{
		L.head[i + 1] = L.head[i];
	}
	L.head[pos] = elem;
	return 0;	//�ɹ�
}

int SeqList_erase(SeqList &L, int pos)//ɾ��Ԫ��
{
	if (L.length <= 0)
		return 1;	//�ձ�
	if (pos<0 || pos>L.length - 1)
		return 2;	//ָ���Ԫ��
	for (int i = pos; i < length - 1; i++)
	{
		L.head[i] = L.head[i + 1];	//���һ�����ø�
	}
	L.length -= 1;
	return 0;	//�ɹ�
}

//��������
typedef class LNode
{
public:
	int data;
	LNode *next;
}ListNode,*LinkedListHead;

int LinkedList_init(LinkedListHead head)	//head�Ǹ�ָ�룬ָ������ĵ�һ��Ԫ��
{
	ListNode *head = 0;

}


int LinkedList_insert(LinkedListHead &head, int pos, int elem)
{//�ڵ�pos��λ�ã�0��ʼ��������elem
	ListNode *q = head;
	ListNode *last = q;
	if (pos < 0)
		return 1;		//����λ�ó���Χ
	while (pos)
	{
		if (q == NULL)
			return 1;		//����λ�ó���Χ
		last = q;
		q = q->next;
		pos--;
	}//��ʱheadָ��Ҫ�����node,lastָ��Ҫ�����ǰһ��node
	ListNode * p = new ListNode;
	if (p == NULL)
		return 2;	//�ڴ�����ʧ��
	p->data = elem;
	p->next = q;
	if (head == NULL)	//�ձ�last==head==NULL
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
		return 1;	//�ձ�
	if (pos < 0)
		return 2;	//ɾ��λ�ô���
	while (pos)
	{
		if (q == NULL)
			return 2;	//ɾ��λ�ô���
		last = q;
		q = q->next;
		pos--;
	}//��ʱheadָ���ɾ��Ԫ��,lastָ���ɾ����һ��node
	if (last == q)	//��ʱ����ֻ��һ����㣬ɾ������Ҫ��head��ֵNULL
		head = NULL;
	else
		last->next = q->next;		
	delete q;
	return 0;
}