#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <vector>
using namespace std;
 
//树的节点
struct TreeNode
{
	string data;//数值域
	TreeNode *firstChild;//第一个孩子节点指针域
	TreeNode *nextSibling;//下一个兄弟节点指针域

	//构造函数
	TreeNode(string name, TreeNode *fc = NULL,TreeNode *ns=NULL):
		data(name),firstChild(fc),nextSibling(ns){}
};

//树类
class Tree
{
private:
	TreeNode *root;//根结点指针
	TreeNode *current;//当前结点指针

	//供公有函数部分内部调用的函数
	bool Parent(TreeNode *r, TreeNode *s);//在根为r的树中找s的父节点，使之成为当前结点
	bool Find(TreeNode* r, string name);//在根为r的树中寻找姓名为name的节点，使之成为当前结点
    void DeleteAll(TreeNode* node);//删除以node为根节点的全部子树

public:
	Tree() { root = current = NULL; }//构造函数，建立空树
	Tree(string& ancestor) { root = new TreeNode(ancestor); }//构造函数
	~Tree() { DeleteAll(root);}//析构函数
	bool IsEmpty() { return root == NULL; }//判空树

	bool Root();//寻找根，使之成为当前结点
	bool FirstChild();//使当前结点的第一个孩子节点成为当前结点
	bool NextSibling();//使当前结点的兄弟节点成为当前结点
	bool FindNode(string name);//使姓名为name的节点成为当前结点
	bool FindParent();//使当前结点的父节点成为当前结点

	void AddChild(const string& name,vector<string>&childs);//加入一个新的节点
	void ChangeName(string &oriName,string &nowName);//更改节点姓名
	void DeleteSubTree(const string& name);//删除以node为根结点的树的儿子节点
	
	void Output(string& name);//输出指定节点的第一代子孙

};
#endif 

