//=============================================================节点类和二叉搜索树类=========================================================================
#ifndef _BSORT_TREE_
#define _BSORT_TREE_
#include <iostream>
using namespace std;

//二叉搜索树节点
struct BsortNode
{
	int data;//数据域
	BsortNode *left, *right;//左子女和右子女

	BsortNode():left(NULL),right(NULL){}
	BsortNode(int da,BsortNode *l=NULL,BsortNode *r=NULL):data(da),left(l),right(r){}
	~BsortNode(){}
	void SetData(int da) { data = da; }//设置数据域
	int GetData() { return data; }//返还数据域
};

//二叉搜索树类
class BsortTree
{
private:
	BsortNode *root=NULL;//二叉搜索树的根指针
	int RefValue = 0;//停止输入标志

public:
	BsortTree() {}//构造函数
	~BsortTree() { Delete(root); }//析构函数
	void FormTree();//生成二叉搜索树
	bool Search(const int value, BsortNode *ptr);//递归搜索
	bool Insert(const int value, BsortNode *&ptr);//递归插入
	void PrintTree(BsortNode *ptr);//中序遍历显示二叉搜索树
	BsortNode*& GetRoot() { return root; }//获得根指针
	void Delete(BsortNode *ptr);//删除以ptr为根结点的子树
};
#endif 
