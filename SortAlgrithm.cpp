#include<iostream>
#include<vector>
using namespace::std;

void BinaryInsertingSort(vector<int> &vec)
{
	int n = vec.size();
	int tmp;
	for (int i = 1; i<n; i++)
	{
		//用二分法在vec[0]:vec[i-1]之间找到vec[i]应该插入的位置
		int high = i - 1;
		int low = 0;
		if (vec[i] >= vec[i - 1])
			continue;	//vec[i]不需要移动，进入下一个元素
		while (high > low)
		{
			if (vec[i] >= vec[(high + low) / 2])
				low = (high + low) / 2 + 1;
			else
				high = (high + low) / 2 - 1;
		}//循环结束low=high，vec[i]应该在high的位置
		tmp = vec[i];
		for (int j = i; j>high; j--)
		{
			vec[j] = vec[j - 1];
		}
		vec[high] = tmp;
	}
}


void HillSort(vector<int> &vec)
{
	int n = vec.size();
	int delta = n / 2;	//vec[0],vec[delta]...
	while (delta>0)
	{
		for (int i = 0; i<delta; i++)
		{
			//vec[(0+i):delta:n]
			//下面是插入排序的两层循环
			int p = i + delta;	//待插入元素位置;始于第二个（第一个位置不用变）
			while (p<n)
			{
				int q = i;	//比较的元素从第一个开始
				while (q<p)
				{
					if (vec[p]<vec[q])
					{
						int tmp = vec[p];
						for (int j = p; j>q; j -= delta)	//移位：注意不是j--
						{
							vec[j] = vec[j - delta];
						}
						vec[q] = tmp;
						break;	//找到了要插入的位置，直接更新下一个待插入元素
					}
					q += delta;
				}

				p += delta;
			}
		}
		delta = delta / 2;
	}
}

void BubbleSort(vector<int> &vec)
{
	int n = vec.size();
	for (int i = 1; i<n; i++)
	{
		for (int j = 0; j<n - i; j++)
		{
			if (vec[j]>vec[j + 1])
			{
				int tmp = vec[j + 1];
				vec[j + 1] = vec[j];
				vec[j] = tmp;
			}
		}
	}
}


void quicksort_(vector<int>::iterator ite1, vector<int>::iterator ite2)
{
	//ite1为左指针，ite2为右指针；待定位元素初始为*ite1
	int flag = 0;	//0：待定位元素为*ite1；1：待定位元素为ite2	
	auto ite_l = ite1;
	auto ite_r = ite2;
	while (ite1 != ite2)
	{
		if (flag == 0)	//*ite1为待定位，*ite1为比较元素
		{
			if (*ite2 >= *ite1)
				--ite2;
			else
			{
				int tmp = *ite2;
				*ite2 = *ite1;
				*ite1 = tmp;
				flag = 1;
			}
		}
		else	//*ite2为待定位，*ite1为比较元素
		{
			if (*ite1 <= *ite2)
				++ite1;
			else
			{
				int tmp = *ite2;
				*ite2 = *ite1;
				*ite1 = tmp;
				flag = 0;
			}
		}
	}
	//循环完成后ite1=ite2
	if (ite1 - ite_l > 0)
		quicksort_(ite_l, --ite1);	//注意--ite1改变了ite1，后面不要再用
	if (ite_r - ite2 > 0)
		quicksort_(++ite2, ite_r);
}

void QuickSort(vector<int> &vec)
{
	auto ite1 = vec.begin();//指向第一个元素
	auto ite2 = vec.end();
	ite2--;	//指向最后一个元素
	quicksort_(ite1, ite2);
}



void Combine(vector<int>::iterator ite1, vector<int>::iterator ite2, vector<int>::iterator ite3)	//合并[ite1,ite2),[ite2,ite3)
{
	int n1 = ite2 - ite1;	//序列1长度
	int n2 = ite3 - ite2;	//序列2长度
	vector<int> vec_tmp;
	int i = 0;	//标记序列1中元素
	int j = 0;	//标记序列2
	while (i<n1&&j<n2)
	{
		//选取较小的元素入栈vec_tmp
		//当任一序列元素全部入栈->循环结束
		if (*(ite1 + i)<*(ite2 + j))
		{
			vec_tmp.push_back(*(ite1 + i));
			i++;
		}
		else
		{
			vec_tmp.push_back(*(ite2 + j));
			j++;
		}
	}
	while (i<n1)	//当序列1有剩余元素时，该循环执行
	{
		vec_tmp.push_back(*(ite1 + i));
		i++;
	}
	while (j<n2) 	//当序列2有剩余元素时，执行该循环
	{
		vec_tmp.push_back(*(ite2 + j));
		j++;
	}

	for (int k = 0; k<(n1 + n2); k++)	//将临时vec_tmp中的元素存入原序列中
	{
		*(ite1 + k) = vec_tmp[k];
	}
}

