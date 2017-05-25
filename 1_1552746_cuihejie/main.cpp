#include "Student.h"
#include <iomanip>
using namespace std;

int main()
{
	StudentNode* stu;
	StudentList stuList;
	cout << "首先请建立考生信息系统：" << endl;
	cout<<"请输入考生人数：";
	int n;
	int idnum, age,pos,caseNum;
	string name, gender, type;
	int flag = 1;
	StudentNode* del = new StudentNode();
	StudentNode* search = new StudentNode();
	cin >> n;
	cout << "请依次输入考生的考号，姓名，性别，年龄和报考类型："<<endl;
	for (int i = 0; i < n; i++)
	{
		cin >> idnum >> name >> gender >> age >> type;
		stu = new StudentNode(idnum, name, gender, age, type);
		stuList.PushBack(*stu);
	}
	cout << endl;
	stuList.Output();
	while (flag)
	{
		cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）";
		cin >> caseNum;
		switch (caseNum)
		{
		case 1:
			cout << "请输入你您要插入的考生的位置：";
			cin >> pos;
			cout << "请依次输入要插入的学生的考号，姓名，性别，年龄及报考类型：" << endl;
			cin >> idnum >> name >> gender >> age >> type;
			stu = new StudentNode(idnum, name, gender, age, type);
			stuList.Insert(*stu, pos);
			cout << endl;
			stuList.Output();
			break;

		case 2:
			cout << "请输入您要删除的学生的考号：";
			cin >> idnum;
			
			stuList.Remove(*del, idnum);
			cout << "您要删除的学生的信息是："<<endl;
			del->Output();
			cout << endl;
			stuList.Output();
			break;

		case 3:
			cout << "请输入您要查找的学生的考号：";
			cin >> idnum;
			
			stuList.Search(*search, idnum);
			cout << "查找到的学生信息为：" << endl;
			search->Output();
			break;

		case 4:
			cout << "请输入您要修改的考生的考号：";
			cin >> n;
			cout << "请依次输入要修改的考生的考号，姓名，性别，年龄及报考类型：" << endl;
			cin >> idnum >> name >> gender >> age >> type;
			stu = new StudentNode(idnum, name, gender, age, type);
			stuList.Reset(*stu, n);
			cout << endl;
			stuList.Output();
			break;

		case 5:
			cout << "请输入需要统计的报考类型：";
			cin >> type;
			cout <<"该报考类型的学生人数为："<< stuList.Count(type) << endl;
			break;

		case 0:
			flag = 0;
			cout << "谢谢使用！";
			break;

		default:
			continue;
		}
	
	}
	getchar();
	return 0;
}