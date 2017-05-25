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

//���ݱ�Ԫ����
template <class T>
class Element
{
public:
	T key;//������
	void operator=(Element<T>& x)//��x��ֵ����this
	{
		key = x.key;
	}
	void operator=(T x)//��x��ֵ����key
	{
		key = x;
	}
	friend ostream& operator<<(ostream& os, Element<int> ele);//���������<<

	bool operator==(Element<T>& x) { return key == x.key; }//��*this��x���
	bool operator<=(Element<T>& x) { return key <= x.key; }//��*this<=x
	bool operator>=(Element<T>& x) { return key >= x.key; }//��*this>=x
	bool operator>(Element<T>& x) { return key > x.key; }//��*this>x
	bool operator<(Element<T>& x) { return key < x.key; }//��*this<x
};

ostream& operator<<(ostream& os, Element<int> ele)//��Ԫ����
{
	os << ele.key;
	return os;
}

//���ݱ���
template <class T>
class DataList
{
private:
	Element<T>* Vector;//�洢���ݵ�����

public:
	DataList(int maxSz = DefaultSize) :maxSize(maxSz)//���캯�����������ֵ��
	{
		Vector = new Element<T>[maxSize];
	}
	~DataList()//��������
	{
		delete []Vector;
	}
	DataList(DataList<T>& data)//���캯�������ƣ�
	{
		Vector = new Element<T>[data.maxSize];
		memcpy(Vector, data.getVector(), sizeof(T)*data.maxSize);
		maxSize = data.maxSize;
	}
	Element<T>& operator[](int i) { return Vector[i]; }//���������[]
	Element<T>* getVector() { return Vector; }//��ȡ����
	
	int maxSize;
};

//�����㷨��
template <class T>
class Sort
{
public:
	clock_t runtime = 0;
	int compareTimes = 0;
	const T maxValue = 50000000;
	void Swap(Element<T>& x, Element<T>& y)//����x��y
	{
		Element<T> temp = x; x = y; y = temp;
	}
	void BubbleSort(DataList<T>& dataList);//ð������
	void SelectSort(DataList<T>& dataList);//ѡ������
	void InsertSort(DataList<T>& dataList);//ֱ�Ӳ�������
	void ShellSort(DataList<T>& dataList);//ϣ������

	int Partition(DataList<T>& dataList,const int low, const int high );//��������������ڻ���
	void QuickSort(DataList<T>& dataList,const int left,const int right);//��������

	void SiftDown(DataList<T>& dataList, const int start, const int end);//���ѵ�������
	void HeapSort(DataList<T>& dataList);//������

	void Merge(DataList<T>& L1, DataList<T>& L2, const int left, const int mid, const int right);//��·�鲢�㷨
	void MSort(DataList<T>& L1, DataList<T>& L2, int left, int right);//�鲢�ĵݹ����
	void MergeSort(DataList<T>& L1);//�鲢����

	int MaxBit(DataList<T>& dataList);//ȷ�����λ��
	void RadixSort(DataList<T>& dataList);//��������

	void BinaryInsertSort(DataList<T>& dataList);//�۰��������

	int Winner(int a, int b, T* e);//���߱Ƚϻ��ʤ��
	bool Initial(DataList<T>& dataList, int *t, T *e, int size, int& lowExt, int& offset);//��ʼ��ʤ����
	void Play(int *t, T *e, int k, int lc, int rc);//ͨ������������ʼ��
	bool RePlay(DataList<T>& dataList, int i, int lowExt, int offset, T *e, int *t);//��Ԫ��i�ı�ʱ������֯����
	void TournamentSort(DataList<T>& dataList);//����������
};

//ð������
template<class T>
void Sort<T>::BubbleSort(DataList<T>& dataList)
{
	bool exchange = true;//�Ƿ��������ı�־

	int start = clock();
	for (int i = 1; (i < dataList.maxSize)&& exchange ;i++)//exchangeΪfalseʱ����������ֹͣ����
	{
		exchange = false;//���ǰ����û�з�������
		for (int j = dataList.maxSize - 1; j >= i; j--)//�Ӻ���ǰ����Ƿ�������
		{
			compareTimes++;
			if (dataList[j - 1] > dataList[j])//�������򣬽���Ԫ�ص�ֵ
			{
				Swap(dataList[j - 1], dataList[j]);
				exchange = true;//��exchangeΪ�н���״̬
			}
		}
	}
	runtime = clock() - start;
	//�������õĲ��Դ��룬�����ÿһ�������㷨����
	/*for (int i = 0; i < dataList.maxSize; i++)
	{
		cout << dataList[i] << " " << endl;
	}*/
}

