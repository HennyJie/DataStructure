//======================================================Լɪ�������㷨��������==============================================================
#include "CircleList.h"
#include <iomanip>
using namespace std;

//���Լɪ��������㷨
void Josephus(CircleList* cirList,  int startNum, int key, int killedNum, int amount)
{
	int i, j, k;
	if(!cirList->IsEmpty())
	{
		CircleNode *current = cirList->Locate(1), *pre = cirList->Locate(amount);//�ҵ��洢���Ϊ1�Ľڵ�
		for (i = 1; i < startNum; i++)//�������룬�ƶ�ָ���ҵ���ʼ������λ��
		{
			pre = current;
			current = current->link;
		}
		for (j = 1; j <= killedNum; j++)//ѭ�������ǳ��ֵ���������
		{
			for (k = 1; k < key; k++)//��1������������ ��key��
			{
				pre = current;

				current = current->link;
			}
			cout << "��" << j << "�����ߵ�λ���ǣ�" << cirList->Remove(pre, current) << endl;
			cirList->SetAmount(cirList->GetAmount() - 1);//ѭ�������нڵ�������һ
		}
	}
	
}

//������
int main()
{
	int N, S, K, M;
	CircleList *cirList;
	CircleList a;
	cout << "����N����Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ���˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ" << endl;
	cout <<left<<setw(24)<<"������������Ϸ��������N��";
	cin >> N;
	cout <<left<< setw(25) << "��������Ϸ��ʼ��λ��S��";
	cin >> S;
	cout <<left<< setw(25) << "��������������M��";
	cin >> M;
	cout <<left<< setw(25) << "������ʣ����������K��";
	cin >> K;
	cout << endl;

	cirList=new CircleList(N);
	Josephus(cirList, S, M, N - K, N);
	cirList->Output();
	delete cirList;
	getchar();
	getchar();
	return 0;

}