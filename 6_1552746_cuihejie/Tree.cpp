#include"Tree.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

//寻找根，使之成为当前结点
bool Tree::Root()
{
	if (root == NULL)
	{
		current = NULL;
		return false;
	}
	else 
	{
		current = root;
		return true;
	}
}

//使当前结点的第一个孩子节点成为当前结点
bool Tree::FirstChild()
{
	if (current != NULL&&current->firstChild != NULL)
	{
		current = current->firstChild;
		return true;
	}
	else
	{
		current = NULL;
		return false;
	}
}

//使当前结点的兄弟节点成为当前结点
bool Tree::NextSibling()
{
	if (current != NULL&&current->nextSibling != NULL)
	{
		current = current->nextSibling;
		return true;
	}
	else
	{
		current = NULL;
		return false;
	}
}

//在根为r的树中寻找姓名为name的节点，使之成为当前结点（内部调用）
bool Tree::Find(TreeNode* r, string name)
{
	bool result = false;
	if (r->data == name)//首先判断根结点
	{ 
		result = true;
		current = r; 
	}
	else//根节点不满足时，遍历所有子节点
	{
		TreeNode *temp = r->firstChild;
		while (temp != NULL && !(result = Find(temp, name)))
			temp = temp->nextSibling;
	}
	return result;
}

//s使姓名为name的节点成为当前结点（外部调用）
bool Tree::FindNode(string name)
{
	if (IsEmpty())return false;
	return Find(root, name);
}

//在根为r的树中找s的父节点，使之成为当前结点（内部调用）
bool Tree::Parent(TreeNode *r, TreeNode *s)
{
	bool result;

	TreeNode *temp = r->firstChild;//从根节点的第一个孩子节点开始，逐层向下查找
	while (temp != NULL && temp != s)//每一层，递归查找s节点
	{
		result = Parent(temp, s);
		if (result == true)return true;
		temp = temp->nextSibling;//遍历所有兄弟节点
	}

	if (temp != NULL&&temp == s)//找到s结点
	{
		current = r;//使s节点的父节点成为当前结点
		return true;
	}

	else 
	{
		current = NULL;//未找到s节点
		return false;
	}
}

//使当前结点的父节点成为当前结点（外部调用）
bool Tree::FindParent() 
{
	TreeNode *r = current;
	if (r == NULL || r== root)//判断是否为空节点或者根节点
	{
		current = NULL;
		return false;
	}
	return Parent(root, r);
}

//更改节点姓名
void Tree::ChangeName(string &oriName,string &nowName)
{
	while(FindNode(oriName))//查找要修改姓名的节点
	{
		current->data = nowName;//修改
	}
}

//加入指定父节点的所有的新子节点
void Tree::AddChild(const string& name, vector<string>& childs)
{
	if (FindNode(name))//首先查找到父节点所在位置
	{
		int count = 0;//用来统计已经插入的孩子节点的个数

		if (current->firstChild != NULL)//父节点已经有第一个孩子时
		{
			current = current->firstChild;
			while (current->nextSibling!=NULL)//当前指针一直移动到可以插入兄弟节点的位置
			{
				current = current->nextSibling;
			}
		}
		else
		{
			current->firstChild = new TreeNode(childs[0]);//父节点没有第一个孩子节点时
			count = 1;//此时已插入第一个孩子节点
			current = current->firstChild;//当前指针移动到第一个孩子节点
		}

		for (;count<childs.size();count++)//在可以插入兄弟节点的位置，依次插入所有兄弟节点
		{
			current->nextSibling = new TreeNode(childs[count]);
			current = current->nextSibling;
		}
	}
}

//删除以name为名的父节点及其子女（不能删除其兄弟节点）
void Tree::DeleteSubTree(const string& name)
{
	if (FindNode(name))//首先找到节点node所在的位置
	{
		DeleteAll(current->firstChild);//删除第一个孩子节点为根的全部子树
		auto temp = current;
		if (FindParent())//当父节点不为根结点时（能找到父亲节点）
		{
			if (current->firstChild->data == name)//如果删除的是第一个孩子节点
				current->firstChild = temp->nextSibling;
			else//删除的为兄弟节点时
			{
				temp = current->firstChild;
				while (temp->nextSibling->data != name)
				{
					temp = temp->nextSibling;
				}
				auto nodeTemp = temp->nextSibling;
				temp->nextSibling = temp->nextSibling->nextSibling;
				temp = nodeTemp;
			}
		}
		else//当node为根结点时
		{
			root = temp->nextSibling;//其兄弟节点成为根结点
		}
		delete temp;//删除当前节点node
	}
}

//递归算法删除以node为根结点的全部子树（外部调用）
void Tree::DeleteAll(TreeNode* node)
{
	if (node == NULL)return;//当前节点为时返回
	if (node->firstChild != NULL)//递归删除所有第一个孩子节点
	{
		DeleteAll(node->firstChild);
	}
	if (node->nextSibling != NULL)//递归删除所有的兄弟节点
	{
		DeleteAll(node->nextSibling);
	}
	delete node;//删除当前父节点
}

//输出指定节点的第一代子孙
void Tree::Output(string& name)
{
	TreeNode* node;
	if (FindNode(name))
	{
		node = current;
		cout << node->data << "的第一代子孙是：";
		if (node->firstChild != NULL)
		{
			node = node->firstChild;
			cout <<setw(5)<<node->data;
			while (node->nextSibling != NULL)
			{
				node = node->nextSibling;
				cout <<setw(5)<<node->data;
			}
		}
		cout << endl;
	}
}