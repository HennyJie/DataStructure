#include "Tree.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <stack>

using namespace std;

//移除某个子树
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

//以ch为根结点数据域创建分支
void BinaryTree::CreateBunch(string ch, stack<TreeNode*> &nodeStack)
{
	TreeNode* bunch = new TreeNode(ch);
	bunch->rightChild = nodeStack.top();
	nodeStack.pop();
	bunch->leftChild = nodeStack.top();
	nodeStack.pop();
	nodeStack.push(bunch);
}

//将字符转化为字符串（可兼容10以上的数字）
string ChangeChar2Stirng(char ch)
{
	char st[] = { ch,'\0' };//字符数组
	string str(st);//用字符数组构造string
	return str;
}

//利用中缀表达式创建二叉树
TreeNode* BinaryTree::CreateBinTree(string s)
{
	stack<string> operStack;//运算符栈
	stack<TreeNode*> nodeStack;//二叉树节点栈
	int i=0;

	while (s[i] != '\0')
	{
		if (s[i] >= '0'&&s[i] <= '9')//操作数
		{
			string num = ChangeChar2Stirng(s[i]);//字符转字符串
			while (s[i+1] >= '0'&&s[i+1] <= '9')//10以上的数字
			{
				num = num + s[i+1];
				i++;
			}
			TreeNode* node = new TreeNode(num);
			nodeStack.push(node);
		}
		else if (s[i] == '+' || s[i] == '-')//加减号
		{
			while (!operStack.empty())
			{
				CreateBunch(operStack.top(), nodeStack);
				operStack.pop();
			}
			operStack.push(ChangeChar2Stirng(s[i]));
		}
		else if (s[i] == '*' || s[i] == '/')//乘除号
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
		else if (s[i] == '(')//左括号
		{
			int num = 1;
			int start = i;
			while (num)
			{
				i++;
				if (s[i] == ')')num--;
				if (s[i] == '(')num++;
			}
			//拿出括号中部分，递归调用创建二叉树的函数
			TreeNode* bunchTree = CreateBinTree(s.substr(start + 1, i - start - 1));
			bunchTree->isBracket = true;//标记该节点符号处于括号内
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

void BinaryTree::preOrder(TreeNode *node)//前序遍历
{
	if (node != NULL)
	{
		cout << node->data << " ";
		preOrder(node->leftChild);
		preOrder(node->rightChild);
	}
}

void BinaryTree::inOrder(TreeNode *node)//中序遍历
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

void BinaryTree::postOrder(TreeNode *node)//后序遍历
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
	cout << setw(16) << "请输入表达式：";
	string s;
	cin >> s;
	BinaryTree Tree(s);
	cout << endl;

	cout << setw(16) << "波兰表达式：";
	Tree.preOrder(Tree.GetRoot());
	cout <<"\n"<< endl;

	cout << setw(16) << "中缀表达式：";
	Tree.inOrder(Tree.GetRoot());
	cout << "\n" << endl;

	cout << setw(16) << "逆波兰表达式：";
	Tree.postOrder(Tree.GetRoot());
	cout << "\n" << endl;
	getchar();
	getchar();
	return 0;
}