//==================================实现类中各函数功能===============================================
#include "Student.h"
using namespace std;

//===================================节点类函数实现==================================================
void StudentNode::operator=(StudentNode& stu)//重载运算符 “=”
{
	idnum = stu.idnum;
	name = stu.name;
	gender = stu.gender;
	age = stu.age;
	type = stu.type;
}

void StudentNode::SetNext(StudentNode* ptr)//设置下一个节点
{
	link = ptr;
}

void StudentNode::Input()//输入节点信息
{
	int idnum, age;
	string name, gender, type;
	cin >> idnum >> name >> gender >> age >> type;
	StudentNode* stu;
	stu = new StudentNode(idnum, name, gender, age, type);
	return;
}

void StudentNode::Output()//输出节点信息
{
	cout << idnum << '\t' << name << '\t' << gender << '\t' << age << '\t' << type << endl;
}

//=====================================链表类函数实现=================================================
StudentList::StudentList()//构造函数
{
	//含空的附加头节点，这样在空表或非空表第一个节点之前的插入可不做特殊情况处理
	first = new StudentNode();
	last = first;
	size = 0;
}
StudentList::~StudentList()//析构函数
{
	Delete();
}
void StudentList::Delete()//删除链表
{
	StudentNode* ptr;  
	while (first!= nullptr)
	{
		ptr = first;
		first = ptr->link;
		delete ptr;
	}
}
bool StudentList::PushBack(StudentNode& stu)//链表尾部插入数据
{
	last->link = &stu;
	last=&stu;
	size++;
	return true;
}

bool StudentList::Insert(StudentNode& stu, int pos)//插入
{
	//判断位置是否合理
	if(pos>size+1 || pos<=0)
	{ 
		return false;
	}
	//查找对应位置
	StudentNode* ptr = first;//从附加头结点的下一个开始查找
	pos--;
	while (pos--)
	{
		ptr = ptr->link;
	}
	//单链表中插入节点
	stu.SetNext( ptr->link);
	ptr->SetNext(&stu);

	size++;
	return true;
}

bool StudentList::Remove(StudentNode& stu, int id)//删除
{
	StudentNode *del, *current, *pre;
	pre = first;
	current = first->link;//从第一个空的附加头节点的下一个开始查找
	bool flag = 0;

	while (current->link!= nullptr)
	{
		if (current->idnum == id)//找到该考号对应的节点
		{
			del = current;
			pre->link = del->link;
			stu = *del;//利用重载的“=”赋值
			delete del;
			flag = 1;//表示成功删除节点
			break;
		}
		else
		{
			current = current->link;
			pre = pre->link;
		}
	}
	return flag;
}

StudentNode* StudentList::Search(StudentNode& stu, int id)//查找
{
	StudentNode* ptr = first->link;//从第一个空的附加头节点的下一个开始查找
	while (ptr != nullptr)
	{
		if (ptr->idnum == id)//查找到对应学号
		{
			stu = *ptr;//利用重载的“=”赋值
			break;
		}
		ptr = ptr->link;
	}
	return &stu;//返回查找到的值
}

bool StudentList::Reset(StudentNode& stu, int id)//修改
{
	StudentNode* ptr = first->link;//从第一个空的附加头节点的下一个开始查找
	while (ptr != nullptr)
	{
		if (ptr->idnum == id)
		{
			*ptr = stu;//利用重载的“=”赋值
			return true;
		}
		ptr = ptr->link;
	}
	return false;
}

int StudentList::Count(string& dataType)//统计
{
	int typeNum = 0;
	StudentNode* ptr = first->link;//从第一个空的附加头节点的下一个开始查找
	while (ptr != nullptr)
	{
		if (ptr->type == dataType)//节点类型符合所查找类型
		{
			typeNum++;
		}
		ptr = ptr->link;
	}
	return typeNum;
}

void StudentList::Output()//输出链表
{
	cout << "考号\t姓名\t性别\t年龄\t报考类别" << endl;
	StudentNode* ptr = first->link;
	while (ptr != nullptr)
	{
		ptr->Output();
		ptr = ptr->link;
	}
}