//ѡ������
template<class T>
void Sort<T>::SelectSort(DataList<T>& dataList)
{
	int start = clock();
	for (int i = 0; i < dataList.maxSize - 1; i++)
	{
		int k = i;//��dataList[i]��dataList[dataList.maxsize-1]��������С������Ԫ��
		for (int j = i + 1; j <= dataList.maxSize - 1; j++)
		{
			compareTimes++;
			if (dataList[j] < dataList[k])k = j;//��ǰ����С�������Ԫ��
		}
		if (k != i)Swap(dataList[i], dataList[k]);//����
	}
	runtime = clock() - start;
	/*for (int i = 0; i < dataList.maxSize; i++)
	{
		cout << dataList[i] << " " << endl;
	}*/
}

//ֱ�Ӳ�������
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
			temp = dataList[i];//�ݴ������
			int j = i - 1;
			do {
				compareTimes++;
				dataList[j + 1] = dataList[j];//˳�κ���
				j--;
			} while (j >= 0 && temp < dataList[j]);
			compareTimes++;
			dataList[j + 1] = temp;//�ݴ��ԭ����dataList[i]�����j��λ�õĺ�һλ��
		}
	}
	runtime = clock() - start;
	/*for (int i = 0; i < dataList.maxSize; i++)
	{
		cout << dataList[i] << " " << endl;
	}*/
}

//ϣ������
template<class T>
void Sort<T>::ShellSort(DataList<T>& dataList)
{
	int i, j, gap = dataList.maxSize;//�����ĳ�ʼֵ
	Element<T> temp;

	int start = clock();
	do {
		gap = gap / 3 + 1;//����һ����ֵ
		for (i = gap; i < dataList.maxSize; i++)//�������н��洦��
		{
			compareTimes++;
			if (dataList[i] < dataList[i - gap])//����
			{
				temp = dataList[i];
				j = i - gap;
				do {
					dataList[j + gap] = dataList[j];//����Ԫ��
					j = j - gap;//�ٱȽ�ǰһԪ��
					compareTimes++;
				} while (j >= 0 && temp < dataList[j]);
				compareTimes++;
				dataList[j + gap] = temp;//��dataList[i]����
			}
		}
	} while (gap > 1);
	runtime = clock() - start;
	/*for (i = 0; i < dataList.maxSize; i++)
	{
		cout << dataList[i] << " " << endl;
	}*/
}

//��������������ڻ���
template <class T>
int Sort<T>::Partition(DataList<T>& dataList, const int low, const int high)
{
	int pivotpos = low;
	Element<T> pivot = dataList[low];//��׼Ԫ��
	for (int i = low + 1; i <= high; i++)//����������У����л���
	{
		compareTimes++;
		if (dataList[i] < pivot)//С�ڻ�׼�Ľ��������
		{
			pivotpos++;
			if (pivotpos != i)
			{
				Swap(dataList[pivotpos], dataList[i]);
			}
		}
	}
	dataList[low] = dataList[pivotpos];//����׼Ԫ�ؾ�λ
	dataList[pivotpos] = pivot;
	return pivotpos;//����i��׼Ԫ��λ��
}
//��������
template <class T>
void Sort<T>::QuickSort(DataList<T>& dataList,const int left,const int right)
{
	int start = clock();
	if (left < right)//Ԫ�����г��ȴ���1ʱ
	{
		int pivotpos = Partition(dataList, left, right);//����
		QuickSort(dataList, left, pivotpos - 1);//�����������ʩ��ͬ������
		QuickSort(dataList, pivotpos + 1, right);//���Ҳ�������ʩ��ͬ������
	}
	runtime = clock() - start;
	/*for (i = 0; i < dataList.maxSize; i++)
	{
		cout << dataList[i] << " " << endl;
	}*/
}

