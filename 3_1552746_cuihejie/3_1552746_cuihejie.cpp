//---------------------------------------------�ǵݹ��ջ��BFS�����㷨��ʵ�ֺ�������=======================================================
#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>
using namespace std;

int n,m;//�Թ�����������
pair<int, int> before[500][500];//���ڼ�¼ĳһ�����ǰһ���㣬��������ҵ��Թ�·��

//��ʼ���Թ���ͼ�͸�λ�õķ���״̬
void Init(char **&maze,int **&mark)
{
	int i, j;
	cout << "�������Թ���ͼ��" << endl;

	//�Թ�����maze,�������mark
	maze = new char*[n];
	mark = new int*[n];
	for (i = 0; i < n; i++)
	{
		maze[i] = new char[m];
		mark[i] = new int[m];
	}
	for (i = 0; i < n; i++)
	{
		for (j= 0; j< m; j++)
		{
			cin >> maze[i][j];//�����Թ���ͼ
			mark[i][j] = 0;//����λ����Ϊδ����״̬
		}
	}
}

//�㷨һ���ǵݹ��ջ
vector<pair<int, int>> FindPath(char **maze, int **mark, int x, int y)
{
	stack<pair<int, int>> st;//ջ
	vector<pair<int, int>> vec;//��Ž��������

	st.push(make_pair(x, y));//��������ջ��
	int dx[4] = { 0,0,1,-1 };
	int dy[4] = { 1,-1,0,0 };
	bool flag = false;

	while (!st.empty())
	{
		pair<int, int> temp = st.top();//ȡջ��Ԫ��
		st.pop();//��ջ
		mark[temp.first][temp.second] = 1;//��ʶ�õ��ѱ�����
		for (int i = 0; i < 4; i++)//�ֱ����£��ϣ��ң����ĸ�������̽
		{
			int tempx = temp.first + dx[i];
			int tempy = temp.second + dy[i];
			if (tempx != -1 && tempx != n && tempy != -1 && tempy != m && mark[tempx][tempy] == 0 && maze[tempx][tempy] == '0')//���Ǳ߽磬δ���ʣ��õ��ͨ��
			{
				before[tempx][tempy] = temp;//˵���õ��ڳ��Թ�·���ϣ�����õ����һ����
				mark[tempx][tempy] = mark[temp.first][temp.second] + 1;//�����ߵ��õ���Ҫ�߹��Ĳ���
				st.push(make_pair(tempx, tempy));//���õ����ջ��
				if (tempx == 0 || tempx == n - 1 || tempy == 0 || tempy == m - 1)//�Ǳ߽�
				{
					vec.push_back(make_pair(tempx, tempy));//���յ������ջ
					while (tempx!=x||tempy!=y)//��δ���ݵ����ʱ
					{
						auto last = before[tempx][tempy];//�ص�ĳһ�����ǰһ����
						vec.push_back(last);
						tempx = last.first;//ȡx����
						tempy = last.second;//ȡy����
					}
					return vec;
				}
			}
		}
	}
	return vec;
}

