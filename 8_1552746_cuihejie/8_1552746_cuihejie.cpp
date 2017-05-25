//=======================================================��������ĺ�������������ʵ��============================================================
#include "MinSpanTree.h"
#include <iostream>
#include <iomanip>
using namespace std;

//����ϵͳʱ�Ľ�������
void OutputUI()
{
	cout << left;
	cout << setw(20) << "**" << setw(30) << "�������ģ��ϵͳ" << "**" << endl;
	cout << "====================================================" << endl;
	cout << setw(19) << "**" << setw(31) << "A---������������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "B---��ӵ����ı�" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "C---������С������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "D---��ʾ��С������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "E---�˳�  ����" << "**" << endl;
	cout << "====================================================" << endl;
}

int main()
{
	OutputUI();
	MinSpanTree minSpanTree;
	int flag = 1;
	while (flag)//flagΪ0ʱ���˳�����
	{
		cout << "\n��ѡ�������";
		char choice;
		cin >> choice;
		switch (choice)
		{
		case'A':
			minSpanTree.SetVertex();//���붥��
			break;
		case'B':
			minSpanTree.SetEdge();//�����Ȩ��
			break;
		case'C':
			minSpanTree.Prim();//������С������
			break;
		case'D':
			minSpanTree.Output();//��ӡ��С������
			break;
		case'E':
			flag = 0;//�˳�����
			break;
		default:
			continue;
		}
	}
	getchar();
	getchar();
	return 0;
}