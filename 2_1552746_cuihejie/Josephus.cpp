//======================================================约瑟夫问题算法和主函数==============================================================
#include "CircleList.h"
#include <iomanip>
using namespace std;

//求解约瑟夫环问题的算法
void Josephus(CircleList* cirList,  int startNum, int key, int killedNum, int amount)
{
	int i, j, k;
	if(!cirList->IsEmpty())
	{
		CircleNode *current = cirList->Locate(1), *pre = cirList->Locate(amount);//找到存储序号为1的节点
		for (i = 1; i < startNum; i++)//根据输入，移动指针找到开始报数的位置
		{
			pre = current;
			current = current->link;
		}
		for (j = 1; j <= killedNum; j++)//循环次数是出局的死者总数
		{
			for (k = 1; k < key; k++)//从1数到死亡数字 “key”
			{
				pre = current;

				current = current->link;
			}
			cout << "第" << j << "个死者的位置是：" << cirList->Remove(pre, current) << endl;
			cirList->SetAmount(cirList->GetAmount() - 1);//循环链表中节点总数减一
		}
	}
	
}

//主函数
int main()
{
	int N, S, K, M;
	CircleList *cirList;
	CircleList a;
	cout << "现有N个人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一个人开始报数，如此循环，直到剩下K个人为止" << endl;
	cout <<left<<setw(24)<<"请输入生死游戏的总人数N：";
	cin >> N;
	cout <<left<< setw(25) << "请输入游戏开始的位置S：";
	cin >> S;
	cout <<left<< setw(25) << "请输入死亡数字M：";
	cin >> M;
	cout <<left<< setw(25) << "请输入剩余生者数量K：";
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