//==========================================================循环链表类函数的实现===============================================================
#include"CircleList.h"
using namespace std;

CircleList::CircleList(int n)//循环链表构造函数
{
	int i;
	amount = n;
	first=last = new CircleNode(1);

	if (n == 1)//链表长度为 1 时
	{
		first->link = first;
		return;
	}

	for (i = 2; i <= n; i++)
	{
		CircleNode *newNode = new CircleNode(i);
		last->link = newNode;
		last = newNode;
	}
	last->link = first;//首尾相连
}

CircleList::~CircleList()//删除整个循环链表
{
	int i;
	CircleNode *current;
	for (i = 0; i < amount; i++)
	{
		current = first->link;
		delete first;
		first = current;
	}
}

CircleNode* CircleList::Locate(int pos)//找到某位置节点的地址
{
	int i=1;
	if (pos < 0)return NULL;
	CircleNode *current = first;
	while (current != NULL&&i < pos)
	{
		current = current->link;
		i++;
	}
	return current;
}

int CircleList::Remove(CircleNode *&pre,CircleNode *&current)//删除当前位置的节点
{
	pre->link = current->link;
	auto temp = current->link;
	auto index = current->GetNum();
	if (current == first)
		first = current->link;
	delete current;
	current = temp;
	return index;
}

void CircleList::Output()//输出游戏结束后剩余的节点
{
	CircleNode *ptr = first;
	int i;
	cout << endl;
	cout << "最后剩下：" << amount << "人" << endl;
	cout << endl;
	cout << "剩余生者位置："<<endl;
	for (i = 0; i < amount; i++)
	{
		cout << ptr->GetNum() << "\t";
		ptr = ptr->link;
	}
}