//---------------------------------------------非递归加栈和BFS两种算法的实现和主函数=======================================================
#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>
using namespace std;

int n,m;//迷宫行数，列数
pair<int, int> before[500][500];//用于记录某一个点的前一个点，方便最后找到迷宫路径

//初始化迷宫地图和各位置的访问状态
void Init(char **&maze,int **&mark)
{
	int i, j;
	cout << "请输入迷宫地图：" << endl;

	//迷宫数组maze,标记数组mark
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
			cin >> maze[i][j];//输入迷宫地图
			mark[i][j] = 0;//所有位置设为未访问状态
		}
	}
}

//算法一：非递归加栈
vector<pair<int, int>> FindPath(char **maze, int **mark, int x, int y)
{
	stack<pair<int, int>> st;//栈
	vector<pair<int, int>> vec;//存放结果的向量

	st.push(make_pair(x, y));//将起点放入栈中
	int dx[4] = { 0,0,1,-1 };
	int dy[4] = { 1,-1,0,0 };
	bool flag = false;

	while (!st.empty())
	{
		pair<int, int> temp = st.top();//取栈顶元素
		st.pop();//出栈
		mark[temp.first][temp.second] = 1;//标识该点已被访问
		for (int i = 0; i < 4; i++)//分别向下，上，右，左四个方向试探
		{
			int tempx = temp.first + dx[i];
			int tempy = temp.second + dy[i];
			if (tempx != -1 && tempx != n && tempy != -1 && tempy != m && mark[tempx][tempy] == 0 && maze[tempx][tempy] == '0')//若非边界，未访问，该点可通行
			{
				before[tempx][tempy] = temp;//说明该点在出迷宫路线上，保存该点的上一个点
				mark[tempx][tempy] = mark[temp.first][temp.second] + 1;//计算走到该点需要走过的步数
				st.push(make_pair(tempx, tempy));//将该点加入栈中
				if (tempx == 0 || tempx == n - 1 || tempy == 0 || tempy == m - 1)//是边界
				{
					vec.push_back(make_pair(tempx, tempy));//将终点加入结果栈
					while (tempx!=x||tempy!=y)//当未回溯到起点时
					{
						auto last = before[tempx][tempy];//回到某一个点的前一个点
						vec.push_back(last);
						tempx = last.first;//取x坐标
						tempy = last.second;//取y坐标
					}
					return vec;
				}
			}
		}
	}
	return vec;
}

//算法二：广度优先搜索算法
int BFS(char** maze, int** mark, int x, int y, int& resx, int& resy)
{
	int dx[4] = { 0,0,1,-1 };
	int dy[4] = { 1,-1,0,0 };
	deque<pair<int, int>> rec;//广搜使用的队列
	rec.push_back(make_pair(x, y));//将起点加入队列
	mark[x][y] = 1;//起点访问状态置为1
	while (!rec.empty())//队列不为空时进行循环
	{
		auto temp = rec.front();//取队列首元素
		rec.pop_front();//冒出队列
		for (int i = 0; i < 4; i++)
		{
			int tempx = temp.first + dx[i];
			int tempy = temp.second + dy[i];
			if (tempx != -1 && tempx != n && tempy != -1 && tempy != m && mark[tempx][tempy]==0 && maze[tempx][tempy] == '0')//若当前位置非边界，未访问，可通行
			{
				mark[tempx][tempy] = mark[temp.first][temp.second] + 1;//计算走到该点需要的步数
				if (tempx == 0 || tempx == n - 1 || tempy == 0 || tempy == m - 1)//若达到边界
				{
					resx = tempx;//记录出口横坐标
					resy = tempy;//记录出口纵坐标
					return mark[tempx][tempy];//返回走到该点需要的步数
				}
				rec.push_back(make_pair(tempx, tempy));//若未达到边界则把当前点加入队列中
			}
		}
	}
	return 0;
}
//根据路线上各点标记的步数找到迷宫路线
bool FindAns(char** maze, int** mark, int x, int y, int ax, int ay, int flag, vector<pair<int, int>>& result)
{
	if (mark[x][y] == flag && ax==x && ay==y)return true;//达到终点时返回
	
	int dx[4] = { 0,0,1,-1 };
	int dy[4] = { 1,-1,0,0 };
	for (int i = 0; i < 4; i++)//分别向下，上，右，左四个方向循环
	{
		int tempx = x + dx[i];
		int tempy = y + dy[i];
		if (tempx != -1 && tempx != n && tempy != -1 && tempy != m && mark[x][y]+1==mark[tempx][tempy])//判断为迷宫路径上该点的的下一个点
		{
			if (FindAns(maze, mark, tempx, tempy, ax,ay, flag, result))
			{
				result.push_back(make_pair(tempx, tempy));//将该点加入到结果栈，最后输出
				return true;
			}
		}
	}
	return false;
}

//打印结果，即迷宫路径和包含了路径的迷宫地图
void Output(char** maze, vector<pair<int, int>> result)
{
	if (result.size() <= 1)
	{
		cout << "此迷宫地图没有有效出口！";
		return;
	}
	int i, j;
	//打印标记了出口路线的迷宫地图
	cout << "\n迷宫地图：\n" << endl;
	cout << left;
	cout << setw(8) << " ";
	for (auto o : result)//将所有走过的点做记号为“X”
	{
		maze[o.first][o.second] = 'X';
	}
	for (i = 0; i < m; i++)
	{
		cout << i << "列     ";
	}
	cout << endl;
	for (i = 0; i < n; i++)
	{
		cout << i << "行     ";
		for (j = 0; j < m; j++)
		{
			cout << setw(8) << maze[i][j];
		}
		cout << "\n" << endl;
	}
	//打印查找到的路径
	cout << "迷宫路径：" << endl;
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
	char **maze=nullptr;//迷宫地图
	int **mark=nullptr;//标记是否走过
	cout << "请输入迷宫的行数：" << endl;
	cin >> n;
	cout << "请输入迷宫的列数：" << endl;
	cin >> m;
	Init(maze, mark);//初始化迷宫地图
	int x, y;
	cout << "请输入迷宫起点x和y,以空格作为分隔：" << endl;
	cin >> x >> y;

	vector<pair<int, int>> result;//存放找到的路径结果
	int step;//记录步数
	int choice;
	cout << "请选择算法类型：（1表示非递归加栈算法，0表示BFS算法）"<<endl;
	cin >> choice;
	if (choice)//choice为1时，调用非递归加栈的算法
	{
		result = FindPath(maze, mark, x, y);
	}
	else//choice为0时，调用BFS算法
	{
		int endx, endy;//记录终点
		if (step = BFS(maze, mark, x, y, endx, endy))//迷宫出口存在的时候进入循环
		{
			FindAns(maze, mark, x, y, endx, endy, step, result);
			result.push_back(make_pair(x, y));
		}
	}
	Output(maze, result);//输出结果

	getchar();
	getchar();
	return 0;
}
