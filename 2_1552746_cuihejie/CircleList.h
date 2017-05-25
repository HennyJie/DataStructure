//=======================================================�ڵ����������Ķ���===============================================================
#ifndef _CIRCLELIST_H_
#define _CIRCLELIST_H_

#include <iostream>
using namespace std;

//ѭ������ڵ���
struct CircleNode
{
	int idnum;//�ڵ�����λ�õ�����
	CircleNode *link;
	CircleNode() {}//Ĭ�Ϲ��캯��
	CircleNode(int n):idnum(n){}//��ʼ�����ֵĹ��캯��
	int GetNum() { return idnum; }//ȡ���ڵ��д洢������
};

//ѭ������
class CircleList
{
private:
	CircleNode *first, *last;//ѭ�������ͷβָ��
	int amount;//�����нڵ�����
public:
	CircleList(){}//Ĭ�Ϲ��캯��
	CircleList(int n);//��ʼ�������ȵĹ��캯��
	~CircleList();
	bool IsEmpty() { return first->link == first ? true : false; }//�ж�ѭ�������Ƿ�Ϊ��
	int GetAmount() { return amount; }//���������
	void SetAmount(int num) { amount = num; }//���ݲ���ֵ����������
	CircleNode* Locate(int pos);//����λ����ĳ�ڵ�ĵ�ַ
	int Remove(CircleNode *&pre, CircleNode *&current);//�Ƴ��ڵ�
	void Output();//���ʣ��ڵ�
};
#endif 