//���ѵ�������
template<class T>
void Sort<T>::SiftDown(DataList<T>& dataList, const int start, const int end)
{
	int i = start;
	int j = 2 * i + 1;//j��i������Ů
	Element<T> temp = dataList[i];//�ݴ����������
	while (j <= end)//����Ƿ����λ��
	{
		compareTimes++;
		if (j < end&&dataList[j] < dataList[j + 1])//��childָ������Ů�еĴ���
			j++;
		compareTimes++;
		if (temp >= dataList[j])//temp�����������������
			break;
		else //������Ů�еĴ�������
		{
			dataList[i] = dataList[j];
			i = j;//i�½�����Ůλ��
			j = 2 * j + 1;
		}
	}
	dataList[i] = temp;//temp���ݴ�Ԫ�طŵ�����λ��
}
//������
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

//��·�鲢�㷨
template<class T>
void Sort<T>::Merge(DataList<T>& L1, DataList<T>& L2, const int left, const int mid, const int right)
{
	for (int k = left; k <= right; k++)
	{
		L2[k] = L1[k];
	}
	int s1 = left, s2 = mid + 1, t = left;//s1,s2�Ǽ��ָ�룬t�Ǵ��ָ��
	while (s1 <= mid && s2 <= right)//������δ����꣬�����Ƚ�
	{
		compareTimes++;
		if (L2[s1] <= L2[s2])
			L1[t++] = L2[s1++];
		else
			L1[t++] = L2[s2++];
	}
	while (s1 <= mid)//����һ����δ����꣬����
	{
		L1[t++] = L2[s1++];
	}
	while (s2 <= right)//���ڶ�����δ����꣬����
	{
		L1[t++] = L2[s2++];
	}
}
//�鲢�ĵݹ����
template<class T>
void Sort<T>::MSort(DataList<T>& L1, DataList<T>& L2, int left, int right)
{
	if (left >= right)return;
	int mid = (left + right) / 2;//���м仮��Ϊ����������
	MSort(L1, L2, left, mid);//����������н��еݹ�����
	MSort(L1, L2, mid + 1, right);//���Ҳ������н��еݹ�����
	Merge(L1, L2, left, mid, right);//�ϲ�
}
//�鲢����
template<class T>
void Sort<T>::MergeSort(DataList<T>& L1)
{
	DataList<T> L2(L1.maxSize);//���츨������L2

	int start = clock();
	MSort(L1, L2, 0, L1.maxSize-1);//�鲢�ĵݹ����
	runtime = clock() - start;
	/*for (int i = 0; i < L1.maxSize; i++)
	{
		cout << L1[i] << " " << endl;
	}*/
}

//ȷ�����λ��
template<class T>
int Sort<T>::MaxBit(DataList<T>& dataList)
{
	Element<int> max = dataList[0];
	for (int i = 1; i < dataList.maxSize; i++)
	{
		compareTimes++;
		if (dataList[i] > max)
			max = dataList[i];//�ҵ�������
	}
	int bit = 1, num = 10;
	while (max.key >= num)//�����������λ��
	{
		bit++;
		num *= 10;
	}
	return bit;
}
//��������
template<class T>
void Sort<T>::RadixSort(DataList<T>& dataList)
{
	int maxBit = MaxBit(dataList);//���λ��
	DataList<int> data(dataList);
	DataList<int> temp(dataList.maxSize);
	int container[10];//���0~9��Ͱ
	int i, j, k;
	int radix = 1;//����

	int start = clock();
	for (i = 0; i < maxBit; i++)
	{
		memset(container, 0, sizeof(int)* 10);
		for (j = 0; j < data.maxSize; j++)
		{
			k = data[j].key / radix % 10;//keyΪ��ǰλ�ϵ�����
			container[k]++;//��ͳ��ÿ��Ͱ�е�Ԫ�ظ���
		}
		for (j = 1; j < 10; j++)
		{
			container[j] += container[j - 1];//���Ÿ�ͰԪ�صĴ��λ��
		}
		for (j = data.maxSize-1; j>=0; j--)//�������������е�Ԫ�ذ�λֵ���䵽����Ͱ�У����ڸ�������temp
		{
			compareTimes++;
			k = data[j].key / radix % 10;//ȡĳλ������
			temp[container[k] - 1] = data[j];//��Ԥ�ȼ���λ�ô��
			container[k]--;//��������һ
		}
		for (j = 0; j < data.maxSize; j++)//�Ӹ�������˳��д��ԭ����
		{
			data[j] = temp[j];
		}
		radix *= 10;//�Ӹ�λ��ʮλ����λ������ǰ�ƶ�
	}

	runtime = clock() - start;
	/*for (i = 0; i < data.maxSize; i++)
	{
		cout << data[i] << " " << endl;
	}*/
}

