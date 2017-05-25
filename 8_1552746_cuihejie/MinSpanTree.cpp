//=======================================================��С�Ѻ���С�������к�����ʵ��=================================================================
#include "MinSpanTree.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
using namespace std;

//��С�ѵ��»������㷨
void MinHeap::siftDown(int start, int end)
{
	int i = start, j = i * 2 + 1;//j��i������Ůλ��
	Edge temp = heap[i];
	while (j <= end)//����Ƿ����λ��
	{
		if (j<end && heap[j].weight> heap[j + 1].weight)//��jָ������Ů�е�С��
			j++;
		if (temp.weight <= heap[j].weight)
			break;
		else
		{
			heap[i] = heap[j];//����λ��
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;//�ط�temp���ݴ��Ԫ��
}

//��С�ѵ��ϻ������㷨
void MinHeap::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	Edge temp = heap[j];
	while (j > 0)//�ظ��ڵ�·������ֱ���
	{
		if (heap[i].weight <= temp.weight)break;
		else
		{
			heap[j] = heap[i];//����
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;//����
}

//�ѵĲ����㷨
bool MinHeap::Insert(Edge& ed)
{
	heap.push_back(ed);
	currentSize++;//�Ѽ�����һ
	siftUp(currentSize-1);//���ϵ���
	return true;
}

//�ѵ�ɾ���㷨
bool MinHeap::RemoveMin()
{
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);//�������µ���
	return true;
}

//���붥��
void MinSpanTree::SetVertex()
{
	cout << "�����붥��ĸ�����";
	cin >> size;
	cout << "�������������������ƣ�" << endl;
	int i ;
	for (i = 1; i <= size; i++)
	{
		char ch;
		cin >> ch;
		vertex.insert(make_pair(ch, i));//�������ƺ���ųɶԴ���map
	}
}

//�����Ȩ��
void MinSpanTree::SetEdge()
{
	while (1)
	{
		cout << "�������������㼰�ߣ�";
		char start, end;
		int weight;
		cin >> start >> end >> weight;
		if (start == '?'&&end == '?'&&weight == 0)//������־
			break;
		Edge ed1(start, end, weight), ed2(end, start, weight);
		edgeFromVertex[vertex[start]].push_back(ed1);//���ڽӱ��м�������start�ϵı�
		edgeFromVertex[vertex[end]].push_back(ed2);//���ڽӱ��м�������end�ϵı�
	}
}

//Prim�㷨������С������
void MinSpanTree::Prim()
{
	cout << "��������ʼ���㣺";
	char startPoint;
	cin >> startPoint;
	bool mark[100];
	memset(mark, 0, sizeof(mark));//��ʼ���������
	MinHeap Heap;//��С��
	MinSpanTree MinTree;//��С������
	Edge temp;

	size--;
	while (size--)//ѭ�������������������еı���size-1��
	{
		mark[vertex[startPoint]] = 1;
		for (Edge i : edgeFromVertex[vertex[startPoint]])//���ڸýڵ��ϵı����μ�����С��
		{
			Heap.Insert(i);
		}
		while (1)
		{
			int index = Heap.GetTop().endVertex;
			if (mark[vertex[index]])//����ñ��ϵ���һ������������С��������
			{
				Heap.RemoveMin();//��С�ѵ�topð��
			}
			else
			{
				startPoint = Heap.GetTop().endVertex;//�����ڣ�������һ��������Ϊ�µ���ʼ����
				minEdge.push_back(Heap.GetTop());//��С�Ѷ�����뵽��С��������
				break;
			}
		}
	}
	cout << "����Prim��С��������" << endl;
}

//�����С���������
void MinSpanTree::Output()
{
	for (Edge i : minEdge)//��ӡ��С��������ÿ����
	{
		cout << i.startVertex << "-<" << i.weight << ">->" << i.endVertex << "\t";
	}
	cout << endl;
}
