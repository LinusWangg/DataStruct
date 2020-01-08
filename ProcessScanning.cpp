#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<iomanip>
#include<cstring>
#include <windows.h>
#define Ok 1
#define Error 0
using namespace std;
vector<char*> vl;
class task {
public:
	char name[128];
	int memory;
	SYSTEMTIME start;
	SYSTEMTIME end;
	double time;
	task(char* t) : memory(0)
	{
		char* b = t + 1, *p = t + 1;
		while (*p) {
			if (*p == '"')
			{
				*p = 0;
				strcpy_s(name,128, b);
				break;
			}
			p++;
		}
		for (b = p + 1; p[1] != 'K'; p++)
			if (*p == '"')
				b = p;
		for (char* c = b + 1; c != p; c++)
			if (*c == ',')
				continue;
			else
				memory = 10 * memory + *c - '0';

	}
	bool operator<(task& t) { return this->memory < t.memory; }
};

typedef struct DLNode {
	task run;
	struct DLNode* prior, * next;
}DLNode, * DLinkList;

typedef struct LNode {
	task end;
	struct LNode* next;
}LNode, * LinkList;

int InitDList(DLinkList& L)
{
	L = (DLNode*)malloc(sizeof(struct DLNode));
	if (!L)
		return Error;
	L->next = NULL;
	L->prior = NULL;
	return Ok;
}

int InitList(LinkList& L)
{
	L = (LNode*)malloc(sizeof(struct LNode));
	if (!L)
		return Error;
	L->next = NULL;
	return 1;
}

int ClearDList(DLinkList& L)
{
	free(L->next);
	L->next = NULL;
	return 1;
}

int ClearList(LinkList& L)
{
	free(L->next);
	L->next = NULL;
	return 1;
}

int insertDList(DLinkList& L, DLNode* p)
{
	DLNode* temp = L->next, * temp2 = L->next;
	if (!temp)
	{
		L->next = p;
		p->prior = L;
		return Ok;
	}
	while (temp)
	{
		if (temp->run.memory >= p->run.memory)
			temp = temp->next;
		else
			break;
	}
	if (!temp)
	{
		while (temp2->next != NULL)
			temp2 = temp2->next;
		temp2->next = p;
		p->prior = temp2;
		return Ok;
	}
	temp->prior->next = p;
	p->next = temp;
	p->prior = temp->prior;
	temp->prior = p;
	return Ok;
}

int insertList(LinkList& L, LNode* p)
{
	LNode* temp = L->next, * temp2=L;
	if (L->next == NULL)
	{
		L->next = p;
		return 1;
	}
	while (temp)
	{
		if (temp->end.end.wHour > p->end.end.wHour || (temp->end.end.wHour == p->end.start.wHour && temp->end.end.wMinute > p->end.end.wMinute) || (temp->end.end.wHour == p->end.end.wHour && temp->end.end.wMinute == p->end.end.wMinute && temp->end.end.wSecond > p->end.end.wMinute))
			temp = temp->next;
		else
			break;
	}
	if (temp == NULL)
	{
		while (temp2->next != NULL)
			temp2 = temp2->next;
		temp2->next = p;
		return 1;
	}
	while (temp2->next != temp)
		temp2 = temp2->next;
	temp2->next = p;
	p->next = temp;
	return 1;
}

void TraverseDList(DLinkList L)
{
	DLNode* temp = L->next;
	cout << setw(70) << left << "��������";
	cout << setw(15) << left << "�ڴ����";
	cout << setw(10) << left << "����ʱ��" << endl;
	cout << "===================================================================================================" << endl;
	while (temp)
	{
		cout << setw(70) << left << temp->run.name;
		cout << setw(15) << left << temp->run.memory;
		cout << setw(10) << left << (double)temp->run.time << "s" << endl;
		temp = temp->next;
	}
}

void TraverseList(LinkList L)
{
	LNode* temp = L->next;
	cout << setw(70) << left << "��������";
	cout << setw(15) << left << "�ڴ����";
	cout << setw(10) << left << "����ʱ��" << endl;
	cout << "=======================================================================================================" << endl;
	while (temp)
	{
		cout << setw(70) << left << temp->end.name;
		cout << setw(15) << left << temp->end.memory;
		cout << left << temp->end.start.wHour << "h" << temp->end.start.wMinute << "min" << temp->end.start.wSecond << "s" << endl;
		temp = temp->next;
	}
}

int showpresent(DLinkList& L, DLinkList LL, LinkList& Lt)//��ʾ��ǰ���� 
{
	int flag = 0;
	char buffer[128], cmd[] = "tasklist /FO CSV";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe)
		return Error;
	fgets(buffer, 128, pipe);
	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe))
		{
			flag = 0;
			DLNode* p = (DLNode*)malloc(sizeof(struct DLNode));
			DLNode* temp;
			temp = LL->next;
			p->run = task(buffer);
			p->next = NULL;
			p->prior = NULL;
			GetLocalTime(&p->run.start);
			while (temp)
			{
				if (strcmp(temp->run.name, p->run.name) == 0)
				{
					flag = 1;
					p->run.time = (p->run.start.wMinute - temp->run.start.wMinute) * 60.0 + (p->run.start.wSecond - temp->run.start.wSecond) * 1.0 + (p->run.start.wMilliseconds - temp->run.start.wMilliseconds) * 0.001;
					break;
				}
				temp = temp->next;
			}
			if (flag == 0)
				p->run.time = 0;
			insertDList(L, p);
		}
	}
	_pclose(pipe);
	TraverseDList(L);
}

