//=======================================================节点类和链表类的定义===============================================================
#ifndef _CIRCLELIST_H_
#define _CIRCLELIST_H_

#include <iostream>
using namespace std;

//循环链表节点类
struct CircleNode
{
	int idnum;//节点所在位置的数字
	CircleNode *link;
	CircleNode() {}//默认构造函数
	CircleNode(int n):idnum(n){}//初始化数字的构造函数
	int GetNum() { return idnum; }//取出节点中存储的数字
};

//循环链表
class CircleList
{
private:
	CircleNode *first, *last;//循环链表的头尾指针
	int amount;//链表中节点总数
public:
	CircleList(){}//默认构造函数
	CircleList(int n);//初始化链表长度的构造函数
	~CircleList();
	bool IsEmpty() { return first->link == first ? true : false; }//判断循环链表是否为空
	int GetAmount() { return amount; }//获得链表长度
	void SetAmount(int num) { amount = num; }//根据参数值设置链表长度
	CircleNode* Locate(int pos);//根据位置找某节点的地址
	int Remove(CircleNode *&pre, CircleNode *&current);//移除节点
	void Output();//输出剩余节点
};
#endif 
