//======================================================��¼�����˽ڵ��Ȩ�صıߡ���С�Ѻ���С��������===============================================================
#ifndef _MINSPANTREE_H_
#define _MINSPANTREE_H_
#include <iostream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

//��¼�����˽ڵ��Ȩ�صı�
struct Edge 
{
	char startVertex, endVertex;//ͷ�ڵ㣬β�ڵ�
	int weight;//Ȩ��

	Edge(){}
	Edge(char start,char end,int wei):startVertex(start),endVertex(end),weight(wei){}
	void operator = (Edge t)//���صȺ�
	{
		startVertex = t.startVertex;
		endVertex = t.endVertex;
		weight = t.weight;
	}
};

//��С��
class MinHeap
{
private:
	vector<Edge> heap;//��С�Ѵ洢�ṹ
	int currentSize=0;//��ǰ����Ԫ�ظ���
	void siftDown(int start, int end);//��С�ѵ��»������㷨
	void siftUp(int start);//��С�ѵ��ϻ������㷨

public:
	bool Insert(Edge& ed);//�ѵĲ����㷨
	bool RemoveMin();//�ѵ�ɾ���㷨
	Edge& GetTop() { return heap[0]; }//ȡ����С�ѵĶ�Ԫ��
};

//��С������
class MinSpanTree
{
private:
	map<char, int> vertex;//�洢������ƺ���ŵ�map
	int size;//������
	vector<Edge> edgeFromVertex[100];//�洢�ߵ��ڽӱ�
	vector<Edge> minEdge;//��С������

public:
	void SetVertex();//���붥��
	void SetEdge();//�����Ȩ��
	void Prim();//Prim�㷨������С������
	void Output();//�����С���������
};
#endif 
