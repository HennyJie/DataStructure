#include "String.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//�ж�����Ԫ���Ƿ�Ϊ�ַ���
bool String::IsChar(char c)
{
	if ((c >= 'A'&&c <= 'Z') || (c >= 'a'&&c <= 'z'))
	{
		return true;
	}
	else
		return false;
}

//�����Զ����String��
String::String(string para)
{
	int i;
	maxSize = para.length();
	ch = new char[maxSize + 1];
	if (!ch)
	{
		cout << "Allocation error!" << endl;
		exit(1);
	}
	length = para.length();
	for (i = 0; i < para.length()+1; i++)
	{
		ch[i] = para[i];
	}
}

//����next(j)���㷨
void String::SetNext()
{
	int j = 0, k = -1, lengthP = length;
	next[0] = -1;
	while (j < lengthP)
	{
		if (k == -1 || ch[j] == ch[k])
		{
			j++;
			k++;
			next[j] = k;
		}
		else k = next[k];
	}
}

//����ģʽƥ��BF�㷨���ڶ����м����ؼ���key���ֵĴ���
int String::BF_Find(String& key)
{
	int i, j, count=0;
	for (i = 0; i < length - key.GetLength(); i++)//���䳤��
	{
		int flag = 0;
		for (j = 0; j < key.GetLength(); j++)//key����
		{
			if (ch[i + j] != key.ch[j])//����ֲ�������־Ϊ��1��
			{
				flag = 1;
				break;
			}
		}
		//������key.GetLength()λһֱ��ȣ����������һ��ͬʱi����ƶ�jλ
		if ( !flag && j == key.GetLength() && IsChar(ch[i+j])==false )
		{
				count++;
				i += j;
		}
	}
	return count;//���س��ִ���
}

//�Ľ�ģʽƥ��KMP�㷨���ڶ����м����ؼ���key���ֵĴ���
int String::KMP_Find(String& key,int next[])
{
	int posP = 0, posT = 0;//��������ɨ��ָ��
	int count = 0;//����
	int lengthT = length;//ģʽ��Ŀ�괮�ĳ���
	int lengthP = key.GetLength();
	while (posT < lengthT - lengthP)
	{
		while (posP < lengthP && posT < lengthT)//������ɨ��
		{
			if (posP == -1 || key.ch[posP] == ch[posT])//��Ӧ�ַ�ƥ��
			{
				posP++;
				posT++;
			}
			else posP = next[posP];
		}
		if (posP >= lengthP && IsChar(ch[posT]) == false)//ƥ��ɹ�
			count++;
		posP = 0;//ģʽָ��ص����
	}
	return count;
}

//��������������������Զ�����ַ�����
istream& operator >> (istream &is, String &str)
{
	char temp[10000];
	is >> temp;
	str.SetLength (strlen(temp));
	str.ch = new char[str.GetLength() + 1];
	strcpy(str.ch, temp);
	return is;
}

//������������<<,����Զ�����ַ�����
ostream& operator <<(ostream &os, String &str)
{
	os << str.ch;
	return os;
}


int main()
{
	char fname[100];
	char temp[100];
	int result,wordSize;
	string paragraph,key;
	int choice;
	cout << "�ؼ��ּ���ϵͳ��\n" << endl;
	cout << "�������ļ�����";
	cin >> fname;
	cout << "������һ��Ӣ�ģ�" << endl;
	
	ofstream outfile(fname);//�����
	ifstream infile(fname);//������
	getchar();
	getline(cin, paragraph);//�����������
	outfile << paragraph;//�������fname�������ļ���
	outfile.close();
	String passage(paragraph);//�����Զ�����ַ�����

	cout << "\n�����ı��ѱ������ļ�\"" << fname << "\"��!" << endl;
	cout << "\n������Ҫ���ҵĹؼ��֣�";
	cin >> key;
	String keyWord(key);//�����Զ�����ַ�����

	cout << "\n��ѡ���ַ���ƥ����㷨(1��������ģʽƥ��B-F�㷨��2����Ľ�ģʽƥ��KMP�㷨����";//�����㷨ʵ��ģʽƥ�����
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "\n��ʾԴ�ļ�\"" << fname << "\" :" << endl;
		cout << paragraph;
		result = passage.BF_Find(keyWord);//��������ģʽƥ��BF�㷨
		break;

	case 2:
		cout << "\n��ʾԴ�ļ�\"" << fname << "\" :" << endl;
		cout << paragraph;
		passage.SetNext();//����next(j)
		result = passage.KMP_Find(keyWord,passage.GetNext());//���øĽ�ģʽƥ��KMP�㷨
		break;

	default:
		break;
	}
	cout << "\n"<<endl;
	cout << "��Դ�ļ��й��ҵ�" << result << "��" << "\"" << key << "\"" << endl;

	getchar();
	getchar();
	return 0;
}