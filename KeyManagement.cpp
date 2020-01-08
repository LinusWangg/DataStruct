#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<algorithm>
using namespace std;
struct key {
	int identity;
	int starttime;
	int endtime;
};

struct keyinfo {
	int identity;
	bool flag;
};

typedef struct QueueNode {
	key keymessage;
	struct QueueNode* next;
}QueueNode,*Queueptr;

typedef struct {
	Queueptr front;
	Queueptr rear;
	int length;
}LinkQueue;
key elem[1001];
keyinfo kp[1001];
int n, time, m;
int InitQueue(LinkQueue& Q)
{
	Q.front = Q.rear = (QueueNode*)malloc(sizeof(struct QueueNode));
	if (!Q.front || !Q.rear)
	{
		cout << "ÉêÇë¿Õ¼äÊ§°Ü£¡" << endl;
		return 0;
	}
	Q.front->next = NULL;
	Q.length = 0;
	return 1;
}

int EnQueue(LinkQueue& Q, key e)
{
	QueueNode* p = (QueueNode*)malloc(sizeof(struct QueueNode));
	if (!p)
	{
		cout << "¿Õ¼äÉêÇëÊ§°Ü" << endl;
		return 0;
	}
	p->keymessage = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	Q.length++;
	return 1;
}

int DeQueue(LinkQueue& Q, key& e)
{
	if (Q.rear == Q.front)
	{
		cout << "¶ÓÁÐÖÐ²»´æÔÚÔªËØ!" << endl;
		return 0;
	}
	QueueNode* p = (QueueNode*)malloc(sizeof(struct QueueNode));
	if (!p)
	{
		cout << "¿Õ¼äÉêÇëÊ§°Ü" << endl;
		return 0;
	}
	p = Q.front->next;
	e = p->keymessage;
	Q.front->next = p->next;
	if (Q.rear == p)
	{
		Q.rear = Q.front;
	}
	free(p);
	Q.length--;
	return 1;
}

int QueueTraverse(LinkQueue Q)
{
	if (Q.rear == Q.front)
	{
		cout << "¶ÓÁÐÖÐÎÞÔªËØ£¡" << endl;
		return 0;
	}
	QueueNode* p = (QueueNode*)malloc(sizeof(struct QueueNode));
	if (!p)
	{
		cout << "¿Õ¼äÉêÇëÊ§°Ü" << endl;
		return 0;
	}
	p = Q.front->next;
	while (p != NULL)
	{
		cout << p->keymessage.identity << " " << p->keymessage.starttime << " " << p->keymessage.endtime << endl;
		p = p->next;
	}
	return 1;
}

bool QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return true;
	return false;
}

bool cmp_starttime(const key &a,const key &b)
{
	if (a.starttime == b.starttime)
		return false;
	return a.starttime < b.starttime;
}

bool cmp_endtime(const key &a,const key &b)
{
	if (a.endtime == b.endtime)
	{
		if (a.identity < b.identity)
			return true;
		return false;
	}
	return a.endtime < b.endtime;
}

void Initkeyinfo()
{
	for (int i = 1; i <= n; i++)
	{
		kp[i].flag = true;
		kp[i].identity = i;
	}
}

void PutKey(key a)
{
	for (int i = 1; i <= n; i++)
	{
		if (kp[i].flag == false)
		{
			kp[i].identity = a.identity;
			kp[i].flag = true;
			i = n;
		}	
	}
}

void TakeKey(key a)
{
	for (int i = 1; i <= n; i++)
	{
		if (kp[i].identity == a.identity&&kp[i].flag==true)
		{
			kp[i].flag = false;
			i = n;
		}
	}
}

void Traversekey()
{
	for (int i = 1; i < n; i++)
	{
		cout << kp[i].identity << " ";
	}
	cout << kp[n].identity;
	cout << endl;
}

void keymanage(LinkQueue& take, LinkQueue& back)
{
	int temp = 0;
	key tk, bk;
	DeQueue(take, tk);
	DeQueue(back, bk);
	while ((!QueueEmpty(take) && !QueueEmpty(back))||temp==1)
	{
		if (tk.starttime < bk.endtime)
		{
			TakeKey(tk);
			if (take.length == 0)
				break;
			DeQueue(take, tk);
			if (take.length == 0)
				temp = 1;
		}
		else if (tk.starttime >= bk.endtime)
		{
			PutKey(bk);
			DeQueue(back, bk);
		}
	}
	temp = 0;
	while (!QueueEmpty(back)||temp==1)
	{
		PutKey(bk);
		if (temp == 1)
			break;
		DeQueue(back, bk);
		if (back.length == 0)
			temp = 1;
	}
}

int main()
{
	LinkQueue take,back;
	InitQueue(take);
	InitQueue(back);
	cin >> n>>m;
	Initkeyinfo();
	for(int i=1;i<=m;i++)
	{
		cin >> elem[i].identity >> elem[i].starttime >> time;
		elem[i].endtime = elem[i].starttime + time;
	}
	sort(elem+1, elem + m+1, cmp_starttime);
	for (int i = 1; i <= m; i++)
		EnQueue(take, elem[i]);
	sort(elem+1, elem + m+1, cmp_endtime);
	for (int i = 1; i <= m; i++)
		EnQueue(back, elem[i]);
	keymanage(take, back);
	Traversekey();
	return 0;
}