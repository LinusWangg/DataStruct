#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<fstream>
using namespace std;
#define MAX_NUM 20
#define VexType int
#define OK 1
#define ERROR 0
#define QElemType int
typedef enum { DG, DN, UDG, UDN }GraphKind;
struct PrVex {
	float distance;
	VexType vex;
	bool flag;
};
PrVex* Pr = new PrVex[10000000];
typedef struct ArcCell {
	int adj;
	float weight;
}ArcCell, AdjMatrix[MAX_NUM][MAX_NUM];
typedef struct {
	VexType vexs[MAX_NUM];
	AdjMatrix arcs;
	int vexnum, arcnum;
	int kind;
}MGraph;
int Visit[1000001];
typedef struct QNode {
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;
typedef struct {
	QueuePtr front;
	QueuePtr rear;
	int length;
}LinkQueue;
vector<char> staname;
int InitQueue(LinkQueue& Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
		exit(0);
	Q.front->next = NULL;
	Q.length = 0;
	return OK;
}

int EnQueue(LinkQueue& Q, int e)
{
	QNode* p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(0);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	Q.length++;
	return OK;
}

int DeQueue(LinkQueue& Q, int& e)
{
	if (Q.front == Q.rear)
		return ERROR;
	QNode* p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)
	{
		Q.rear = Q.front;
	}
	free(p);
	Q.length--;
	return OK;
}

int QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return 1;
	return 0;
}

int LocateVex(MGraph G, VexType vex)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vexs[i] == vex)
			return i;
	}
	return -1;
}

void CreateUDN(MGraph& G,fstream &fp)//wu向图 
{
	int vexnum, arcnum;
	VexType start, end;
	int weight;
	fp >> vexnum >> arcnum;
	G.vexnum = vexnum;
	G.arcnum = arcnum;
	for (int i = 0; i < vexnum; i++)
	{
		fp >> G.vexs[i];
	}
	for (int i = 0; i < vexnum; i++)
	{
		for (int j = 0; j < vexnum; j++)
		{
			G.arcs[i][j].adj = INT_MAX;
			G.arcs[i][j].weight = 0;
		}
	}
	for (int i = 0; i < G.arcnum; i++)
	{
		fp >> start >> end >> weight;
		G.arcs[LocateVex(G, start)][LocateVex(G, end)].adj = 0;
		G.arcs[LocateVex(G, start)][LocateVex(G, end)].weight = weight;
		G.arcs[LocateVex(G, end)][LocateVex(G, start)].adj = 0;
		G.arcs[LocateVex(G, end)][LocateVex(G, start)].weight = weight;
	}
}

void CreateMGraph(MGraph& G,fstream &fp)
{
	CreateUDN(G,fp);
}

void Prim(MGraph G, VexType v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		Pr[i].flag = false;
		Pr[LocateVex(G, v)].flag = true;
		if (G.arcs[LocateVex(G, v)][i].adj == 0)
			Pr[i].distance = G.arcs[LocateVex(G, v)][i].weight;
		else if (i == LocateVex(G, v))
			Pr[i].distance = 0;
		else
			Pr[i].distance = INT_MAX;
		Pr[i].vex = v;
	}
	while (1)
	{
		int sum = 0;
		int minnposition;
		float minn = INT_MAX;
		for (int i = 0; i < G.vexnum; i++)
		{
			if (Pr[i].flag == true)
				continue;
			if (minn >= Pr[i].distance)
			{
				minnposition = i;
				minn = Pr[i].distance;
			}
		}
		Pr[minnposition].flag = true;
		v = G.vexs[minnposition];//找到最短的distance 
		for (int i = 0; i < G.vexnum; i++)
		{
			if (Pr[i].flag == true)//已经遍历的点不在遍历 
				continue;
			if (G.arcs[LocateVex(G, v)][i].adj == 0)
			{
				if (G.arcs[LocateVex(G, v)][i].weight < Pr[i].distance)
				{
					Pr[i].vex = v;
					Pr[i].distance = G.arcs[LocateVex(G, v)][i].weight;
				}
			}
		}
		for (int i = 0; i < G.vexnum; i++)
		{
			if (Pr[i].flag == true)
				sum++;
		}
		if (sum == G.vexnum)
			break;
	}
}

void showPrim(MGraph G)
{
	float sum = 0;
	for (int i = 0; i < G.vexnum; i++)
	{
		sum += Pr[i].distance;
		if (Pr[i].distance == 0)
			continue;
		else
			cout << G.vexs[i] << "与" << Pr[i].vex << "相连\n";
	}
	cout << "总距离：" << sum << endl;
}

struct Edge {
	int start;
	int end;
	float weight;
}E[100001];
int N, M;
int parent[10001];
bool cmp(Edge a, Edge b)
{
	return a.weight < b.weight;
}

int finda(int x)
{
	if (parent[x] == x)
		return x;
	else
		return finda(parent[x]);
}

float kruskal()
{
	float ans = 0;
	int t = 0;
	for (int i = 1; i <= M; i++)
	{
		int t1 = finda(E[i].start);
		int t2 = finda(E[i].end);
		if (t1 == t2)
			continue;
		else if (t1 != t2)
		{
			t++;
			ans += E[i].weight;
			parent[t1] = parent[t2];
		}
	}
	if (t < N - 1)
		return 0;
	return ans;
}

int main()
{
	fstream fp;
	fp.open("3.txt", ios::in);
	char name;
	fp >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		parent[i] = i;
	}
	for (int i = 1; i <= N; i++)
	{
		fp >> name;
		staname.push_back(name);
	}
	for (int i = 1; i <= M; i++)
	{
		fp >> E[i].start >> E[i].end >> E[i].weight;
	}
	sort(E + 1, E + M + 1, cmp);
	float ans=kruskal();
	for (int i = 1; i <= N; i++)
	{
		if (i == parent[i])
			continue;
		cout << staname[i-1] << "与" << staname[parent[i]-1] <<"相连"<< endl;
	}
	cout << "总距离：" << ans << endl;
	fp.close();
	fp.open("3.txt", ios::in);
	MGraph G;
	CreateMGraph(G, fp);
	Prim(G, 1);
	showPrim(G);
	fp.close();
}