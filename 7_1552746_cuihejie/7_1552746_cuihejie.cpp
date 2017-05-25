#include "Tree.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <stack>

using namespace std;

//�Ƴ�ĳ������
void BinaryTree::Remove(TreeNode* node)
{
	if (node == NULL)return;
	if (node->leftChild != NULL)
	{
		Remove(node->leftChild);
	}
	if (node->rightChild != NULL)
	{
		Remove(node->rightChild);
	}
	delete node;
}

//��chΪ����������򴴽���֧
void BinaryTree::CreateBunch(string ch, stack<TreeNode*> &nodeStack)
{
	TreeNode* bunch = new TreeNode(ch);
	bunch->rightChild = nodeStack.top();
	nodeStack.pop();
	bunch->leftChild = nodeStack.top();
	nodeStack.pop();
	nodeStack.push(bunch);
}

//���ַ�ת��Ϊ�ַ������ɼ���10���ϵ����֣�
string ChangeChar2Stirng(char ch)
{
	char st[] = { ch,'\0' };//�ַ�����
	string str(st);//���ַ����鹹��string
	return str;
}

//������׺���ʽ����������
TreeNode* BinaryTree::CreateBinTree(string s)
{
	stack<string> operStack;//�����ջ
	stack<TreeNode*> nodeStack;//�������ڵ�ջ
	int i=0;

	while (s[i] != '\0')
	{
		if (s[i] >= '0'&&s[i] <= '9')//������
		{
			string num = ChangeChar2Stirng(s[i]);//�ַ�ת�ַ���
			while (s[i+1] >= '0'&&s[i+1] <= '9')//10���ϵ�����
			{
				num = num + s[i+1];
				i++;
			}
			TreeNode* node = new TreeNode(num);
			nodeStack.push(node);
		}
		else if (s[i] == '+' || s[i] == '-')//�Ӽ���
		{
			while (!operStack.empty())
			{
				CreateBunch(operStack.top(), nodeStack);
				operStack.pop();
			}
			operStack.push(ChangeChar2Stirng(s[i]));
		}
		else if (s[i] == '*' || s[i] == '/')//�˳���
		{
			if (operStack.empty() ||  operStack.top()== "+"  || operStack.top() == "-")
				operStack.push(ChangeChar2Stirng(s[i]));
			else
			{
				CreateBunch(operStack.top(), nodeStack);
				operStack.pop();
				operStack.push(ChangeChar2Stirng(s[i]));
			}
		}
		else if (s[i] == '(')//������
		{
			int num = 1;
			int start = i;
			while (num)
			{
				i++;
				if (s[i] == ')')num--;
				if (s[i] == '(')num++;
			}
			//�ó������в��֣��ݹ���ô����������ĺ���
			TreeNode* bunchTree = CreateBinTree(s.substr(start + 1, i - start - 1));
			bunchTree->isBracket = true;//��Ǹýڵ���Ŵ���������
			nodeStack.push(bunchTree);
		}
		i++;
	}
	while (!operStack.empty())
	{
		CreateBunch(operStack.top(), nodeStack);
		operStack.pop();
	}
	return nodeStack.top();
}

void BinaryTree::preOrder(TreeNode *node)//ǰ�����
{
	if (node != NULL)
	{
		cout << node->data << " ";
		preOrder(node->leftChild);
		preOrder(node->rightChild);
	}
}

void BinaryTree::inOrder(TreeNode *node)//�������
{
	if (node != NULL)
	{
		if (node->isBracket)cout << "(";
		inOrder(node->leftChild);
		cout << node->data <<" ";
		inOrder(node->rightChild);
		if (node->isBracket)cout << ")";
	}
}

void BinaryTree::postOrder(TreeNode *node)//�������
{
	if (node != NULL)
	{
		postOrder(node->leftChild);
		postOrder(node->rightChild);
		cout << node->data << " ";
	}
}

int main()
{
	cout << left;
	cout << setw(16) << "��������ʽ��";
	string s;
	cin >> s;
	BinaryTree Tree(s);
	cout << endl;

	cout << setw(16) << "�������ʽ��";
	Tree.preOrder(Tree.GetRoot());
	cout <<"\n"<< endl;

	cout << setw(16) << "��׺���ʽ��";
	Tree.inOrder(Tree.GetRoot());
	cout << "\n" << endl;

	cout << setw(16) << "�沨�����ʽ��";
	Tree.postOrder(Tree.GetRoot());
	cout << "\n" << endl;
	getchar();
	getchar();
	return 0;
}