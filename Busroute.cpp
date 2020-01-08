#include<iostream>
#include<map>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<map>
#include<queue>
#include<fstream>
#include<ctime>
#include<set>
using namespace std;
struct DjNode {
	int distance;
	int pre;
	bool flag;
	int name;
	int prebus;
	DjNode() {
		distance = INT_MAX-1;
		flag = false;
	}
	const bool operator < (const DjNode& a) const {
		return a.distance < distance;
	}
};
map<int,string> mp;
map<string,int> mp2;
map<int, int> buss;
vector<int> bus[1000];
int *busname=(int*)malloc(sizeof(int) * 1000);
int busnum=1;
int stationnum = 0;
int InitBus()
{
	fstream fp;
	fp.open("南京公交线路.txt", ios::in);
	int i=0;
	int k = 0;
	string temp;
	fp >> busname[i];
	buss.insert({ busname[i],i });
	while (!fp.eof())
	{
		while (!fp.eof())
		{
			fp >> temp;
			int flag = 0;
			for (int j = 0; j < temp.length(); j++)
			{
				int flag1 = 0;
				if (temp[j]<'0' || temp[j]>'9')
				{
					flag = 1;
					map<string, int>::iterator it;
					it = mp2.find(temp);
					if (it!=mp2.end())
					{
						bus[i].push_back(it->second);
						flag1 = 1;
						break;
					}
					if (flag1 == 1)
						break;
					bus[i].push_back(stationnum);
					mp.insert({ stationnum,temp });
					mp2.insert({ temp,stationnum });
					stationnum++;
					break;
				}
			}
			if (flag == 0)
			{
				i++;
				busnum++;
				busname[i] = stoi(temp);
				buss.insert({ busname[i],i });
				break;
			}
		}
	}
	cout << "线路读取完成！" << endl;
	fp.close();
	return 1;
}

DjNode* Dj = new DjNode[6000];
typedef struct {
	int name;
	vector<vector<int>> bus;
	vector<int> vicinity;
}MNode;
typedef struct {
	vector<MNode> Graph;
	int vexnum;
}MGraph;

void CreateGraph(MGraph& G)
{
	int start, end;
	auto it = mp.begin();
	vector<vector<int>> nothing;
	vector<int> nope;
	for (int i = 0; i < mp.size(); i++)
	{
		G.Graph.push_back({ it->first,nothing,nope });
		it++;
	}
	G.vexnum = mp.size();
	for (int i = 0; i < busnum; i++)
	{
		for (int j = 0; j < bus[i].size()-1; j++)
		{
			int flag = 0,flag2=0;
			start = bus[i][j];
			end = bus[i][j + 1];
			for (int t = 0; t < G.Graph[start].vicinity.size(); t++)
			{
				if (G.Graph[start].vicinity[t] == end)
				{
					G.Graph[start].bus[t].push_back(busname[i]);
					flag = 1;
				}
			}
			for (int k = 0; k < G.Graph[end].vicinity.size(); k++)
			{
				if (G.Graph[end].vicinity[k] == start)
				{
					G.Graph[end].bus[k].push_back(busname[i]);
					flag = 1;
				}
			}
			if (flag == 0)
			{
				G.Graph[start].vicinity.push_back(end);
				G.Graph[start].bus.push_back({ busname[i] });
			}
			if (flag2 == 0)
			{
				G.Graph[end].vicinity.push_back(start);
				G.Graph[end].bus.push_back({ busname[i] });
			}
		}
	}
	cout << "交通网络建立完成" << endl;
}
priority_queue <DjNode> q;
void Dijkstra(MGraph G, int start)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		Dj[i].flag = false;
		Dj[i].name = G.Graph[i].name;
		Dj[i].distance = INT_MAX - 1;
		Dj[i].pre = start;
	}
	Dj[start].distance = 0;
	Dj[start].pre = start;
	q.push(Dj[start]);
	while (!q.empty())
	{
		DjNode temp = q.top();
		q.pop();
		if (Dj[temp.name].flag == true)
			continue;
		Dj[temp.name].flag = true;
		for (int i = 0; i < G.Graph[temp.name].vicinity.size(); i++)
		{
			if (Dj[G.Graph[temp.name].vicinity[i]].flag == true)
				continue;
			if (Dj[G.Graph[temp.name].vicinity[i]].distance > Dj[temp.name].distance + 1)
			{
				Dj[G.Graph[temp.name].vicinity[i]].distance = Dj[temp.name].distance + 1;
				Dj[G.Graph[temp.name].vicinity[i]].pre = Dj[temp.name].name;
				q.push(Dj[G.Graph[temp.name].vicinity[i]]);
			}
		}
	}
}

