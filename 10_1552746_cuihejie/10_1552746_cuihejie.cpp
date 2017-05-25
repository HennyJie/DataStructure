#include<iostream>
#include<iomanip>
#include<ctime>
#include <string>
#include"Sort.h"
using namespace std;

void OutputUI()
{
	cout << left;
	cout << setw(20) << "**" << setw(30) << "排序算法比较" << "**" << endl;
	cout << "====================================================" << endl;
	cout << setw(19) << "**" << setw(31) << "1---冒泡排序" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "2---选择排序" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "3---直接插入排序" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "4---希尔排序" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "5---快速排序" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "6---堆排序" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "7---归并排序" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "8---基数排序" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "9---折半插入排序" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "10---锦标赛排序" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "11---退出程序" << "**" << endl;

	cout << "====================================================" << endl;
}

//产生随机数
void CreateData(DataList<int>& dataList)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < dataList.maxSize; i++)
	{
		dataList[i] = rand() % 1000000;
	}
}

//运行
void Run(Sort<int>& sort)
{
	int choice;
	int flag = 1;
	int size;
	cout << left;
	cout << "请输入要产生随机数的个数：";
	cin >> size;
	DataList<int> dataList(size);
	CreateData(dataList);
	string name;
	while (flag)
	{
		sort.compareTimes = 0;
		sort.runtime = 0;
		cout << endl;
		cout << setw(24) << "请选择排序算法： ";
		cin >> choice;
		DataList<int> sortVector(dataList);

		switch (choice)
		{
		case 1:
			name = "冒泡";
			sort.BubbleSort(sortVector);
			break;
		case 2:
			name = "选择";
			sort.SelectSort(sortVector);
			break;
		case 3:
			name = "直接插入";
			sort.InsertSort(sortVector);
			break;
		case 4:
			name = "希尔";
			sort.ShellSort(sortVector);
			break;
		case 5:
			name = "快速";
			sort.QuickSort(sortVector, 0, dataList.maxSize - 1);
			break;
		case 6:
			name = "堆";
			sort.HeapSort(sortVector);
			break;
		case 7:
			name = "归并";
			sort.MergeSort(sortVector);
			break;
		case 8:
			name = "基数";
			sort.RadixSort(sortVector);
			break;
		case 9:
			name = "折半插入";
			sort.BinaryInsertSort(sortVector);
			break;
		case 10:
			name = "锦标赛";
			sort.TournamentSort(sortVector);
			break;
		case 11:
			flag = 0;
			break;
		}
		if (flag != 0)
		{
			cout << setw(24) << name + "排序所用时间： " << (double)(sort.runtime) / CLOCKS_PER_SEC << "s" << endl;
			cout << setw(24) << name + "排序交换次数： " << sort.compareTimes << endl;
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

