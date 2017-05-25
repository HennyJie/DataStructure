//=======================================================最小堆和最小生成树中函数的实现=================================================================
#include "MinSpanTree.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
using namespace std;

//最小堆的下滑调整算法
void MinHeap::siftDown(int start, int end)
{
	int i = start, j = i * 2 + 1;//j是i的左子女位置
	Edge temp = heap[i];
	while (j <= end)//检查是否到最后位置
	{
		if (j<end && heap[j].weight> heap[j + 1].weight)//让j指向两子女中的小者
			j++;
		if (temp.weight <= heap[j].weight)
			break;
		else
		{
			heap[i] = heap[j];//调整位置
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;//回放temp中暂存的元素
}

//最小堆的上滑调整算法
void MinHeap::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	Edge temp = heap[j];
	while (j > 0)//沿父节点路径向上直达根
	{
		if (heap[i].weight <= temp.weight)break;
		else
		{
			heap[j] = heap[i];//调整
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;//回送
}

//堆的插入算法
bool MinHeap::Insert(Edge& ed)
{
	heap.push_back(ed);
	currentSize++;//堆计数加一
	siftUp(currentSize-1);//向上调整
	return true;
}

//堆的删除算法
bool MinHeap::RemoveMin()
{
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);//自上向下调整
	return true;
}

//读入顶点
void MinSpanTree::SetVertex()
{
	cout << "请输入顶点的个数：";
	cin >> size;
	cout << "请依次输入各顶点的名称：" << endl;
	int i ;
	for (i = 1; i <= size; i++)
	{
		char ch;
		cin >> ch;
		vertex.insert(make_pair(ch, i));//顶点名称和序号成对存入map
	}
}

//读入带权边
void MinSpanTree::SetEdge()
{
	while (1)
	{
		cout << "请输入两个顶点及边：";
		char start, end;
		int weight;
		cin >> start >> end >> weight;
		if (start == '?'&&end == '?'&&weight == 0)//结束标志
			break;
		Edge ed1(start, end, weight), ed2(end, start, weight);
		edgeFromVertex[vertex[start]].push_back(ed1);//向邻接表中加入连在start上的边
		edgeFromVertex[vertex[end]].push_back(ed2);//向邻接表中加入连在end上的边
	}
}

//Prim算法构造最小生成树
void MinSpanTree::Prim()
{
	cout << "请输入起始顶点：";
	char startPoint;
	cin >> startPoint;
	bool mark[100];
	memset(mark, 0, sizeof(mark));//初始化标记数组
	MinHeap Heap;//最小堆
	MinSpanTree MinTree;//最小生成树
	Edge temp;

	size--;
	while (size--)//循环条件：加入生成树中的边是size-1条
	{
		mark[vertex[startPoint]] = 1;
		for (Edge i : edgeFromVertex[vertex[startPoint]])//连在该节点上的边依次加入最小堆
		{
			Heap.Insert(i);
		}
		while (1)
		{
			int index = Heap.GetTop().endVertex;
			if (mark[vertex[index]])//如果该边上的另一个顶点已在最小生成树中
			{
				Heap.RemoveMin();//最小堆的top冒出
			}
			else
			{
				startPoint = Heap.GetTop().endVertex;//若不在，则令另一个顶点作为新的起始顶点
				minEdge.push_back(Heap.GetTop());//最小堆顶点加入到最小生成树中
				break;
			}
		}
	}
	cout << "生成Prim最小生成树！" << endl;
}

//输出最小生成树结果
void MinSpanTree::Output()
{
	for (Edge i : minEdge)//打印最小生成树的每条边
	{
		cout << i.startVertex << "-<" << i.weight << ">->" << i.endVertex << "\t";
	}
	cout << endl;
}
