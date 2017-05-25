#include"Tree.h"
#include<iomanip>
#include <string>
using namespace std;

//进入系统时显示界面
void OutputUI()
{
	cout << left;
	cout << setw(20) << "**" << setw(30) << "家谱管理系统" << "**"<<endl;
	cout << "====================================================" << endl;
	cout << setw(17) << "**" << setw(33) << "请选择要执行的操作：" << "**" << endl;
	cout << setw(19)<< "**" << setw(31) << "A---完善家庭" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "B---添加家庭成员" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "C---解散局部家庭" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "D---更改家庭成员姓名" << "**" << endl;
	cout << setw(19) << "**" << setw(31) << "E---退出程序" << "**" << endl;
	cout << "====================================================" << endl;
}


int main()
{
	OutputUI();//进入系统是显示界面
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	string ancestorName, fatherName, childName;
	string oriName, nowName;//修改姓名用
	int num;
	vector<string> childs;//某一个节点的全部子女

	cin >> ancestorName;
	cout << "此家谱的祖先是：" << ancestorName << endl;
	Tree familyTree(ancestorName);//构造家谱树

	int flag = 1;
	while (flag)//flag为1时系统继续运行
	{
		cout << endl;
		cout << "请选择要执行的操作：";
		char choice;
		cin >> choice;
		childs.clear();//每次循环前先清空vector
		switch (choice)//根据提示，五种选择对应的不同操作
		{
		case'A':
			cout << "请输入要建立家庭的人的姓名：";
			cin >> fatherName;
			cout << "请输入" << fatherName << "的儿女人数：";
			cin >> num;
			cout << "请依次输入" << fatherName << "的儿女的姓名：";

			while (num--)
			{
				cin >> childName;
				childs.push_back(childName);
			}

			familyTree.AddChild(fatherName, childs);
			familyTree.Output(fatherName);
			break;

		case'B':
			cout << "请输入要添加儿子（或女儿）的人的姓名：";
			cin >> fatherName;
			cout << "请输入" << fatherName << "新添加的儿子（或女儿）的姓名：";
			cin >> childName;
			childs.push_back(childName);
			familyTree.AddChild(fatherName, childs);
			familyTree.Output(fatherName);
			break;

		case'C':
			cout << "请输入要解散家庭的人的姓名：";
			cin >> fatherName;
			cout << "要解散家庭的人是：" << fatherName<<endl;
			familyTree.Output(fatherName);
			familyTree.DeleteSubTree(fatherName);
			break;

		case'D':
			cout << "请输入要更改姓名的人的目前姓名：";
			cin >> oriName;
			cout << "请输入更改后的姓名：";
			cin >> nowName;
			familyTree.ChangeName(oriName, nowName);
			cout << oriName << "已更名为" << nowName;
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