//�۰��������
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
		while (low <= high)//�����۰���������λ��
		{
			middle = (low + high) / 2;//ȡ�е�
			compareTimes++;
			if (temp < dataList[middle])//����ֵС���е�ֵ
				high = middle - 1;//������С����
			else
				low = middle + 1;//����������С����
		}
		for (k = i - 1; k >= low; k--)//�ɿ��ƶ����ճ�����λ��
		{
			dataList[k + 1] = dataList[k];
		}
		dataList[low] = temp;//����
	}
	runtime = clock() - start;
	/*for (i = 0; i < dataList.maxSize; i++)
	{
	cout << dataList[i] << " " <<endl;
	}*/
}

//ѡ��ʤ��
template <class T>
int Sort<T>::Winner(int a, int b, T* e)
{ 
	compareTimes++;
	return(e[a] <= e[b]) ? a : b;//��С��ʤ
}
//��ʼ��ʤ����
template <class T>
bool Sort<T>::Initial(DataList<T>& dataList,int *t,T *e,int size,int& lowExt,int& offset)
{
	if (size > dataList.maxSize || size < 2)return false;
	int n = size;
	int i, s;
	for (s = 1; 2 * s <= n - 1; s += s);
	lowExt = 2 * (n - s);
	offset = 2 * s - 1;
	for (i = 2; i <= lowExt; i += 2)//��Զ���ⲿ�ڵ�ı���
		Play(t, e, (offset + i) / 2, i - 1, i);
	//���������ⲿ�ڵ�
	if (n % 2 == 0)i = lowExt + 2;
	else//��nΪ����ʱ���ڲ��ڵ�Ҫ���ⲿ�ڵ����
	{
		Play(t, e, n / 2, t[n - 1], lowExt + 1);
		i = lowExt + 3;
	}
	for (; i <= n; i += 2)//iΪ����ʣ��ڵ㣬���������ⲿ�ڵ�ı���
		Play(t, e, (i - lowExt + n - 1) / 2, i - 1, i);
	return true;
}
//ͨ���������̶�����ʼ��
template <class T>
void Sort<T>::Play(int *t, T *e, int k, int lc, int rc)
{
	t[k] = Winner(lc, rc, e);//��e[lc]��e[rc]��ѡ��ʤ��
	while (k > 1 && k % 2 != 0)//������Ů�����ϱ�����ֱ����
	{
		t[k / 2] = Winner(t[k - 1], t[k],e);
		k /= 2;//�����ڵ�
	}
}
//��Ԫ��i�ı�ʱ������֯����
template <class T>
bool Sort<T>::RePlay(DataList<T>& dataList,int i,int lowExt,int offset,T *e,int *t)
{
	if (i <= 0 || i > dataList.maxSize)return false;
	int k, lc, rc;//�����ڵ㼰��������Ů
	if (i <= lowExt)//��Զ���ⲿ�ڵ�����
	{
		k = (offset + i) / 2;//����i�ĸ��ڵ�
		lc = 2 * k - offset;//���㸸�ڵ��������Ů
		rc = lc + 1;
	}
	else//��Զ���ⲿ�ڵ�����
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
	for (; k >= 1; k /= 2)//�����򸸽ڵ����ֱ����
	{
		t[k] = Winner(t[2 * k], t[2 * k + 1], e);
	}
}
//����������
template<class T>
void Sort<T>::TournamentSort(DataList<T>& dataList)
{
	int lowExt, offset;//��Զ���ⲿ�ڵ�����Ͱ�������ڵ�������һ��Ϊ��һ���ⲿ�ڵ㣩
	int *t=new int[dataList.maxSize];//ʤ��������
	T *e=new T[dataList.maxSize+1];//ѡ������
	int i;
	int size = dataList.maxSize;

	int start = clock();
	for (i = 1; i <= dataList.maxSize; i++) e[i]=dataList[i- 1].key;//ѡ�������ʼ��
	Initial(dataList,t, e, size, lowExt, offset);//�����ʼʤ����
	for (i = 1; i <= dataList.maxSize; i++)
	{
		dataList[i - 1] = e[t[1]];//���ʤ��
		e[t[1]] = maxValue;//�޸�ʤ�ߵ�ֵ
		RePlay(dataList, t[1], lowExt, offset, e,t);//�ع�ʤ������ѡ���µ�ʤ��
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