void leastchange(MGraph G, int start)
{
	int level = 0;
	for (int i = 0; i < G.vexnum; i++)
	{
		Dj[i].flag = false;
		Dj[i].name = G.Graph[i].name;
		Dj[i].distance = INT_MAX - 1;
		Dj[i].pre = start;
		Dj[i].prebus = 0;
	}
	Dj[start].distance = 0;
	Dj[start].pre = start;
	q.push(Dj[start]);
	while (!q.empty())
	{
		DjNode temp = q.top();
		q.pop();
		if (Dj[temp.name].flag == true)
			continue;
		Dj[temp.name].flag = true;
		for (int i = 0; i < G.Graph[temp.name].bus.size(); i++)
		{
			for (int j = 0; j < G.Graph[temp.name].bus[i].size(); j++)
			{
				int tempbus = G.Graph[temp.name].bus[i][j];
				int pos = buss[tempbus];
				for (int k = 0; k < bus[pos].size(); k++)
				{
					if (bus[pos][k] == temp.name)
					{
						int s;
						if (level != 0)
						{
							for (s = 0; s < bus[pos].size(); s++)
							{
								if (Dj[bus[pos][s]].flag == true)
									continue;
								if (Dj[temp.name].distance+1 < Dj[bus[pos][s]].distance)
								{
									Dj[bus[pos][s]].distance = Dj[temp.name].distance+1;
									Dj[bus[pos][s]].pre = temp.name;
									q.push(Dj[bus[pos][s]]);
									Dj[bus[pos][s]].prebus = tempbus;
								}
							}
						}
						else if (level == 0)
						{
							for (s = 0; s < bus[pos].size(); s++)
							{
								if (Dj[bus[pos][s]].flag == true)
									continue;
								Dj[bus[pos][s]].distance = 0;
								Dj[bus[pos][s]].pre = temp.name;
								q.push(Dj[bus[pos][s]]);
								Dj[bus[pos][s]].prebus = tempbus;
							}
						}
						if (s == bus[pos].size())
							break;
					}
				}
			}
		}
		level++;
	}
}

int SearchsPath(MGraph G, int start, int end)
{
	int v = end;
	int *a=new int[5000];
	int sum = 0;
	if (Dj[end].distance == INT_MAX-1)
	{
		cout << "Cant Reach!" << endl;
		return 0;
	}
	while (v != start)
	{
		a[sum] = v;
		v = Dj[v].pre;
		sum++;
	}
	cout << mp[start] << "->";
	for (int i = sum - 1; i >= 1; i--)
	{
		cout << mp[a[i]] << "->";
	}
	cout << mp[a[0]] << endl;
	cout << "经过站点数目:" << Dj[end].distance << endl;
	return 1;
}

int SearchlPath(MGraph G, int start, int end)
{
	int v = end;
	int* a = new int[5000];
	int sum = 0;
	if (Dj[end].distance == INT_MAX - 1)
	{
		cout << "Cant Reach!" << endl;
		return 0;
	}
	while (v != start)
	{
		a[sum] = v;
		v = Dj[v].pre;
		sum++;
	}
	cout << mp[start] << "->";
	for (int i = sum - 1; i >= 1; i--)
	{
		cout <<"("<<Dj[a[i]].prebus<<")" <<mp[a[i]] << "->";
	}
	cout << "(" << Dj[a[0]].prebus << ")" <<mp[a[0]] << endl;
	cout << "换乘次数:" << Dj[end].distance << endl;
	return 1;
}

int main()
{
	MGraph G;
	InitBus();
	CreateGraph(G);
	string start,end;
	int a, b;
	while (1)
	{
		cout << "                                        1.最短路径" << " " << "2.最少换乘" <<" 3.退出"<< endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			cout << "                                        请输入起点与终点：" << endl;
			cin >> start >> end;
			Dijkstra(G, mp2[start]);
			SearchsPath(G, mp2[start], mp2[end]);
		}
		else if (choice == 2)
		{
			cout << "                                        请输入起点与终点：" << endl;
			cin >> start >> end;
			leastchange(G, mp2[start]);
			SearchlPath(G, mp2[start], mp2[end]);
		}
		else
			break;
	}
	return 0;
}