//�㷨����������������㷨
int BFS(char** maze, int** mark, int x, int y, int& resx, int& resy)
{
	int dx[4] = { 0,0,1,-1 };
	int dy[4] = { 1,-1,0,0 };
	deque<pair<int, int>> rec;//����ʹ�õĶ���
	rec.push_back(make_pair(x, y));//�����������
	mark[x][y] = 1;//������״̬��Ϊ1
	while (!rec.empty())//���в�Ϊ��ʱ����ѭ��
	{
		auto temp = rec.front();//ȡ������Ԫ��
		rec.pop_front();//ð������
		for (int i = 0; i < 4; i++)
		{
			int tempx = temp.first + dx[i];
			int tempy = temp.second + dy[i];
			if (tempx != -1 && tempx != n && tempy != -1 && tempy != m && mark[tempx][tempy]==0 && maze[tempx][tempy] == '0')//����ǰλ�÷Ǳ߽磬δ���ʣ���ͨ��
			{
				mark[tempx][tempy] = mark[temp.first][temp.second] + 1;//�����ߵ��õ���Ҫ�Ĳ���
				if (tempx == 0 || tempx == n - 1 || tempy == 0 || tempy == m - 1)//���ﵽ�߽�
				{
					resx = tempx;//��¼���ں�����
					resy = tempy;//��¼����������
					return mark[tempx][tempy];//�����ߵ��õ���Ҫ�Ĳ���
				}
				rec.push_back(make_pair(tempx, tempy));//��δ�ﵽ�߽���ѵ�ǰ����������
			}
		}
	}
	return 0;
}
//����·���ϸ����ǵĲ����ҵ��Թ�·��
bool FindAns(char** maze, int** mark, int x, int y, int ax, int ay, int flag, vector<pair<int, int>>& result)
{
	if (mark[x][y] == flag && ax==x && ay==y)return true;//�ﵽ�յ�ʱ����
	
	int dx[4] = { 0,0,1,-1 };
	int dy[4] = { 1,-1,0,0 };
	for (int i = 0; i < 4; i++)//�ֱ����£��ϣ��ң����ĸ�����ѭ��
	{
		int tempx = x + dx[i];
		int tempy = y + dy[i];
		if (tempx != -1 && tempx != n && tempy != -1 && tempy != m && mark[x][y]+1==mark[tempx][tempy])//�ж�Ϊ�Թ�·���ϸõ�ĵ���һ����
		{
			if (FindAns(maze, mark, tempx, tempy, ax,ay, flag, result))
			{
				result.push_back(make_pair(tempx, tempy));//���õ���뵽���ջ��������
				return true;
			}
		}
	}
	return false;
}

//��ӡ��������Թ�·���Ͱ�����·�����Թ���ͼ
void Output(char** maze, vector<pair<int, int>> result)
{
	if (result.size() <= 1)
	{
		cout << "���Թ���ͼû����Ч���ڣ�";
		return;
	}
	int i, j;
	//��ӡ����˳���·�ߵ��Թ���ͼ
	cout << "\n�Թ���ͼ��\n" << endl;
	cout << left;
	cout << setw(8) << " ";
	for (auto o : result)//�������߹��ĵ����Ǻ�Ϊ��X��
	{
		maze[o.first][o.second] = 'X';
	}
	for (i = 0; i < m; i++)
	{
		cout << i << "��     ";
	}
	cout << endl;
	for (i = 0; i < n; i++)
	{
		cout << i << "��     ";
		for (j = 0; j < m; j++)
		{
			cout << setw(8) << maze[i][j];
		}
		cout << "\n" << endl;
	}
	//��ӡ���ҵ���·��
	cout << "�Թ�·����" << endl;
	cout << endl;
	for (int k = result.size() - 1; k >= 0; k--)
	{
		cout  << "<" << result[k].first << "," << result[k].second << ">";
		if (k != 0)cout << "-->";
	}
	cout << endl;
}

int main()
{
	char **maze=nullptr;//�Թ���ͼ
	int **mark=nullptr;//����Ƿ��߹�
	cout << "�������Թ���������" << endl;
	cin >> n;
	cout << "�������Թ���������" << endl;
	cin >> m;
	Init(maze, mark);//��ʼ���Թ���ͼ
	int x, y;
	cout << "�������Թ����x��y,�Կո���Ϊ�ָ���" << endl;
	cin >> x >> y;

	vector<pair<int, int>> result;//����ҵ���·�����
	int step;//��¼����
	int choice;
	cout << "��ѡ���㷨���ͣ���1��ʾ�ǵݹ��ջ�㷨��0��ʾBFS�㷨��"<<endl;
	cin >> choice;
	if (choice)//choiceΪ1ʱ�����÷ǵݹ��ջ���㷨
	{
		result = FindPath(maze, mark, x, y);
	}
	else//choiceΪ0ʱ������BFS�㷨
	{
		int endx, endy;//��¼�յ�
		if (step = BFS(maze, mark, x, y, endx, endy))//�Թ����ڴ��ڵ�ʱ�����ѭ��
		{
			FindAns(maze, mark, x, y, endx, endy, step, result);
			result.push_back(make_pair(x, y));
		}
	}
	Output(maze, result);//������

	getchar();
	getchar();
	return 0;
}
