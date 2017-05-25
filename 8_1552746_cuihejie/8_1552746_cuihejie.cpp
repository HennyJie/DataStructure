//=======================================================交互界面的函数和主函数的实现============================================================
#include "MinSpanTree.h"
#include <iostream>
#include <iomanip>
using namespace std;

//建立系统时的交互界面
void OutputUI()
{
	cout << left;
	cout << setw(20) << "**" << setw(30) << "电网造价模拟系统" << "**" << endl;
	cout << "====================================================" << endl;
	cout << setw(19) << "**" << setw(31) << "A---创建电网顶点" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "B---添加电网的边" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "C---构造最小生成树" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "D---显示最小生成树" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "E---退出  程序" << "**" << endl;
	cout << "====================================================" << endl;
}

int main()
{
	OutputUI();
	MinSpanTree minSpanTree;
	int flag = 1;
	while (flag)//flag为0时，退出程序
	{
		cout << "\n请选择操作：";
		char choice;
		cin >> choice;
		switch (choice)
		{
		case'A':
			minSpanTree.SetVertex();//读入顶点
			break;
		case'B':
			minSpanTree.SetEdge();//读入带权边
			break;
		case'C':
			minSpanTree.Prim();//生成最小生成树
			break;
		case'D':
			minSpanTree.Output();//打印最小生成树
			break;
		case'E':
			flag = 0;//退出程序
			break;
		default:
			continue;
		}
	}
	getchar();
	getchar();
	return 0;
}