void MergeSort(vector<int> &vec)	//归并排序
{
	int n = vec.size();
	int i = n;	//i表示当前循环中，子序列的个数
	auto ite = vec.begin();
	int delta = 1;	//每个子序列的元素个数(最后一个子序列个数<=delta)
	while (i>1)
	{
		for (int j = 0; j<i; j += 2)		//相邻两子序列(序列j、序列j+1)合并
		{
			//序列j：[ite1,ite2)
			//序列j+1：[ite2,ite3)
			auto ite1 = vec.begin();
			auto ite2 = ite1;
			auto ite3 = ite1;
			if (j == i - 1)	//当前序列j是i个子序列中最后一个：序列j的长度不一定为delta，序列j+1为空
			{
				ite1 = ite + delta*j;
				ite2 = vec.end();
				ite3 = ite2;
			}
			else if (j + 1 == i - 1)	//当前序列j+1是子序列中最后一个：序列j长度为delta，独立j+1则不一定
			{
				ite1 = ite + delta*j;
				ite2 = ite1 + delta;
				ite3 = vec.end();
			}
			else	//序列j和序列j+1都是中间序列：长度都是delta
			{
				ite1 = ite + delta*j;	//序列j首元素
				ite2 = ite1 + delta;		//序列j+1首元素
				ite3 = ite2 + delta;		//序列j+1尾元素的下一个
			}
			Combine(ite1, ite2, ite3);
		}
		i = (i + 1) / 2;	//ceil(i/2)
		delta = delta * 2;
	}
}



void HeapBuild(vector<int>::iterator ite,int root,int length)		//将仅有根节点位置被破坏的 堆树，构造成新的堆树
{
	//ite+0为未排序序列的第一个元素，对应深度遍历序列中的元素1
	//ite+1*2-1为第一个元素的左子结点，对应元素1*2
	//ite+(1*2+1)-1为右子节点，对应元素1*2+1
	//root为根节点在深度遍历中的序号，ite+root-1为根节点指针；ite+root*2-1为左子节点；ite+(root*2+1)-1右子节点
	//length为未排序序列的尾指针对应的深度遍历序号
	int j = root*2;
	while(j<length)		//保证左子节点和右子节点都存在
	{
		if(*(ite+j-1)<*(ite+j))	//左子节点<右子节点时，替换右子树（保证ite+j-1指向子节点中最大值）
			j = j+1;
		if(*(ite+j-1)>*(ite+root-1))	//当最大子节点>根节点：交换
		{
			int tmp = *(ite+root-1);
			*(ite+root-1) = *(ite+j-1);
			*(ite+j-1) = tmp;
			root = j;
			j = j*2;
		}
		else
			break;	//左右子节点中最大值<根节点，则不用移动
	}
	if(j==length&&(*(ite+j-1)>*(ite+root-1)))	//while中遗漏的情况j==length
	{
		int tmp = *(ite+root-1);
		*(ite+root-1) = *(ite+j-1);
		*(ite+j-1) = tmp;
	}
}

void HeapSort(vector<int> &vec)		//堆排序
{
	int n = vec.size();		//当前未排序的元素个数
	auto ite = vec.begin();
	for(int i = n/2;i>0;i--)	//i起始于vec尾结点的父节点，循环结束：将vec初始化为一个堆树
	{
		HeapBuild(ite,i,n);
	}
	
	while(n>0)
	{
		int tmp = vec[0];
		vec[0] = vec[n-1];
		vec[n-1] = tmp;
		n--;
		HeapBuild(ite,1,n);
	}
}

void main()
{
	int n = 5;
	vector<int> vec(n);
	vec = { 2, 5, 3, 4, 1 };
	//BinaryInsertingSort(vec);
	//HillSort(vec);
	//QuickSort(vec);
	MergeSort(vec);
	for (int i = 0; i<n; i++)
		cout << vec[i] << endl;
	cin.get();
}
