//======================================================记录了两端节点和权重的边、最小堆和最小生成树类===============================================================
#ifndef _MINSPANTREE_H_
#define _MINSPANTREE_H_
#include <iostream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

//记录了两端节点和权重的边
struct Edge 
{
	char startVertex, endVertex;//头节点，尾节点
	int weight;//权重

	Edge(){}
	Edge(char start,char end,int wei):startVertex(start),endVertex(end),weight(wei){}
	void operator = (Edge t)//重载等号
	{
		startVertex = t.startVertex;
		endVertex = t.endVertex;
		weight = t.weight;
	}
};

//最小堆
class MinHeap
{
private:
	vector<Edge> heap;//最小堆存储结构
	int currentSize=0;//当前堆中元素个数
	void siftDown(int start, int end);//最小堆的下滑调整算法
	void siftUp(int start);//最小堆的上滑调整算法

public:
	bool Insert(Edge& ed);//堆的插入算法
	bool RemoveMin();//堆的删除算法
	Edge& GetTop() { return heap[0]; }//取出最小堆的顶元素
};

//最小生成树
class MinSpanTree
{
private:
	map<char, int> vertex;//存储结点名称和序号的map
	int size;//顶点数
	vector<Edge> edgeFromVertex[100];//存储边的邻接表
	vector<Edge> minEdge;//最小生成树

public:
	void SetVertex();//读入顶点
	void SetEdge();//读入带权边
	void Prim();//Prim算法构造最小生成树
	void Output();//输出最小生成树结果
};
#endif 
