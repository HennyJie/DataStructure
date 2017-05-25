//-----------------------------------��ͷ�ļ�����ڵ���StudentNode��������StudentList--------------------------------------
#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <iostream>
#include <string>

using namespace std;

struct StudentNode//�ڵ���
{
	int idnum;
	string name;
	string gender;
	int age;
	string type;
	StudentNode* link=nullptr;

	StudentNode(){}//Ĭ�Ϲ��캯��
	~StudentNode() {}//��������
	StudentNode(int dataNum,string dataName,string dataGender,int dataAge,string dataType):
		idnum(dataNum),name(dataName),gender(dataGender),age(dataAge),type(dataType){}//���캯��
	
	void operator=(StudentNode& stu);//��������� ��=��
	void SetNext(StudentNode* ptr);//������һ���ڵ�

	void Input();//����ڵ���Ϣ
	void Output();//����ڵ���Ϣ
};

class StudentList//������
{
private:
	StudentNode* first;//ͷ�ڵ�
	StudentNode* last;//β�ڵ�
	int size;//�����нڵ�����

public:
	StudentList();//���캯��
	~StudentList();//��������
	void Delete();//ɾ������

	//5����ʵ�ֺ���
	bool PushBack(StudentNode& stu);//����β����������
	bool Insert(StudentNode& stu, int pos);//����λ�ò���ڵ�
	bool Remove(StudentNode& stu, int idnum);//����ѧ��ɾ����Ӧ�ڵ�
	StudentNode* Search(StudentNode& stu, int idnum);//����ѧ�Ų��Ҷ�Ӧ�ڵ�
	bool Reset(StudentNode& stu, int idnum);//����ѧ���޸Ķ�Ӧ�ڵ�
	int Count(string& type);//���ݱ������ͣ�ͳ�Ƹ����Ϳ�����Ŀ

	void Output();//��������������Ϣ
};

#endif 