int showend(LinkList& L, DLinkList LL, DLinkList Lt)//��ʾ�������� 
{
	int i = 0;
	int flag = 0;
	DLNode* temp = LL->next, * temp2 = Lt->next;
	vector<char*> vnow;
	while (temp2)
	{
		vnow.push_back(temp2->run.name);
		temp2 = temp2->next;
	}
	while (temp)
	{
		int flag = 0;
		vector<char*>::iterator iter;
		iter = vnow.begin();
		while (iter != vnow.end())//LL��Lt���Ҳ���
		{
			if (strcmp(*iter, temp->run.name) == 0)
			{
				flag = 1;
				break;
			}
			iter++;
		}
		if (flag == 0)
		{
			LNode* s = (LNode*)malloc(sizeof(struct LNode));
			strcpy_s(s->end.name,128, temp->run.name);
			s->end.memory = temp->run.memory;
			s->end.start = temp->run.start;
			s->next = NULL;
			SYSTEMTIME now;
			GetLocalTime(&now);
			GetLocalTime(&s->end.end);
			s->end.time = (now.wMinute - s->end.start.wMinute) * 60.0 + (now.wSecond - s->end.start.wSecond) * 1.0 + (now.wMilliseconds - s->end.start.wMilliseconds) * 0.001;
			s->end.start = now;
			insertList(L, s);
			vl.push_back(s->end.name);
		}
		temp = temp->next;
	}
	TraverseList(L);
	return 1;
}

int InitLL(DLinkList& L)//��׼�� 
{
	char buffer[128], cmd[] = "tasklist /FO CSV";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe)
		return Error;
	fgets(buffer, 128, pipe);
	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe))
		{
			DLNode* p = (DLNode*)malloc(sizeof(struct DLNode));
			p->run = task(buffer);
			p->next = NULL;
			p->prior = NULL;
			GetLocalTime(&p->run.start);
			insertDList(L, p);
		}
	}
	_pclose(pipe);
}

int circuit(LinkList& L, DLinkList L1)//����presentɾ���������� 
{
	DLNode* temp = L1->next;
	while (temp)
	{
		vector<char*>::iterator iter;
		iter = vl.begin();
		while (iter != vl.end())
		{
			if (strcmp(*iter, temp->run.name) == 0)
			{
				LNode* temp3 = L->next;
				while (strcmp(*iter, temp3->end.name) != 0)
				{
					temp3 = temp3->next;
				}
				LNode* temp2 = L;
				while (temp2->next != temp3)
				{
					temp2 = temp2->next;
				}
				temp2->next = temp3->next;
				vl.erase(iter);
				break;
			}
			iter++;
		}
		temp = temp->next;
	}
	return 1;
}

int circuitll(DLinkList& pre, DLinkList now)//��������У���׼�� 
{
	vector<char*> prev;
	DLNode* temp = now->next, * temp2 = pre->next;
	while (temp2)
	{
		prev.push_back(temp2->run.name);
		temp2 = temp2->next;
	}
	temp = now->next, temp2 = pre->next;
	while (temp2)//Ѱ��now�в����ڵ�ɾ��
	{
		temp = now->next;
		int flag = 0;
		while (temp)
		{
			if (strcmp(temp->run.name, temp2->run.name) == 0)
			{
				flag = 1;
				break;
			}
			temp = temp->next;
		}
		if (flag == 0)
		{
			DLNode* temp3 = pre->next;
			while (temp3->next != temp2)
			{
				temp3 = temp3->next;
			}
			temp2 = temp2->next;
			temp2->prior = temp3;
			temp3->next = temp2;
			continue;
		}
		temp2 = temp2->next;
	}
	temp = now->next, temp2 = pre->next;
	while (temp)//now�д��ڵ�LL�����ڵ����
	{
		int flag = 0;
		vector<char*>::iterator it;
		it = prev.begin();
		while (it != prev.end())
		{
			if (strcmp(*it, temp->run.name) == 0)//LL�д��ڵ�
			{
				flag = 1;
				break;
			}
			it++;
		}
		if (flag == 0)
		{
			DLNode* s = (DLNode*)malloc(sizeof(struct DLNode));
			strcpy_s(s->run.name,128, temp->run.name);
			s->run.memory = temp->run.memory;
			s->run.start = temp->run.start;
			s->run.time = temp->run.time;
			insertDList(pre, s);
		}
		temp = temp->next;
	}
	return 1;
}

int main()
{
	DLinkList L, LL;//LL-pre,L-now��LLΪ��׼��
	LinkList L2;//L2-end
	InitDList(L);
	InitDList(LL);
	InitList(L2);
	InitLL(LL);
	long t = time(NULL);
	while (1)
	{
		ClearDList(L);
		showpresent(L, LL, L2);
		circuit(L2, L);
		showend(L2, LL, L);
		circuitll(LL, L);
		cin.ignore();
	}
}