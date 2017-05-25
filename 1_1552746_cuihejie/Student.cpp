//==================================ʵ�����и���������===============================================
#include "Student.h"
using namespace std;

//===================================�ڵ��ຯ��ʵ��==================================================
void StudentNode::operator=(StudentNode& stu)//��������� ��=��
{
	idnum = stu.idnum;
	name = stu.name;
	gender = stu.gender;
	age = stu.age;
	type = stu.type;
}

void StudentNode::SetNext(StudentNode* ptr)//������һ���ڵ�
{
	link = ptr;
}

void StudentNode::Input()//����ڵ���Ϣ
{
	int idnum, age;
	string name, gender, type;
	cin >> idnum >> name >> gender >> age >> type;
	StudentNode* stu;
	stu = new StudentNode(idnum, name, gender, age, type);
	return;
}

void StudentNode::Output()//����ڵ���Ϣ
{
	cout << idnum << '\t' << name << '\t' << gender << '\t' << age << '\t' << type << endl;
}

//=====================================�����ຯ��ʵ��=================================================
StudentList::StudentList()//���캯��
{
	//���յĸ���ͷ�ڵ㣬�����ڿձ��ǿձ��һ���ڵ�֮ǰ�Ĳ���ɲ��������������
	first = new StudentNode();
	last = first;
	size = 0;
}
StudentList::~StudentList()//��������
{
	Delete();
}
void StudentList::Delete()//ɾ������
{
	StudentNode* ptr;  
	while (first!= nullptr)
	{
		ptr = first;
		first = ptr->link;
		delete ptr;
	}
}
bool StudentList::PushBack(StudentNode& stu)//����β����������
{
	last->link = &stu;
	last=&stu;
	size++;
	return true;
}

bool StudentList::Insert(StudentNode& stu, int pos)//����
{
	//�ж�λ���Ƿ����
	if(pos>size+1 || pos<=0)
	{ 
		return false;
	}
	//���Ҷ�Ӧλ��
	StudentNode* ptr = first;//�Ӹ���ͷ������һ����ʼ����
	pos--;
	while (pos--)
	{
		ptr = ptr->link;
	}
	//�������в���ڵ�
	stu.SetNext( ptr->link);
	ptr->SetNext(&stu);

	size++;
	return true;
}

bool StudentList::Remove(StudentNode& stu, int id)//ɾ��
{
	StudentNode *del, *current, *pre;
	pre = first;
	current = first->link;//�ӵ�һ���յĸ���ͷ�ڵ����һ����ʼ����
	bool flag = 0;

	while (current->link!= nullptr)
	{
		if (current->idnum == id)//�ҵ��ÿ��Ŷ�Ӧ�Ľڵ�
		{
			del = current;
			pre->link = del->link;
			stu = *del;//�������صġ�=����ֵ
			delete del;
			flag = 1;//��ʾ�ɹ�ɾ���ڵ�
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

StudentNode* StudentList::Search(StudentNode& stu, int id)//����
{
	StudentNode* ptr = first->link;//�ӵ�һ���յĸ���ͷ�ڵ����һ����ʼ����
	while (ptr != nullptr)
	{
		if (ptr->idnum == id)//���ҵ���Ӧѧ��
		{
			stu = *ptr;//�������صġ�=����ֵ
			break;
		}
		ptr = ptr->link;
	}
	return &stu;//���ز��ҵ���ֵ
}

bool StudentList::Reset(StudentNode& stu, int id)//�޸�
{
	StudentNode* ptr = first->link;//�ӵ�һ���յĸ���ͷ�ڵ����һ����ʼ����
	while (ptr != nullptr)
	{
		if (ptr->idnum == id)
		{
			*ptr = stu;//�������صġ�=����ֵ
			return true;
		}
		ptr = ptr->link;
	}
	return false;
}

int StudentList::Count(string& dataType)//ͳ��
{
	int typeNum = 0;
	StudentNode* ptr = first->link;//�ӵ�һ���յĸ���ͷ�ڵ����һ����ʼ����
	while (ptr != nullptr)
	{
		if (ptr->type == dataType)//�ڵ����ͷ�������������
		{
			typeNum++;
		}
		ptr = ptr->link;
	}
	return typeNum;
}

void StudentList::Output()//�������
{
	cout << "����\t����\t�Ա�\t����\t�������" << endl;
	StudentNode* ptr = first->link;
	while (ptr != nullptr)
	{
		ptr->Output();
		ptr = ptr->link;
	}
}