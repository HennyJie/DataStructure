//==================================================栈类中函数实现和主函数======================================================
#include<iostream>
#include <iomanip>
#include <deque>
using namespace std;

deque<int> deq;
int ansNum=0;//方案数
int n;//皇后个数

void Output()//输出摆放好皇后的棋盘
{
	int i, j;
	cout << "No." << ansNum << " result is:\n" << endl;

	for (auto index : deq)
	{
		for (j = 0; j < index; j++)
		{
			cout << setw(4) << "0";//不放置皇后的地方打印 0
		}
		cout << setw(4) << "X";//放置皇后的地方打印 X
		for (j = index + 1; j < deq.size(); j++)
		{
			cout << setw(4) << "0";//之后的位置继续打印 0
		}
		cout << "\n" << endl;
	}
}

bool Judge()//判断该摆放位置是否在同一行，同一列或同一对角线
{
	int i;
	int top = deq.size();//队列中元素个数
	for (i = 0; i < top - 1; i++)
	{
		if ((deq[top - 1] == deq[i]) || (abs(deq[top - 1] - deq[i])) == (top - 1 - i))//在同一列或者同一对角线
			return false;
	}
	return true;
}

void PlaceQueen(int row)//摆放N皇后的递归函数
{
	int col;//列数
	for (col = 0; col < n; col++)//穷尽第0到N-1列
	{
		deq.push_back(col);//加入队列
		if (Judge())//判断摆放皇后的位置是否合法
		{
			if (row < n - 1)//若还没到第N个皇后，则摆放下一个皇后的位置
			{
				PlaceQueen(row + 1);
			}
			else
			{
				ansNum++;//方案数加一
				Output();//打印该方案
			}
		}
		deq.pop_back();//从队列中取出
	}
}

int main()
{
	cout << "现有N*N的棋盘，放入N个皇后，要求所有皇后不在同一行、列和同一对角线上！\n" << endl;
	cout << "设置N的值：";
	cin >> n;
	cout << endl;
	PlaceQueen(0);//从第一行开始摆放皇后
	cout << "如上所示，共有" << ansNum << "种解法！"<<endl;//输出棋盘中皇后摆放方法的总数

	getchar();
	getchar();
	return 0;
}
