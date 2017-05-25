#include"Tree.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

//Ѱ�Ҹ���ʹ֮��Ϊ��ǰ���
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

//ʹ��ǰ���ĵ�һ�����ӽڵ��Ϊ��ǰ���
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

//ʹ��ǰ�����ֵܽڵ��Ϊ��ǰ���
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

//�ڸ�Ϊr������Ѱ������Ϊname�Ľڵ㣬ʹ֮��Ϊ��ǰ��㣨�ڲ����ã�
bool Tree::Find(TreeNode* r, string name)
{
	bool result = false;
	if (r->data == name)//�����жϸ����
	{ 
		result = true;
		current = r; 
	}
	else//���ڵ㲻����ʱ�����������ӽڵ�
	{
		TreeNode *temp = r->firstChild;
		while (temp != NULL && !(result = Find(temp, name)))
			temp = temp->nextSibling;
	}
	return result;
}

//sʹ����Ϊname�Ľڵ��Ϊ��ǰ��㣨�ⲿ���ã�
bool Tree::FindNode(string name)
{
	if (IsEmpty())return false;
	return Find(root, name);
}

//�ڸ�Ϊr��������s�ĸ��ڵ㣬ʹ֮��Ϊ��ǰ��㣨�ڲ����ã�
bool Tree::Parent(TreeNode *r, TreeNode *s)
{
	bool result;

	TreeNode *temp = r->firstChild;//�Ӹ��ڵ�ĵ�һ�����ӽڵ㿪ʼ��������²���
	while (temp != NULL && temp != s)//ÿһ�㣬�ݹ����s�ڵ�
	{
		result = Parent(temp, s);
		if (result == true)return true;
		temp = temp->nextSibling;//���������ֵܽڵ�
	}

	if (temp != NULL&&temp == s)//�ҵ�s���
	{
		current = r;//ʹs�ڵ�ĸ��ڵ��Ϊ��ǰ���
		return true;
	}

	else 
	{
		current = NULL;//δ�ҵ�s�ڵ�
		return false;
	}
}

//ʹ��ǰ���ĸ��ڵ��Ϊ��ǰ��㣨�ⲿ���ã�
bool Tree::FindParent() 
{
	TreeNode *r = current;
	if (r == NULL || r== root)//�ж��Ƿ�Ϊ�սڵ���߸��ڵ�
	{
		current = NULL;
		return false;
	}
	return Parent(root, r);
}

//���Ľڵ�����
void Tree::ChangeName(string &oriName,string &nowName)
{
	while(FindNode(oriName))//����Ҫ�޸������Ľڵ�
	{
		current->data = nowName;//�޸�
	}
}

//����ָ�����ڵ�����е����ӽڵ�
void Tree::AddChild(const string& name, vector<string>& childs)
{
	if (FindNode(name))//���Ȳ��ҵ����ڵ�����λ��
	{
		int count = 0;//����ͳ���Ѿ�����ĺ��ӽڵ�ĸ���

		if (current->firstChild != NULL)//���ڵ��Ѿ��е�һ������ʱ
		{
			current = current->firstChild;
			while (current->nextSibling!=NULL)//��ǰָ��һֱ�ƶ������Բ����ֵܽڵ��λ��
			{
				current = current->nextSibling;
			}
		}
		else
		{
			current->firstChild = new TreeNode(childs[0]);//���ڵ�û�е�һ�����ӽڵ�ʱ
			count = 1;//��ʱ�Ѳ����һ�����ӽڵ�
			current = current->firstChild;//��ǰָ���ƶ�����һ�����ӽڵ�
		}

		for (;count<childs.size();count++)//�ڿ��Բ����ֵܽڵ��λ�ã����β��������ֵܽڵ�
		{
			current->nextSibling = new TreeNode(childs[count]);
			current = current->nextSibling;
		}
	}
}

//ɾ����nameΪ���ĸ��ڵ㼰����Ů������ɾ�����ֵܽڵ㣩
void Tree::DeleteSubTree(const string& name)
{
	if (FindNode(name))//�����ҵ��ڵ�node���ڵ�λ��
	{
		DeleteAll(current->firstChild);//ɾ����һ�����ӽڵ�Ϊ����ȫ������
		auto temp = current;
		if (FindParent())//�����ڵ㲻Ϊ�����ʱ�����ҵ����׽ڵ㣩
		{
			if (current->firstChild->data == name)//���ɾ�����ǵ�һ�����ӽڵ�
				current->firstChild = temp->nextSibling;
			else//ɾ����Ϊ�ֵܽڵ�ʱ
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
		else//��nodeΪ�����ʱ
		{
			root = temp->nextSibling;//���ֵܽڵ��Ϊ�����
		}
		delete temp;//ɾ����ǰ�ڵ�node
	}
}

//�ݹ��㷨ɾ����nodeΪ������ȫ���������ⲿ���ã�
void Tree::DeleteAll(TreeNode* node)
{
	if (node == NULL)return;//��ǰ�ڵ�Ϊʱ����
	if (node->firstChild != NULL)//�ݹ�ɾ�����е�һ�����ӽڵ�
	{
		DeleteAll(node->firstChild);
	}
	if (node->nextSibling != NULL)//�ݹ�ɾ�����е��ֵܽڵ�
	{
		DeleteAll(node->nextSibling);
	}
	delete node;//ɾ����ǰ���ڵ�
}

//���ָ���ڵ�ĵ�һ������
void Tree::Output(string& name)
{
	TreeNode* node;
	if (FindNode(name))
	{
		node = current;
		cout << node->data << "�ĵ�һ�������ǣ�";
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