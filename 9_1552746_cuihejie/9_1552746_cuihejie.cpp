//===============================================================类中函数的实现和主函数==================================================================
#include"BsortTree.h"
#include <iostream>
#include <iomanip>
using namespace std;

//建立系统时的交互界面
void OutputUI()
{
	cout << left;
	cout << setw(20) << "**" << setw(30) << "二叉排序树" << "**" << endl;
	cout << "====================================================" << endl;
	cout << setw(19) << "**" << setw(31) << "1---建立二叉排序树" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "2---插入元素" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "3---查询元素" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "4---退出程序" << "**" << endl;
	cout << "====================================================" << endl;
}

//删除以ptr为根节点的子树
void BsortTree::Delete(BsortNode *ptr)
{
	if (ptr->left != NULL)
		Delete(ptr->left);
	if (ptr->right != NULL)
		Delete(ptr->right);
	delete ptr;
}

//生成二叉搜索树
void BsortTree::FormTree()
{
	int temp;
	cout << "Please input key to create Bsort_Tree:" << endl;
	cin >> temp;
	root = new BsortNode(temp);
	while (1)
	{
		cin >> temp;
		if (temp == RefValue)break;
		if (!Insert(temp, root))
		{
			cout << "The input key<" << temp << "> is have in!"<<endl;
		}
	}
}

//递归插入元素
bool BsortTree::Insert(const int value, BsortNode *&ptr)
{
	if (ptr == NULL)
	{
		ptr = new BsortNode(value);
		if (ptr == NULL)
		{
			cerr << "Out of space!" << endl;
			exit(1);
		}
		return true;
	}
	if (value < ptr->data)
	{
		return Insert(value, ptr->left);//在左子节点域递归
	}
	if (value > ptr->data)
	{
		return Insert(value, ptr->right);//在右子节点域递归
	}
	if (value == ptr->data)
		return false;
}

//递归搜索元素
bool BsortTree::Search(const int value, BsortNode *ptr)
{
	if (ptr == NULL)return false;
	else if (value < ptr->data)
		return Search(value, ptr->left);
	else if (value > ptr->data)
		return Search(value, ptr->right);
	else
		return true;
}

//中序遍历显示二叉搜索树
void BsortTree::PrintTree(BsortNode *ptr)
{
	if (ptr->left != NULL)
		PrintTree(ptr->left);
	cout << ptr->data << "->";
	if (ptr->right != NULL)
		PrintTree(ptr->right);
}

int main()
{
	OutputUI();
	int choice;
	int temp;
	int flag = 1;
	BsortTree Tree;

	while (flag)//flag为零时退出程序
	{
		cout << "Please select: ";
		cin >> choice;
		switch (choice)
		{
		case 1://建立二叉排序树
			Tree.FormTree();
			cout << "Bsort_Tree is:" << endl;
			Tree.PrintTree(Tree.GetRoot());
			cout << "\n"<<endl;
			break;

		case 2://插入元素
			cout << "Please input key which inserted: ";
			cin >> temp;
			if (Tree.Insert(temp, Tree.GetRoot()))
			{
				Tree.PrintTree(Tree.GetRoot());
				cout << "\n" << endl;
			}
			else
				cout << "Insert failed." << endl;
			break;

		case 3://查询元素
			cout << "Please input key which searched: ";
			cin >> temp;
			if (Tree.Search(temp, Tree.GetRoot()))
				cout << "search success!" <<"\n"<< endl;
			else
				cout << temp << " not exist!" <<"\n"<< endl;
			break;

		case 4://退出程序
			flag = 0;
			break;
		}
	}
	return 0;
}