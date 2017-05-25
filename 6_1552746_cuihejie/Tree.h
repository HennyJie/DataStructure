#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <vector>
using namespace std;
 
//���Ľڵ�
struct TreeNode
{
	string data;//��ֵ��
	TreeNode *firstChild;//��һ�����ӽڵ�ָ����
	TreeNode *nextSibling;//��һ���ֵܽڵ�ָ����

	//���캯��
	TreeNode(string name, TreeNode *fc = NULL,TreeNode *ns=NULL):
		data(name),firstChild(fc),nextSibling(ns){}
};

//����
class Tree
{
private:
	TreeNode *root;//�����ָ��
	TreeNode *current;//��ǰ���ָ��

	//�����к��������ڲ����õĺ���
	bool Parent(TreeNode *r, TreeNode *s);//�ڸ�Ϊr��������s�ĸ��ڵ㣬ʹ֮��Ϊ��ǰ���
	bool Find(TreeNode* r, string name);//�ڸ�Ϊr������Ѱ������Ϊname�Ľڵ㣬ʹ֮��Ϊ��ǰ���
    void DeleteAll(TreeNode* node);//ɾ����nodeΪ���ڵ��ȫ������

public:
	Tree() { root = current = NULL; }//���캯������������
	Tree(string& ancestor) { root = new TreeNode(ancestor); }//���캯��
	~Tree() { DeleteAll(root);}//��������
	bool IsEmpty() { return root == NULL; }//�п���

	bool Root();//Ѱ�Ҹ���ʹ֮��Ϊ��ǰ���
	bool FirstChild();//ʹ��ǰ���ĵ�һ�����ӽڵ��Ϊ��ǰ���
	bool NextSibling();//ʹ��ǰ�����ֵܽڵ��Ϊ��ǰ���
	bool FindNode(string name);//ʹ����Ϊname�Ľڵ��Ϊ��ǰ���
	bool FindParent();//ʹ��ǰ���ĸ��ڵ��Ϊ��ǰ���

	void AddChild(const string& name,vector<string>&childs);//����һ���µĽڵ�
	void ChangeName(string &oriName,string &nowName);//���Ľڵ�����
	void DeleteSubTree(const string& name);//ɾ����nodeΪ���������Ķ��ӽڵ�
	
	void Output(string& name);//���ָ���ڵ�ĵ�һ������

};
#endif 

