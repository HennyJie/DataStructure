//==================================================ջ���к���ʵ�ֺ�������======================================================
#include<iostream>
#include <iomanip>
#include <deque>
using namespace std;

deque<int> deq;
int ansNum=0;//������
int n;//�ʺ����

void Output()//����ڷźûʺ������
{
	int i, j;
	cout << "No." << ansNum << " result is:\n" << endl;

	for (auto index : deq)
	{
		for (j = 0; j < index; j++)
		{
			cout << setw(4) << "0";//�����ûʺ�ĵط���ӡ 0
		}
		cout << setw(4) << "X";//���ûʺ�ĵط���ӡ X
		for (j = index + 1; j < deq.size(); j++)
		{
			cout << setw(4) << "0";//֮���λ�ü�����ӡ 0
		}
		cout << "\n" << endl;
	}
}

bool Judge()//�жϸðڷ�λ���Ƿ���ͬһ�У�ͬһ�л�ͬһ�Խ���
{
	int i;
	int top = deq.size();//������Ԫ�ظ���
	for (i = 0; i < top - 1; i++)
	{
		if ((deq[top - 1] == deq[i]) || (abs(deq[top - 1] - deq[i])) == (top - 1 - i))//��ͬһ�л���ͬһ�Խ���
			return false;
	}
	return true;
}

void PlaceQueen(int row)//�ڷ�N�ʺ�ĵݹ麯��
{
	int col;//����
	for (col = 0; col < n; col++)//���0��N-1��
	{
		deq.push_back(col);//�������
		if (Judge())//�жϰڷŻʺ��λ���Ƿ�Ϸ�
		{
			if (row < n - 1)//����û����N���ʺ���ڷ���һ���ʺ��λ��
			{
				PlaceQueen(row + 1);
			}
			else
			{
				ansNum++;//��������һ
				Output();//��ӡ�÷���
			}
		}
		deq.pop_back();//�Ӷ�����ȡ��
	}
}

int main()
{
	cout << "����N*N�����̣�����N���ʺ�Ҫ�����лʺ���ͬһ�С��к�ͬһ�Խ����ϣ�\n" << endl;
	cout << "����N��ֵ��";
	cin >> n;
	cout << endl;
	PlaceQueen(0);//�ӵ�һ�п�ʼ�ڷŻʺ�
	cout << "������ʾ������" << ansNum << "�ֽⷨ��"<<endl;//��������лʺ�ڷŷ���������

	getchar();
	getchar();
	return 0;
}
