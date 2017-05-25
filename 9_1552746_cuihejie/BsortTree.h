//=============================================================�ڵ���Ͷ�����������=========================================================================
#ifndef _BSORT_TREE_
#define _BSORT_TREE_
#include <iostream>
using namespace std;

//�����������ڵ�
struct BsortNode
{
	int data;//������
	BsortNode *left, *right;//����Ů������Ů

	BsortNode():left(NULL),right(NULL){}
	BsortNode(int da,BsortNode *l=NULL,BsortNode *r=NULL):data(da),left(l),right(r){}
	~BsortNode(){}
	void SetData(int da) { data = da; }//����������
	int GetData() { return data; }//����������
};

//������������
class BsortTree
{
private:
	BsortNode *root=NULL;//�����������ĸ�ָ��
	int RefValue = 0;//ֹͣ�����־

public:
	BsortTree() {}//���캯��
	~BsortTree() { Delete(root); }//��������
	void FormTree();//���ɶ���������
	bool Search(const int value, BsortNode *ptr);//�ݹ�����
	bool Insert(const int value, BsortNode *&ptr);//�ݹ����
	void PrintTree(BsortNode *ptr);//���������ʾ����������
	BsortNode*& GetRoot() { return root; }//��ø�ָ��
	void Delete(BsortNode *ptr);//ɾ����ptrΪ����������
};
#endif 
