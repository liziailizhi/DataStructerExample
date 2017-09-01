#include<iostream>
#include<vector>
#include<deque>
using namespace::std;

typedef struct bitreenode
{
	int data;
	bitreenode* left;
	bitreenode* right;
}BitreeNode, *Bitree;

int BinarySortTree_add(Bitree &T, int elem);
int BinarySortTree_init(Bitree &T)		//初始化二叉排序树
{
	int n;	//node总数

	T = new BitreeNode;
	T->data = 0;
	T->left = NULL;
	T->right = NULL;
	BitreeNode*p = T;
	cout << "please input the node number:" << endl;
	cin >> n;
	cout << "please input all the data in every node:" << endl;
	vector<int> vec_data(n);
	for (int i = 0; i<n; i++)
	{
		cin >> vec_data[i];
	}
	for (int i = 0; i < n; i++)
	{
		int re = 0;
		re = BinarySortTree_add(T, vec_data[i]);
		if (re != 0)
			return re;
	}
	//for (int i = 0; i<n; i++)
	//{
	//	BitreeNode* q = new BitreeNode;
	//	BitreeNode* last = 0;
	//	q->data = vec_data[i];
	//	q->left = NULL;
	//	q->right = NULL;
	//	if (i == 0)	//第一个有数据的结点
	//	{
	//		p->left = q;
	//		p = p->left;	//p指向第一个有数据的结点
	//	}
	//	else
	//	{
	//		p = T->left;	//p指向第一个有数据的结点
	//		while (p != NULL)
	//		{
	//			if (vec_data[i]<p->data)	//往左子树插入
	//			{
	//				last = p;	//指向p的上一个结点
	//				p = p->left;
	//			}
	//			else if (vec_data[i]>p->data)		//往右子树插入
	//			{
	//				last = p;
	//				p = p->right;
	//			}
	//			else
	//				return 1;	//输入的数据有重复值
	//		}	
	//		if (last->data>vec_data[i])
	//		{
	//			last->left = q;
	//		}
	//		else
	//		{
	//			last->right = q;
	//		}
	//	}
	//}
	return 0;
}

int BinarySortTree_add(Bitree &T, int elem)
{
	BitreeNode*q = 0;
	if (T == NULL)
	{
		q = new BitreeNode;
		q->data = 0;
		q->left = NULL;
		q->right = NULL;
		T = q;
	}
	if (T->left == NULL)
	{
		q = new BitreeNode;
		q->data = elem;
		q->left = NULL;
		q->right = NULL;
		T->left = q;
		return 0;
	}
	BitreeNode* p = T->left;	//p指向第一个有数据的结点
	BitreeNode* last = p;
	q = new BitreeNode;
	q->data = elem;
	q->left = NULL;
	q->right = NULL;
	while (p != NULL)
	{
		if (elem<p->data)	//往左子树插入
		{
			last = p;	//指向p的上一个结点
			p = p->left;
		}
		else if (elem>p->data)		//往右子树插入
		{
			last = p;
			p = p->right;
		}
		else
			return 1;	//输入的数据有重复值
	}
	if (last->data>elem)
	{
		last->left = q;
	}
	else
	{
		last->right = q;
	}
	return 0;
}

int BinarySortTree_delete(Bitree T, int elem)
{
	if (T == NULL || T->left == NULL)
	{
		return 1;	//空树
	}
	BitreeNode* p_delete = T->left;		//指向待删结点
	BitreeNode* last = p_delete;		//指向待删结点的父亲
	int if_find = 0;
	while (if_find == 0 && p_delete != NULL)
	{
		if (p_delete->data > elem)
		{
			last = p_delete;
			p_delete = p_delete->left;
		}
		else if (p_delete->data < elem)
		{
			last = p_delete;
			p_delete = p_delete->right;
		}
		else
			if_find = 1;
	}
	if (if_find == 0)
	{
		cout << "No such element!" << endl;
		return 2;	//没有该元素
	}

	if (p_delete->left == NULL&&p_delete->right == NULL)	//待删为叶子节点：直接删除结点
	{
		if (last->right->data == elem)
			last->right = NULL;
		else
			last->left = NULL;
		delete p_delete;
	}
	else if (p_delete->left == NULL)	//待删仅含右子树
	{
		if (last->right->data == elem)
			last->right = p_delete->right;
		else
			last->left = p_delete->right;
		delete p_delete;
	}
	else if (p_delete->right == NULL)	//待删仅含左子树
	{
		if (last->right->data == elem)
			last->right = p_delete->left;
		else
			last->left = p_delete->left;
		delete p_delete;
	}
	else			//待删含有左右子树:找左子树的最右叶子节点。
	{
		BitreeNode* p = p_delete->left;
		last = p;	//指向p的父结点
		BitreeNode* last_last = p_delete;	//指向last的父结点
		while (p != NULL)
		{
			if (last != p)	//当last==p时，如果将last赋给last_last，会导致last_last==last
				last_last = last;
			last = p;
			p = p->right;
		}
		p_delete->data = last->data;
		if (last_last == p_delete)	//左子树的最右叶子节点即为待删的左子节点；
			last_last->left = NULL;
		else
			last_last->right = NULL;
		delete last;
	}
	return 0;
}

int BinarySortTree_print(Bitree T)
{
	BitreeNode* p = T->left;
	deque<BitreeNode*> deq;
	deq.push_back(p);
	while (!deq.empty())
	{
		auto ite = deq.begin();
		p = *ite;
		deq.pop_front();
		if (p != NULL)
		{
			cout << p->data << endl;
			deq.push_back(p->left);
			deq.push_back(p->right);
		}
	}
	return 0;
}


void main()
{
	Bitree T;
	BinarySortTree_init(T);
	BinarySortTree_print(T);
	int elem;
	cin >> elem;
	BinarySortTree_delete(T, elem);
	BinarySortTree_print(T);
	cin.get();
}




