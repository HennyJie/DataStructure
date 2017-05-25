#ifndef _SORT_H_
#define _SORT_H_
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;
const int DefaultSize = 10000;

//数据表元素类
template <class T>
class Element
{
public:
	T key;//排序码
	void operator=(Element<T>& x)//把x的值赋给this
	{
		key = x.key;
	}
	void operator=(T x)//把x的值赋给key
	{
		key = x;
	}
	friend ostream& operator<<(ostream& os, Element<int> ele);//重载运算符<<

	bool operator==(Element<T>& x) { return key == x.key; }//判*this与x相等
	bool operator<=(Element<T>& x) { return key <= x.key; }//判*this<=x
	bool operator>=(Element<T>& x) { return key >= x.key; }//判*this>=x
	bool operator>(Element<T>& x) { return key > x.key; }//判*this>x
	bool operator<(Element<T>& x) { return key < x.key; }//判*this<x
};

ostream& operator<<(ostream& os, Element<int> ele)//友元函数
{
	os << ele.key;
	return os;
}

//数据表类
template <class T>
class DataList
{
private:
	Element<T>* Vector;//存储数据的数组

public:
	DataList(int maxSz = DefaultSize) :maxSize(maxSz)//构造函数（设置最大值）
	{
		Vector = new Element<T>[maxSize];
	}
	~DataList()//析构函数
	{
		delete []Vector;
	}
	DataList(DataList<T>& data)//构造函数（复制）
	{
		Vector = new Element<T>[data.maxSize];
		memcpy(Vector, data.getVector(), sizeof(T)*data.maxSize);
		maxSize = data.maxSize;
	}
	Element<T>& operator[](int i) { return Vector[i]; }//重载运算符[]
	Element<T>* getVector() { return Vector; }//获取数组
	
	int maxSize;
};

//排序算法类
template <class T>
class Sort
{
public:
	clock_t runtime = 0;
	int compareTimes = 0;
	const T maxValue = 50000000;
	void Swap(Element<T>& x, Element<T>& y)//交换x，y
	{
		Element<T> temp = x; x = y; y = temp;
	}
	void BubbleSort(DataList<T>& dataList);//冒泡排序
	void SelectSort(DataList<T>& dataList);//选择排序
	void InsertSort(DataList<T>& dataList);//直接插入排序
	void ShellSort(DataList<T>& dataList);//希尔排序

	int Partition(DataList<T>& dataList,const int low, const int high );//供快速排序调用于划分
	void QuickSort(DataList<T>& dataList,const int left,const int right);//快速排序

	void SiftDown(DataList<T>& dataList, const int start, const int end);//最大堆调整函数
	void HeapSort(DataList<T>& dataList);//堆排序

	void Merge(DataList<T>& L1, DataList<T>& L2, const int left, const int mid, const int right);//两路归并算法
	void MSort(DataList<T>& L1, DataList<T>& L2, int left, int right);//归并的递归调用
	void MergeSort(DataList<T>& L1);//归并排序

	int MaxBit(DataList<T>& dataList);//确定最大位数
	void RadixSort(DataList<T>& dataList);//基数排序

	void BinaryInsertSort(DataList<T>& dataList);//折半插入排序

	int Winner(int a, int b, T* e);//两者比较获得胜者
	bool Initial(DataList<T>& dataList, int *t, T *e, int size, int& lowExt, int& offset);//初始化胜者树
	void Play(int *t, T *e, int k, int lc, int rc);//通过比赛对树初始化
	bool RePlay(DataList<T>& dataList, int i, int lowExt, int offset, T *e, int *t);//当元素i改变时重新组织比赛
	void TournamentSort(DataList<T>& dataList);//锦标赛排序
};

//冒泡排序
template<class T>
void Sort<T>::BubbleSort(DataList<T>& dataList)
{
	bool exchange = true;//是否发生交换的标志

	int start = clock();
	for (int i = 1; (i < dataList.maxSize)&& exchange ;i++)//exchange为false时本趟无逆序，停止处理
	{
		exchange = false;//检查前假设没有发生交换
		for (int j = dataList.maxSize - 1; j >= i; j--)//从后向前检查是否发生逆序
		{
			compareTimes++;
			if (dataList[j - 1] > dataList[j])//发生逆序，交换元素的值
			{
				Swap(dataList[j - 1], dataList[j]);
				exchange = true;//置exchange为有交换状态
			}
		}
	}
	runtime = clock() - start;
	//供检验用的测试代码，下面的每一个排序算法都有
	/*for (int i = 0; i < dataList.maxSize; i++)
	{
		cout << dataList[i] << " " << endl;
	}*/
}

