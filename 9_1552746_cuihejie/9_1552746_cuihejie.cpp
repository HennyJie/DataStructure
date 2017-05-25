//===============================================================���к�����ʵ�ֺ�������==================================================================
#include"BsortTree.h"
#include <iostream>
#include <iomanip>
using namespace std;

//����ϵͳʱ�Ľ�������
void OutputUI()
{
	cout << left;
	cout << setw(20) << "**" << setw(30) << "����������" << "**" << endl;
	cout << "====================================================" << endl;
	cout << setw(19) << "**" << setw(31) << "1---��������������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "2---����Ԫ��" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "3---��ѯԪ��" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "4---�˳�����" << "**" << endl;
	cout << "====================================================" << endl;
}

//ɾ����ptrΪ���ڵ������
void BsortTree::Delete(BsortNode *ptr)
{
	if (ptr->left != NULL)
		Delete(ptr->left);
	if (ptr->right != NULL)
		Delete(ptr->right);
	delete ptr;
}

//���ɶ���������
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

//�ݹ����Ԫ��
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
		return Insert(value, ptr->left);//�����ӽڵ���ݹ�
	}
	if (value > ptr->data)
	{
		return Insert(value, ptr->right);//�����ӽڵ���ݹ�
	}
	if (value == ptr->data)
		return false;
}

//�ݹ�����Ԫ��
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

//���������ʾ����������
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

	while (flag)//flagΪ��ʱ�˳�����
	{
		cout << "Please select: ";
		cin >> choice;
		switch (choice)
		{
		case 1://��������������
			Tree.FormTree();
			cout << "Bsort_Tree is:" << endl;
			Tree.PrintTree(Tree.GetRoot());
			cout << "\n"<<endl;
			break;

		case 2://����Ԫ��
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

		case 3://��ѯԪ��
			cout << "Please input key which searched: ";
			cin >> temp;
			if (Tree.Search(temp, Tree.GetRoot()))
				cout << "search success!" <<"\n"<< endl;
			else
				cout << temp << " not exist!" <<"\n"<< endl;
			break;

		case 4://�˳�����
			flag = 0;
			break;
		}
	}
	return 0;
}