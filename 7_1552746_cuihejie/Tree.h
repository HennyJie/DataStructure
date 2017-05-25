#ifndef _TREE_H_
#define _TREE_H_
#include <iostream>
#include <string>
#include <stack>
#include <string>
using namespace std;

//二叉树结点类
struct TreeNode
{
	string data;
	TreeNode *leftChild, *rightChild;//指向左子节点的指针和右子节点的指针
	bool isBracket = false;//用来标记该节点运算符是否在括号内
	TreeNode(){}
	TreeNode(string ch):data(ch),leftChild(NULL),rightChild(NULL){}
};

//二叉树类
class BinaryTree
{
private:
	TreeNode *root;
public:
	BinaryTree(){}
	BinaryTree(string s) { root = CreateBinTree(s); }//构造函数
	~BinaryTree(){ Remove(root); }//析构函数
	void Remove(TreeNode* node);//释放以node为根结点的子树
	TreeNode* GetRoot() { return root; }//获得根节点

	void CreateBunch(string ch, stack<TreeNode*> &nodeStack);//以ch为根结点数据域创建分支
	TreeNode* CreateBinTree(string s);//利用中缀表达式创建二叉树

	void preOrder(TreeNode *node);//前序遍历
	void inOrder(TreeNode *node);//中序遍历
	void postOrder(TreeNode *node);//后序遍历
};
#endif 

