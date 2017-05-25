#ifndef _TREE_H_
#define _TREE_H_
#include <iostream>
#include <string>
#include <stack>
#include <string>
using namespace std;

//�����������
struct TreeNode
{
	string data;
	TreeNode *leftChild, *rightChild;//ָ�����ӽڵ��ָ������ӽڵ��ָ��
	bool isBracket = false;//������Ǹýڵ�������Ƿ���������
	TreeNode(){}
	TreeNode(string ch):data(ch),leftChild(NULL),rightChild(NULL){}
};

//��������
class BinaryTree
{
private:
	TreeNode *root;
public:
	BinaryTree(){}
	BinaryTree(string s) { root = CreateBinTree(s); }//���캯��
	~BinaryTree(){ Remove(root); }//��������
	void Remove(TreeNode* node);//�ͷ���nodeΪ����������
	TreeNode* GetRoot() { return root; }//��ø��ڵ�

	void CreateBunch(string ch, stack<TreeNode*> &nodeStack);//��chΪ����������򴴽���֧
	TreeNode* CreateBinTree(string s);//������׺���ʽ����������

	void preOrder(TreeNode *node);//ǰ�����
	void inOrder(TreeNode *node);//�������
	void postOrder(TreeNode *node);//�������
};
#endif 

