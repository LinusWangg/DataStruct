#include<iostream>
#include<vector>
#include<math.h> 
#include<iomanip>
using namespace std;
struct tow {
	int name;
	int type;
	long long distance;
};
struct Edge {
	vector<tow> to;
	int name;
};

struct Graph {
	vector<Edge> e;
	int vexnum, arcnum;
};

struct DjNode {
	int name;
	long long distance;
	int pre;
	int flag;
	int type;
	long long sroad;
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
		DJ[i].type = 0;
		DJ[i].sroad = 0;
	}
	DJ[start - 1].pre = start;
	DJ[start - 1].flag = true;
	DJ[start - 1].distance = 0;
	for (int i = 0; i < G.e[start - 1].to.size(); i++)
	{
		if (G.e[start - 1].to[i].type == 0)
		{
			if (DJ[start - 1].distance + G.e[start-1].to[i].distance < DJ[G.e[start - 1].to[i].name - 1].distance)
			{
				DJ[G.e[start - 1].to[i].name - 1].distance = DJ[start - 1].distance + G.e[start - 1].to[i].distance;
				DJ[G.e[start - 1].to[i].name - 1].pre = start;
				DJ[G.e[start - 1].to[i].name - 1].type = 0;
				DJ[G.e[start - 1].to[i].name - 1].sroad = 0;
			}
		}
		else
		{
			if (DJ[start - 1].distance + G.e[start - 1].to[i].distance*G.e[start-1].to[i].distance < DJ[G.e[start - 1].to[i].name - 1].distance)
			{
				DJ[G.e[start - 1].to[i].name - 1].distance = DJ[start - 1].distance + G.e[start - 1].to[i].distance * G.e[start - 1].to[i].distance;
				DJ[G.e[start - 1].to[i].name - 1].pre = start;
				DJ[G.e[start - 1].to[i].name - 1].type = 1;
				DJ[G.e[start - 1].to[i].name - 1].sroad = G.e[start - 1].to[i].distance * G.e[start - 1].to[i].distance;
			}
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
			if (G.e[minnposition].to[i].type == 0)
			{
				if (DJ[minnposition].distance + G.e[minnposition].to[i].distance < DJ[G.e[minnposition].to[i].name - 1].distance)
				{
					DJ[G.e[minnposition].to[i].name - 1].distance = DJ[minnposition].distance + G.e[minnposition].to[i].distance;
					DJ[G.e[minnposition].to[i].name - 1].pre = minnposition+1;
					DJ[G.e[minnposition].to[i].name - 1].sroad = 0;
					DJ[G.e[minnposition].to[i].name - 1].type = 0;
				}
			}
			else if(G.e[minnposition].to[i].type==1&&DJ[minnposition].type==0)
			{
				if (DJ[minnposition].distance + G.e[minnposition].to[i].distance * G.e[minnposition].to[i].distance < DJ[G.e[minnposition].to[i].name - 1].distance)
				{
					DJ[G.e[minnposition].to[i].name - 1].distance = DJ[minnposition].distance + G.e[minnposition].to[i].distance * G.e[minnposition].to[i].distance;
					DJ[G.e[minnposition].to[i].name - 1].pre = minnposition+1;
					DJ[G.e[minnposition].to[i].name - 1].sroad = G.e[minnposition].to[i].distance * G.e[minnposition].to[i].distance;
					DJ[G.e[minnposition].to[i].name - 1].type = 1;
				}
			}
			else if (G.e[minnposition].to[i].type == 1 && DJ[minnposition].type == 1)
			{
				if (DJ[minnposition].distance-DJ[minnposition].sroad + (sqrt(DJ[minnposition].sroad) + G.e[minnposition].to[i].distance) * (sqrt(DJ[minnposition].sroad) + G.e[minnposition].to[i].distance) < DJ[G.e[minnposition].to[i].name - 1].distance)
				{
					DJ[G.e[minnposition].to[i].name - 1].distance = DJ[minnposition].distance-DJ[minnposition].sroad + (sqrt(DJ[minnposition].sroad) + G.e[minnposition].to[i].distance) * (sqrt(DJ[minnposition].sroad) + G.e[minnposition].to[i].distance);
					DJ[G.e[minnposition].to[i].name - 1].pre = minnposition + 1;
					DJ[G.e[minnposition].to[i].name - 1].sroad = (sqrt(DJ[minnposition].sroad) + G.e[minnposition].to[i].distance) * (sqrt(DJ[minnposition].sroad) + G.e[minnposition].to[i].distance);
					DJ[G.e[minnposition].to[i].name - 1].type = 1;
				}
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

int main()
{
	int n, m;
	Graph G;
	vector<tow> nope;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		G.e.push_back({ nope,i + 1 });
	}
	G.vexnum = n;
	G.arcnum = m;
	while (m--)
	{
		int start, end,type,distance;
		cin >>type>> start >> end>>distance;
		G.e[start - 1].to.push_back({end,type,distance});
		G.e[end - 1].to.push_back({start,type,distance});
	}
	Dj(1,G);
	cout << DJ[G.vexnum - 1].distance << endl;
	vector<int> sta;
	for (int i = 1; i < G.vexnum; i++)
	{
		int temp = DJ[i].name;
		while (DJ[temp - 1].pre != temp)
		{
			temp = DJ[temp - 1].pre;
			sta.push_back(temp);
		}
		for (int i = sta.size() - 1; i >= 0; i--)
		{
			cout << sta[i] << "-";
		}
		cout << DJ[i].name << " distance:" << DJ[i].distance << endl;
		sta.clear();
	}
}
