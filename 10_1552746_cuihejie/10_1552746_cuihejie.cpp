#include<iostream>
#include<iomanip>
#include<ctime>
#include <string>
#include"Sort.h"
using namespace std;

void OutputUI()
{
	cout << left;
	cout << setw(20) << "**" << setw(30) << "�����㷨�Ƚ�" << "**" << endl;
	cout << "====================================================" << endl;
	cout << setw(19) << "**" << setw(31) << "1---ð������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "2---ѡ������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "3---ֱ�Ӳ�������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "4---ϣ������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "5---��������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "6---������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "7---�鲢����" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "8---��������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "9---�۰��������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "10---����������" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "11---�˳�����" << "**" << endl;

	cout << "====================================================" << endl;
}

//���������
void CreateData(DataList<int>& dataList)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < dataList.maxSize; i++)
	{
		dataList[i] = rand() % 1000000;
	}
}

//����
void Run(Sort<int>& sort)
{
	int choice;
	int flag = 1;
	int size;
	cout << left;
	cout << "������Ҫ����������ĸ�����";
	cin >> size;
	DataList<int> dataList(size);
	CreateData(dataList);
	string name;
	while (flag)
	{
		sort.compareTimes = 0;
		sort.runtime = 0;
		cout << endl;
		cout << setw(24) << "��ѡ�������㷨�� ";
		cin >> choice;
		DataList<int> sortVector(dataList);

		switch (choice)
		{
		case 1:
			name = "ð��";
			sort.BubbleSort(sortVector);
			break;
		case 2:
			name = "ѡ��";
			sort.SelectSort(sortVector);
			break;
		case 3:
			name = "ֱ�Ӳ���";
			sort.InsertSort(sortVector);
			break;
		case 4:
			name = "ϣ��";
			sort.ShellSort(sortVector);
			break;
		case 5:
			name = "����";
			sort.QuickSort(sortVector, 0, dataList.maxSize - 1);
			break;
		case 6:
			name = "��";
			sort.HeapSort(sortVector);
			break;
		case 7:
			name = "�鲢";
			sort.MergeSort(sortVector);
			break;
		case 8:
			name = "����";
			sort.RadixSort(sortVector);
			break;
		case 9:
			name = "�۰����";
			sort.BinaryInsertSort(sortVector);
			break;
		case 10:
			name = "������";
			sort.TournamentSort(sortVector);
			break;
		case 11:
			flag = 0;
			break;
		}
		if (flag != 0)
		{
			cout << setw(24) << name + "��������ʱ�䣺 " << (double)(sort.runtime) / CLOCKS_PER_SEC << "s" << endl;
			cout << setw(24) << name + "���򽻻������� " << sort.compareTimes << endl;
		}
	}
}

int main()
{
	OutputUI();
	Sort<int> sort;
	Run(sort);
	return 0;
}

