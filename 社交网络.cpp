#include<iostream>
#include<vector>
#include<iomanip>
#include<queue>
#define INT_MAX 500000
using namespace std;
struct Edge {
	vector<int> to;
	int name;
};

struct Graph {
	vector<Edge> e;
	int vexnum, arcnum;
};

struct DjNode {
	int name;
	int distance;
	int pre;
	int flag;
};
DjNode* DJ = new DjNode[5000];
void Dj(int start, Graph G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		DJ[i].distance = INT_MAX - 1;
		DJ[i].flag = false;
		DJ[i].name = G.e[i].name;
		DJ[i].pre = start;
	}
	DJ[start - 1].pre = start;
	DJ[start - 1].flag = true;
	DJ[start - 1].distance = 0;
	for (int i = 0; i < G.e[start-1].to.size(); i++)
	{
		if (DJ[start-1].distance + 1 < DJ[G.e[start-1].to[i] - 1].distance)
		{
			DJ[G.e[start-1].to[i] - 1].distance = DJ[start-1].distance + 1;
			DJ[G.e[start-1].to[i] - 1].pre = start;
		}
	}
	while (1)
	{
		int minnposition = 0, minn = INT_MAX;
		for (int i = 0; i < G.vexnum; i++)
		{
			if (DJ[i].flag == true)
				continue;
			if (DJ[i].distance < minn)
			{
				minn = DJ[i].distance;
				minnposition = i;
			}
		}
		DJ[minnposition].flag = true;
		for (int i = 0; i < G.e[minnposition].to.size(); i++)
		{
			if (DJ[minnposition].distance + 1 < DJ[G.e[minnposition].to[i] - 1].distance)
			{
				DJ[G.e[minnposition].to[i] - 1].distance = DJ[minnposition].distance + 1;
				DJ[G.e[minnposition].to[i] - 1].pre = minnposition + 1;
			}
		}
		int sum = 0;
		for (int i = 0; i < G.vexnum; i++)
		{
			if (DJ[i].flag == true)
			{
				sum++;
			}
		}
		if (sum == G.vexnum)
			break;
	}
}
queue<int> s;
int Visit[100000];
int BFS(Graph G)
{
	int sum = 0;
	s.push(G.e[0].name);
	Visit[G.e[0].name] = 1;
	sum++;
	while (!s.empty())
	{
		int temp = s.front();
		s.pop();
		for (int i = 0; i < G.e[temp - 1].to.size(); i++)
		{
			if (Visit[G.e[temp - 1].to[i]] != 1)
			{
				s.push(G.e[temp - 1].to[i]);
				Visit[G.e[temp - 1].to[i]] = 1;
				sum++;
			}
		}
	}
	if (sum != G.vexnum)
	{
		return 0;
	}
	return 1;
}

int main()
{
	int n, m;
	Graph G;
	vector<int> nope;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		G.e.push_back({ nope,i + 1 });
	}
	G.vexnum = n;
	G.arcnum = m;
	while (m--)
	{
		int start, end;
		cin >> start >> end;
		G.e[start - 1].to.push_back(end);
		G.e[end - 1].to.push_back(start);
	}
	int t, s;
	int g = BFS(G);
	cin >> t;
	while (t--)
	{
		cin >> s;
		Dj(s,G);
		float ssum = 0;
		float end;
		for (int i = 0; i < G.vexnum; i++)
		{
			if (i == s - 1)
				continue;
			if (DJ[i].distance == INT_MAX - 1)
			{
				continue;
			}
			ssum += DJ[i].distance;
		}
		if (g == 1)
		{
			end = 1 / (ssum / (G.vexnum - 1));
			cout << "Cc(" << s << ")=" << setprecision(2) << end << endl;
		}
		else if (g == 0)
		{
			cout << "Cc(" << s << ")=" << 0 << endl;
		}
	}
}