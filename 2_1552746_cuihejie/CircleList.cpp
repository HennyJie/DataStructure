//==========================================================ѭ�������ຯ����ʵ��===============================================================
#include"CircleList.h"
using namespace std;

CircleList::CircleList(int n)//ѭ�������캯��
{
	int i;
	amount = n;
	first=last = new CircleNode(1);

	if (n == 1)//������Ϊ 1 ʱ
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
	last->link = first;//��β����
}

CircleList::~CircleList()//ɾ������ѭ������
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

CircleNode* CircleList::Locate(int pos)//�ҵ�ĳλ�ýڵ�ĵ�ַ
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

int CircleList::Remove(CircleNode *&pre,CircleNode *&current)//ɾ����ǰλ�õĽڵ�
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

void CircleList::Output()//�����Ϸ������ʣ��Ľڵ�
{
	CircleNode *ptr = first;
	int i;
	cout << endl;
	cout << "���ʣ�£�" << amount << "��" << endl;
	cout << endl;
	cout << "ʣ������λ�ã�"<<endl;
	for (i = 0; i < amount; i++)
	{
		cout << ptr->GetNum() << "\t";
		ptr = ptr->link;
	}
}