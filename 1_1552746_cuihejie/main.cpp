#include "Student.h"
#include <iomanip>
using namespace std;

int main()
{
	StudentNode* stu;
	StudentList stuList;
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout<<"�����뿼��������";
	int n;
	int idnum, age,pos,caseNum;
	string name, gender, type;
	int flag = 1;
	StudentNode* del = new StudentNode();
	StudentNode* search = new StudentNode();
	cin >> n;
	cout << "���������뿼���Ŀ��ţ��������Ա�����ͱ������ͣ�"<<endl;
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
		cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������";
		cin >> caseNum;
		switch (caseNum)
		{
		case 1:
			cout << "����������Ҫ����Ŀ�����λ�ã�";
			cin >> pos;
			cout << "����������Ҫ�����ѧ���Ŀ��ţ��������Ա����估�������ͣ�" << endl;
			cin >> idnum >> name >> gender >> age >> type;
			stu = new StudentNode(idnum, name, gender, age, type);
			stuList.Insert(*stu, pos);
			cout << endl;
			stuList.Output();
			break;

		case 2:
			cout << "��������Ҫɾ����ѧ���Ŀ��ţ�";
			cin >> idnum;
			
			stuList.Remove(*del, idnum);
			cout << "��Ҫɾ����ѧ������Ϣ�ǣ�"<<endl;
			del->Output();
			cout << endl;
			stuList.Output();
			break;

		case 3:
			cout << "��������Ҫ���ҵ�ѧ���Ŀ��ţ�";
			cin >> idnum;
			
			stuList.Search(*search, idnum);
			cout << "���ҵ���ѧ����ϢΪ��" << endl;
			search->Output();
			break;

		case 4:
			cout << "��������Ҫ�޸ĵĿ����Ŀ��ţ�";
			cin >> n;
			cout << "����������Ҫ�޸ĵĿ����Ŀ��ţ��������Ա����估�������ͣ�" << endl;
			cin >> idnum >> name >> gender >> age >> type;
			stu = new StudentNode(idnum, name, gender, age, type);
			stuList.Reset(*stu, n);
			cout << endl;
			stuList.Output();
			break;

		case 5:
			cout << "��������Ҫͳ�Ƶı������ͣ�";
			cin >> type;
			cout <<"�ñ������͵�ѧ������Ϊ��"<< stuList.Count(type) << endl;
			break;

		case 0:
			flag = 0;
			cout << "ллʹ�ã�";
			break;

		default:
			continue;
		}
	
	}
	getchar();
	return 0;
}