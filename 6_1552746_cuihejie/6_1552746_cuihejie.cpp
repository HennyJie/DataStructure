#include"Tree.h"
#include<iomanip>
#include <string>
using namespace std;

//����ϵͳʱ��ʾ����
void OutputUI()
{
	cout << left;
	cout << setw(20) << "**" << setw(30) << "���׹���ϵͳ" << "**"<<endl;
	cout << "====================================================" << endl;
	cout << setw(17) << "**" << setw(33) << "��ѡ��Ҫִ�еĲ�����" << "**" << endl;
	cout << setw(19)<< "**" << setw(31) << "A---���Ƽ�ͥ" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "B---��Ӽ�ͥ��Ա" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "C---��ɢ�ֲ���ͥ" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "D---���ļ�ͥ��Ա����" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "E---�˳�����" << "**" << endl;
	cout << "====================================================" << endl;
}


int main()
{
	OutputUI();//����ϵͳ����ʾ����
	cout << "���Ƚ���һ�����ף�" << endl;
	cout << "���������ȵ�������";
	string ancestorName, fatherName, childName;
	string oriName, nowName;//�޸�������
	int num;
	vector<string> childs;//ĳһ���ڵ��ȫ����Ů

	cin >> ancestorName;
	cout << "�˼��׵������ǣ�" << ancestorName << endl;
	Tree familyTree(ancestorName);//���������

	int flag = 1;
	while (flag)//flagΪ1ʱϵͳ��������
	{
		cout << endl;
		cout << "��ѡ��Ҫִ�еĲ�����";
		char choice;
		cin >> choice;
		childs.clear();//ÿ��ѭ��ǰ�����vector
		switch (choice)//������ʾ������ѡ���Ӧ�Ĳ�ͬ����
		{
		case'A':
			cout << "������Ҫ������ͥ���˵�������";
			cin >> fatherName;
			cout << "������" << fatherName << "�Ķ�Ů������";
			cin >> num;
			cout << "����������" << fatherName << "�Ķ�Ů��������";

			while (num--)
			{
				cin >> childName;
				childs.push_back(childName);
			}

			familyTree.AddChild(fatherName, childs);
			familyTree.Output(fatherName);
			break;

		case'B':
			cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
			cin >> fatherName;
			cout << "������" << fatherName << "����ӵĶ��ӣ���Ů������������";
			cin >> childName;
			childs.push_back(childName);
			familyTree.AddChild(fatherName, childs);
			familyTree.Output(fatherName);
			break;

		case'C':
			cout << "������Ҫ��ɢ��ͥ���˵�������";
			cin >> fatherName;
			cout << "Ҫ��ɢ��ͥ�����ǣ�" << fatherName<<endl;
			familyTree.Output(fatherName);
			familyTree.DeleteSubTree(fatherName);
			break;

		case'D':
			cout << "������Ҫ�����������˵�Ŀǰ������";
			cin >> oriName;
			cout << "��������ĺ��������";
			cin >> nowName;
			familyTree.ChangeName(oriName, nowName);
			cout << oriName << "�Ѹ���Ϊ" << nowName;
			cout << endl;
			break;

		case'E':
			flag = 0;
			break;

		default:
			continue;
		}
	}
	getchar();
	getchar();
	return 0;
}