//选择排序
template<class T>
void Sort<T>::SelectSort(DataList<T>& dataList)
{
	int start = clock();
	for (int i = 0; i < dataList.maxSize - 1; i++)
	{
		int k = i;//在dataList[i]到dataList[dataList.maxsize-1]中找有最小排序码元素
		for (int j = i + 1; j <= dataList.maxSize - 1; j++)
		{
			compareTimes++;
			if (dataList[j] < dataList[k])k = j;//当前具最小排序码的元素
		}
		if (k != i)Swap(dataList[i], dataList[k]);//交换
	}
	runtime = clock() - start;
	/*for (int i = 0; i < dataList.maxSize; i++)
	{
		cout << dataList[i] << " " << endl;
	}*/
}

//直接插入排序
template<class T>
void Sort<T>::InsertSort(DataList<T>& dataList)
{
	Element<T> temp;
	
	int start = clock();
	for (int i = 1; i < dataList.maxSize; i++)
	{
		compareTimes++;
		if (dataList[i - 1] > dataList[i])
		{
			temp = dataList[i];//暂存防覆盖
			int j = i - 1;
			do {
				compareTimes++;
				dataList[j + 1] = dataList[j];//顺次后移
				j--;
			} while (j >= 0 && temp < dataList[j]);
			compareTimes++;
			dataList[j + 1] = temp;//暂存的原来的dataList[i]反填到第j个位置的后一位置
		}
	}
	runtime = clock() - start;
	/*for (int i = 0; i < dataList.maxSize; i++)
	{
		cout << dataList[i] << " " << endl;
	}*/
}

//希尔排序
template<class T>
void Sort<T>::ShellSort(DataList<T>& dataList)
{
	int i, j, gap = dataList.maxSize;//增量的初始值
	Element<T> temp;

	int start = clock();
	do {
		gap = gap / 3 + 1;//求下一增量值
		for (i = gap; i < dataList.maxSize; i++)//各子序列交替处理
		{
			compareTimes++;
			if (dataList[i] < dataList[i - gap])//逆序
			{
				temp = dataList[i];
				j = i - gap;
				do {
					dataList[j + gap] = dataList[j];//后移元素
					j = j - gap;//再比较前一元素
					compareTimes++;
				} while (j >= 0 && temp < dataList[j]);
				compareTimes++;
				dataList[j + gap] = temp;//将dataList[i]回送
			}
		}
	} while (gap > 1);
	runtime = clock() - start;
	/*for (i = 0; i < dataList.maxSize; i++)
	{
		cout << dataList[i] << " " << endl;
	}*/
}

//供快速排序调用于划分
template <class T>
int Sort<T>::Partition(DataList<T>& dataList, const int low, const int high)
{
	int pivotpos = low;
	Element<T> pivot = dataList[low];//基准元素
	for (int i = low + 1; i <= high; i++)//检测整个序列，进行划分
	{
		compareTimes++;
		if (dataList[i] < pivot)//小于基准的交换到左边
		{
			pivotpos++;
			if (pivotpos != i)
			{
				Swap(dataList[pivotpos], dataList[i]);
			}
		}
	}
	dataList[low] = dataList[pivotpos];//将基准元素就位
	dataList[pivotpos] = pivot;
	return pivotpos;//返回i基准元素位置
}
//快速排序
template <class T>
void Sort<T>::QuickSort(DataList<T>& dataList,const int left,const int right)
{
	int start = clock();
	if (left < right)//元素序列长度大于1时
	{
		int pivotpos = Partition(dataList, left, right);//划分
		QuickSort(dataList, left, pivotpos - 1);//对左侧子序列施行同样处理
		QuickSort(dataList, pivotpos + 1, right);//对右侧子序列施行同样处理
	}
	runtime = clock() - start;
	/*for (i = 0; i < dataList.maxSize; i++)
	{
		cout << dataList[i] << " " << endl;
	}*/
}

//最大堆调整函数
template<class T>
void Sort<T>::SiftDown(DataList<T>& dataList, const int start, const int end)
{
	int i = start;
	int j = 2 * i + 1;//j是i的左子女
	Element<T> temp = dataList[i];//暂存子树根结点
	while (j <= end)//检查是否到最后位置
	{
		compareTimes++;
		if (j < end&&dataList[j] < dataList[j + 1])//让child指向两子女中的大者
			j++;
		compareTimes++;
		if (temp >= dataList[j])//temp的排序码大则不做调整
			break;
		else //否则子女中的大者上移
		{
			dataList[i] = dataList[j];
			i = j;//i下降到子女位置
			j = 2 * j + 1;
		}
	}
	dataList[i] = temp;//temp中暂存元素放到合适位置
}
//堆排序
template<class T>
void Sort<T>::HeapSort(DataList<T>& dataList)
{
	int i;
	int start = clock();
	for (i = (dataList.maxSize - 2) / 2; i >= 0; i--)
		SiftDown(dataList, i, dataList.maxSize - 1);
	for (i = dataList.maxSize - 1; i >= 0; i--)
	{
		Swap(dataList[0], dataList[i]);
		SiftDown(dataList,0, i - 1);
	}
	runtime = clock() - start;
	/*for (i = 0; i < dataList.maxSize; i++)
	{
		cout << dataList[i] << " " << endl;
	}*/
}

