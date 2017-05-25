//-----------------------------------该头文件定义节点类StudentNode和链表类StudentList--------------------------------------
#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <iostream>
#include <string>

using namespace std;

struct StudentNode//节点类
{
	int idnum;
	string name;
	string gender;
	int age;
	string type;
	StudentNode* link=nullptr;

	StudentNode(){}//默认构造函数
	~StudentNode() {}//析构函数
	StudentNode(int dataNum,string dataName,string dataGender,int dataAge,string dataType):
		idnum(dataNum),name(dataName),gender(dataGender),age(dataAge),type(dataType){}//构造函数
	
	void operator=(StudentNode& stu);//重载运算符 “=”
	void SetNext(StudentNode* ptr);//设置下一个节点

	void Input();//输入节点信息
	void Output();//输出节点信息
};

class StudentList//链表类
{
private:
	StudentNode* first;//头节点
	StudentNode* last;//尾节点
	int size;//链表中节点总数

public:
	StudentList();//构造函数
	~StudentList();//析构函数
	void Delete();//删除链表

	//5大功能实现函数
	bool PushBack(StudentNode& stu);//链表尾部插入数据
	bool Insert(StudentNode& stu, int pos);//根据位置插入节点
	bool Remove(StudentNode& stu, int idnum);//根据学号删除对应节点
	StudentNode* Search(StudentNode& stu, int idnum);//根据学号查找对应节点
	bool Reset(StudentNode& stu, int idnum);//根据学号修改对应节点
	int Count(string& type);//根据报考类型，统计该类型考生数目

	void Output();//输出整个链表的信息
};

#endif 

