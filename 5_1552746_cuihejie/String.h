//=====================================================�Զ�����ַ�����===========================================================
#ifndef _STRING_H_
#define _STRING_H_

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

//�Զ����ַ�����
class String
{
private:
	char *ch;//�洢�ַ���������
	int next[2000];
	int length;//��ǰ����
	int maxSize;//��󳤶�
public:
	String(){}//Ĭ�Ϲ��캯��
	String(string passage);//�ö��������ַ��������Զ�����ַ�����
	~String() { delete[]ch; }//��������
	void SetNext();//����next(j)���㷨
	int* GetNext() { return next; }//��ȡnext����
	char* GetString(){ return ch; }//ȡ���ַ���
	int GetLength() { return length; }//��õ�ǰ����
	void SetLength(int len) { length = len; }//���õ�ǰ����
	int BF_Find(String& key);//ʹ������ģʽƥ��BF�㷨����Ŀ����ִ���
	int KMP_Find(String& key,int next[]);//ʹ������ģʽƥ��BF�㷨����Ŀ����ִ���
	bool IsChar(char c);//�ж��Ƿ�Ϊ�ַ���
	friend istream& operator >> (istream &is, String &str);//�������������
	friend ostream& operator <<(ostream &os, String &str);//������������
};
#endif

