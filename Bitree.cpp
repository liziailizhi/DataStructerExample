#include<iostream>
#include<vector>
#include<deque>
using namespace::std;

typedef struct bitree
{
	int data;
	bitree *left;
	bitree *right;
}BitreeNode, *Bitree;

int Bitree_init(Bitree &T, int depth)//构造深度为depth的满二叉树;第一个结点为头结点（空）
{
	T = new BitreeNode;	//T指向头结点（空）
	if (depth <= 0)
		return 1;	//树深度<=0构造失败
	T->left = new BitreeNode;	//T->left指向第一数据结点
	T->right = 0;
	T->data = 0;
	vector<BitreeNode*> vec_p(1, T->left);	//保存上一层的所有结点的指针
	vec_p[0]->data = 1;
	for (int i = 1; i<depth; i++)	//按树的深度一层一层构造结点
	{
		vector<BitreeNode*> vec_p_new(pow(2, i));	//保存当前层的所有结点的指针
		for (int j = 0; j<pow(2, i - 1); j++)
		{
			BitreeNode* p1 = new BitreeNode;
			BitreeNode* p2 = new BitreeNode;
			vec_p_new[2 * j] = p1;
			vec_p_new[2 * j + 1] = p2;
			vec_p[j]->left = p1;
			vec_p[j]->right = p2;
			p1->data = (vec_p[j]->data) * 2;
			p2->data = (vec_p[j]->data * 2) + 1;
		}
		vec_p = vec_p_new;
	}

	for (int i = 0; i<pow(2, depth - 1); i++)
	{
		vec_p[i]->left = 0;
		vec_p[i]->right = 0;
	}
	return 0;
}

/*int Bitree_print_PreOderTraverse(Bitree T)
{
	if (T == NULL || T->left == NULL)	//当T为空指针时，逻辑短路，T->left不会执行，因此不会报错
		return 1;	//空树
	T = T->left;
	BitreeNode* p = T;
	vector<BitreeNode*> vec;

	while (!(p->left == NULL&&p->right == NULL&&vec.empty()))
	{
		cout << p->data << endl;
		if (p->left == NULL&&p->right == NULL)
		{
			auto ite = vec.end();
			p = (*(--ite))->right;
			vec.pop_back();
		}
		else if (p->left == NULL)
		{
			p = p->right;
		}
		else if (p->right == NULL)
		{
			p = p->left;
		}
		else
		{
			vec.push_back(p);
			p = p->left;
		}
	}
	cout << p->data;
	return 0;
}
*/

int Bitree_print_PreOderTraverse(Bitree T)
{
	if(T==NULL||T->left==NULL)	//当T为空指针时，逻辑短路，T->left不会执行，因此不会报错
		return 1;	//空二叉树
	BitreeNode* p = T->left;
	vector<BitreeNode*> vec;
	while(!(p==NULL&&vec.empty()))
	{
		if(p!=NULL)
		{
			cout<<p->data<<endl;
			vec.push_back(p);
			p = p->left;
		}
		else
		{
			auto ite = vec.end();
			p = (*（--ite）)->right;
			vec.pop_back();
		}
	}
	return 0;
}

int Bitree_print_PostOderTraverse(Bitree T)		//后序遍历：相对前序中序更加复杂，因为要弹栈两次。
{
	if (T == NULL || T->left == NULL)	//当T为空指针时，逻辑短路，T->left不会执行，因此不会报错
		return 1;	//空二叉树
	BitreeNode* p = T->left;
	vector<BitreeNode*> vec;
	vector<int> vec_flag;		//用于标识栈中结点是否已经访问过一次右子树
	while (!(p == NULL&&vec.empty()))
	{
		if (p != NULL)
		{
			vec.push_back(p);
			vec_flag.push_back(0);
			p = p->left;
		}
		else
		{
			auto ite = vec.end();
			p = (*(--ite));
			auto ite_flag = vec_flag.end();
			if(*(--ite_flag)==0)
			{
				p = p->right;	//访问右子树
				*ite_flag = 1;	//标识p的右子树已访问过
			}
			else
			{
				cout<<p->data<<endl;
				vec.pop_back();
				vec_flag.pop_back();
				p = NULL;	//非常非常重要！！！！否则，会死循环，一直输出第一个遍历的结点
			}
		}
	}
	return 0;
}


int Bitree_print_DepthTraverse(Bitree T)
{
	if(T==NULL||T->left==NULL)	//当T为空指针时，逻辑短路，T->left不会执行，因此不会报错
		return 1;		//空树
	BitreeNode* p = T->left;
	deque<BitreeNode*> deq;
	while(!(p==NULL&&deq.empty()))
	{
		if(p!=NULL)
		{
			cout<<p->data<<endl;
			deq.push_back(p->left);
			deq.push_back(p->right);
			p = NULL;
		}
		else
		{
			auto ite = deq.begin();
			p = *ite;
			deq.pop_front();
		}
	}
	return 0;
}




void main()
{
	Bitree T;
	Bitree_init(T, 4);
	Bitree_print_PreOderTraverse(T);
	//cout << T->left->left->left->right->data;
	cin.get();
}
