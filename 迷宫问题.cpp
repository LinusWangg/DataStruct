#include<iostream>
#include<stack>
#include<memory>
#include<queue>
#include<fstream>
using namespace std;
int sx, sy, ex, ey;
int n, m;
int Graph[1000][1000];
bool flag[1000][1000];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
struct node {
	int x=sx;
	int y=sy;
};
stack<node> s;
queue<node> path;
int BFS()
{
	node start;
	path.push(start);
	while (!path.empty())
	{
		int flag1 = 0;
		node start = path.front();
		path.pop();
		flag[start.x][start.y] = true;
		if (start.x == ex && start.y == ey)
		{
			return 1;
		}
		Graph[start.x][start.y] = 2;
		for (int i = 0; i < 4; i++)
		{
			if (start.x + dx[i] >= 0 && start.x + dx[i] <= n - 1 && start.y + dy[i] >= 0 && start.y + dy[i] <= m - 1&&flag[start.x+dx[i]][start.y+dy[i]]==false)
			{
				node temp;
				temp.x = start.x + dx[i];
				temp.y = start.y + dy[i];
				path.push(temp);
				flag1 = 1;
			}
		}
		if (flag1 == 0)
		{
			Graph[start.x][start.y] = 3;
		}
	}
	return 0;
}

int DFS()
{
	node start;
	s.push(start);
	while (!s.empty())
	{
		int flag1 = 0;
		node start = s.top();
		s.pop();
		flag[start.x][start.y] = true;
		if (start.x == ex && start.y == ey)
		{
			return 1;
		}
		Graph[start.x][start.y] = 2;
		for (int i = 0; i < 4; i++)
		{
			if (start.x + dx[i] >= 0 && start.x + dx[i] <= n - 1 && start.y + dy[i] >= 0 && start.y + dy[i] <= m - 1 && flag[start.x + dx[i]][start.y + dy[i]] == false)
			{
				node temp;
				temp.x = start.x + dx[i];
				temp.y = start.y + dy[i];
				s.push(temp);
				flag1 = 1;
			}
		}
		if (flag1 == 0)
		{
			Graph[start.x][start.y] = 3;
		}
	}
	return 0;
}

int main()
{
	fstream fp;
	memset(flag, false, sizeof(flag));
	cout << "DFS" << endl;
	fp.open("1.txt", ios::in);
	fp >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fp >> Graph[i][j];
			if (Graph[i][j] == 1)
				flag[i][j] = true;
		}
	}
	cin >> sx >> sy >> ex >> ey;
	cout << DFS()<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (Graph[i][j] == 2 && i == sx && j == sy)
			{
				cout << "S ";
				continue;
			}
			if (Graph[i][j] == 0 && i == ex && j == ey)
			{
				cout << "E ";
				continue;
			}
			if (Graph[i][j] == 0)
			{
				cout << "_ ";
			}
			if (Graph[i][j] == 1)
			{
				cout << "x ";
			}
			if (Graph[i][j] == 2)
			{
				cout << "* ";
			}
			if (Graph[i][j] == 3)
			{
				cout << "# ";
			}
		}
		cout << endl;
	}
	fp.close();
	memset(flag, false, sizeof(flag));
	cout << "BFS" << endl;
	fp.open("1.txt", ios::in);
	fp >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fp >> Graph[i][j];
			if (Graph[i][j] == 1)
				flag[i][j] = true;
		}
	}
	cin >> sx >> sy >> ex >> ey;
	cout << BFS() << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (Graph[i][j] == 2 && i == sx && j == sy)
			{
				cout << "S ";
				continue;
			}
			if (Graph[i][j] == 0 && i == ex && j == ey)
			{
				cout << "E ";
				continue;
			}
			if (Graph[i][j] == 0)
			{
				cout << "_ ";
			}
			if (Graph[i][j] == 1)
			{
				cout << "x ";
			}
			if (Graph[i][j] == 2)
			{
				cout << "* ";
			}
			if (Graph[i][j] == 3)
			{
				cout << "# ";
			}
		}
		cout << endl;
	}
	fp.close();
}