//两路归并算法
template<class T>
void Sort<T>::Merge(DataList<T>& L1, DataList<T>& L2, const int left, const int mid, const int right)
{
	for (int k = left; k <= right; k++)
	{
		L2[k] = L1[k];
	}
	int s1 = left, s2 = mid + 1, t = left;//s1,s2是检测指针，t是存放指针
	while (s1 <= mid && s2 <= right)//两个表都未检测完，两两比较
	{
		compareTimes++;
		if (L2[s1] <= L2[s2])
			L1[t++] = L2[s1++];
		else
			L1[t++] = L2[s2++];
	}
	while (s1 <= mid)//若第一个表未检测完，复制
	{
		L1[t++] = L2[s1++];
	}
	while (s2 <= right)//若第二个表未检测完，复制
	{
		L1[t++] = L2[s2++];
	}
}
//归并的递归调用
template<class T>
void Sort<T>::MSort(DataList<T>& L1, DataList<T>& L2, int left, int right)
{
	if (left >= right)return;
	int mid = (left + right) / 2;//从中间划分为两个子序列
	MSort(L1, L2, left, mid);//对左侧子序列进行递归排序
	MSort(L1, L2, mid + 1, right);//对右侧子序列进行递归排序
	Merge(L1, L2, left, mid, right);//合并
}
//归并排序
template<class T>
void Sort<T>::MergeSort(DataList<T>& L1)
{
	DataList<T> L2(L1.maxSize);//构造辅助数组L2

	int start = clock();
	MSort(L1, L2, 0, L1.maxSize-1);//归并的递归调用
	runtime = clock() - start;
	/*for (int i = 0; i < L1.maxSize; i++)
	{
		cout << L1[i] << " " << endl;
	}*/
}

//确定最大位数
template<class T>
int Sort<T>::MaxBit(DataList<T>& dataList)
{
	Element<int> max = dataList[0];
	for (int i = 1; i < dataList.maxSize; i++)
	{
		compareTimes++;
		if (dataList[i] > max)
			max = dataList[i];//找到最大的数
	}
	int bit = 1, num = 10;
	while (max.key >= num)//计算最大数的位数
	{
		bit++;
		num *= 10;
	}
	return bit;
}
//基数排序
template<class T>
void Sort<T>::RadixSort(DataList<T>& dataList)
{
	int maxBit = MaxBit(dataList);//最大位数
	DataList<int> data(dataList);
	DataList<int> temp(dataList.maxSize);
	int container[10];//存放0~9的桶
	int i, j, k;
	int radix = 1;//基数

	int start = clock();
	for (i = 0; i < maxBit; i++)
	{
		memset(container, 0, sizeof(int)* 10);
		for (j = 0; j < data.maxSize; j++)
		{
			k = data[j].key / radix % 10;//key为当前位上的数字
			container[k]++;//先统计每个桶中的元素个数
		}
		for (j = 1; j < 10; j++)
		{
			container[j] += container[j - 1];//安排各桶元素的存放位置
		}
		for (j = data.maxSize-1; j>=0; j--)//将待排序序列中的元素按位值分配到各个桶中，存于辅助数组temp
		{
			compareTimes++;
			k = data[j].key / radix % 10;//取某位的数字
			temp[container[k] - 1] = data[j];//按预先计算位置存放
			container[k]--;//计数器减一
		}
		for (j = 0; j < data.maxSize; j++)//从辅助数组顺序写入原数组
		{
			data[j] = temp[j];
		}
		radix *= 10;//从个位到十位到百位依次向前移动
	}

	runtime = clock() - start;
	/*for (i = 0; i < data.maxSize; i++)
	{
		cout << data[i] << " " << endl;
	}*/
}

//折半插入排序
template<class T>
void Sort<T>::BinaryInsertSort(DataList<T>& dataList)
{
	int i, low, high, middle, k;
	Element<T> temp;

	int start = clock();
	for (i = 1; i < dataList.maxSize; i++)
	{
		temp = dataList[i];
		low = 0;
		high = i - 1;
		while (low <= high)//利用折半搜索插入位置
		{
			middle = (low + high) / 2;//取中点
			compareTimes++;
			if (temp < dataList[middle])//插入值小于中点值
				high = middle - 1;//向左缩小区间
			else
				low = middle + 1;//否则，向右缩小区间
		}
		for (k = i - 1; k >= low; k--)//成块移动，空出插入位置
		{
			dataList[k + 1] = dataList[k];
		}
		dataList[low] = temp;//插入
	}
	runtime = clock() - start;
	/*for (i = 0; i < dataList.maxSize; i++)
	{
	cout << dataList[i] << " " <<endl;
	}*/
}

//选出胜者
template <class T>
int Sort<T>::Winner(int a, int b, T* e)
{ 
	compareTimes++;
	return(e[a] <= e[b]) ? a : b;//较小者胜
}
//初始化胜者树
template <class T>
bool Sort<T>::Initial(DataList<T>& dataList,int *t,T *e,int size,int& lowExt,int& offset)
{
	if (size > dataList.maxSize || size < 2)return false;
	int n = size;
	int i, s;
	for (s = 1; 2 * s <= n - 1; s += s);
	lowExt = 2 * (n - s);
	offset = 2 * s - 1;
	for (i = 2; i <= lowExt; i += 2)//最远层外部节点的比赛
		Play(t, e, (offset + i) / 2, i - 1, i);
	//处理其他外部节点
	if (n % 2 == 0)i = lowExt + 2;
	else//当n为奇数时，内部节点要与外部节点比赛
	{
		Play(t, e, n / 2, t[n - 1], lowExt + 1);
		i = lowExt + 3;
	}
	for (; i <= n; i += 2)//i为最左剩余节点，处理其他外部节点的比赛
		Play(t, e, (i - lowExt + n - 1) / 2, i - 1, i);
	return true;
}
//通过比赛过程对树初始化
template <class T>
void Sort<T>::Play(int *t, T *e, int k, int lc, int rc)
{
	t[k] = Winner(lc, rc, e);//在e[lc]和e[rc]中选出胜者
	while (k > 1 && k % 2 != 0)//从右子女处向上比赛，直到根
	{
		t[k / 2] = Winner(t[k - 1], t[k],e);
		k /= 2;//到父节点
	}
}
//当元素i改变时重新组织比赛
template <class T>
bool Sort<T>::RePlay(DataList<T>& dataList,int i,int lowExt,int offset,T *e,int *t)
{
	if (i <= 0 || i > dataList.maxSize)return false;
	int k, lc, rc;//比赛节点及其左右子女
	if (i <= lowExt)//最远层外部节点的情况
	{
		k = (offset + i) / 2;//计算i的父节点
		lc = 2 * k - offset;//计算父节点的左右子女
		rc = lc + 1;
	}
	else//次远层外部节点的情况
	{
		k = (i - lowExt + dataList.maxSize- 1) / 2;
		if (2 * k == dataList.maxSize- 1)
		{
			lc = t[2 * k];
			rc = i;
		}
		else
		{
			lc = 2 * k - dataList.maxSize + 1 + lowExt;
			rc = lc + 1;
		}
	
	}
	t[k] = Winner(lc, rc, e);
	k /= 2;
	for (; k >= 1; k /= 2)//继续向父节点比赛直到根
	{
		t[k] = Winner(t[2 * k], t[2 * k + 1], e);
	}
}
//锦标赛排序
template<class T>
void Sort<T>::TournamentSort(DataList<T>& dataList)
{
	int lowExt, offset;//最远层外部节点个数和按深度满节点数（加一即为第一个外部节点）
	int *t=new int[dataList.maxSize];//胜者树数组
	T *e=new T[dataList.maxSize+1];//选手数组
	int i;
	int size = dataList.maxSize;

	int start = clock();
	for (i = 1; i <= dataList.maxSize; i++) e[i]=dataList[i- 1].key;//选手数组初始化
	Initial(dataList,t, e, size, lowExt, offset);//构造初始胜者树
	for (i = 1; i <= dataList.maxSize; i++)
	{
		dataList[i - 1] = e[t[1]];//输出胜者
		e[t[1]] = maxValue;//修改胜者的值
		RePlay(dataList, t[1], lowExt, offset, e,t);//重构胜者树，选出新的胜者
		if (e[t[1]] == maxValue)break;
 	}
	runtime = clock() - start;
	
	/*for (i = 0; i < dataList.maxSize; i++)
	{
	cout << dataList[i] << " " <<endl;
	}*/

	delete[]t;
	delete[]e;
}


#endif 

