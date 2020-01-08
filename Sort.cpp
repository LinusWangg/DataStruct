#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<queue>
#include<ctime>
#define Listsize 50001
#define increment 10
#define RADIX 10
#define MAX_SPACE 10000
using namespace std;
typedef struct LNode {
	int* elem;
	int listsize;
	int length;
}List;
typedef struct lnode {
	int data;
	lnode* next;
}lnode,*list;
int Initlist(list& l)
{
	l = (lnode*)malloc(sizeof(struct lnode));
	if (!l)
		return 0;
	l->data = 0;
	l->next = NULL;
	return 1;
}

int insert(list& l, int data)
{
	lnode *temp = l;
	lnode* p = (lnode*)malloc(sizeof(struct lnode));
	while (temp->next)
	{
		temp = temp->next;
	}
	p->data = data;
	p->next = NULL;
	temp->next = p;
	l->data++;
	return 1;
}

int Delete(list& l, int& data)
{
	if (l->next == NULL)
		return 0;
	lnode* temp = l->next;
	l->next = temp->next;
	data = temp->data;
	l->data--;
	return 1;
}

int freelist(list& l)
{
	int i;
	while (l->data != 0)
		Delete(l, i);
	return 1;
}
list e[10], f[10];
int Keynum(int data, int n)
{
	int j = 1;
	while (n--)
	{
		j *= 10;
	}
	data = data % j;
	data = data / (j / 10);
	return data;
}

int Set(list& e, list& f, int data)
{
	lnode* p = (lnode*)malloc(sizeof(struct lnode));
	lnode* temp;
	p->data = data;
	p->next = NULL;
	if (f->next == NULL)
	{
		f->next = p;
		e->next = p;
		f->data++;
		e->data++;
		return 1;
	}
	else if (f->next != NULL)
	{
		e->next->next = p;
		e->next = p;
		f->data++;
		e->data++;
	}
	return 1;
}
clock_t a, b;
time_t temp = 0;
int Select(list& l, int k)
{
	int data;
	Delete(l, data);
	a = clock();
	int key = Keynum(data, k);
	Set(e[key], f[key], data);
	b = clock();
	temp += b - a;
	return 1;
}

int rel(list& l)
{
	lnode *temp = l;
	for (int i = 0; i <= 9; i++)
	{
		temp->next = f[i]->next;
		f[i]->next = NULL;
		e[i]->next = NULL;
		while (temp->next)
		{
			temp = temp->next;
		}
	}
	return 1;
}

void Traver(list l)
{
	lnode* temp = l->next;
	while (temp)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}

void RadixSort(list& l,int dk)
{
	int length = l->data;
	for (int i = 1; i <= dk; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			f[j]->data = 0;
			e[j]->data = 0;
		}
		while (l->data != 0)
		{
			Select(l, i);
		}
		rel(l);
		l->data = length;
	}
}
//以上均为基数排序

int InitList(List& L)
{
	L.elem = (int*)malloc(sizeof(int)*Listsize);
	if (!L.elem)
		exit(0);
	L.listsize = Listsize;
	L.length = 0;
	return 1;
}

void freelist(List& L)
{
	delete L.elem;
	L.elem = NULL;
	L.length = 0;
}

int Insert(List& L,int e,int i)
{
	if (L.elem == NULL)
		cout << "No exist the list!" << endl;
	else if (i<1 || i>L.length + 1) {
		cout << "Cannot be inserted!" << endl;
	}
	else {
		if (L.length >= L.listsize)
		{
			int* newbase = (int*)realloc(L.elem, (L.listsize + increment) * sizeof(int));
			if (!newbase)
				exit(0);
			L.elem = newbase;
			L.listsize += increment;
		}
		int j;
		for (j = L.length; j > i; j--)
		{
			L.elem[j + 1] = L.elem[j];
		}
		L.elem[i - 1] = e;
		L.length++;
	}
	return 1;
}

void Traverse(List L)
{
	for (int i = 0; i < L.length; i++)
		cout << L.elem[i] << " ";
	cout << endl;
}

void InsertSort(List& L)
{
	int temp,j;
	for (int i = 1; i < L.length; i++)
	{
		if (L.elem[i] < L.elem[i - 1])
		{
			temp = L.elem[i];
			L.elem[i] = L.elem[i - 1];
			for (j = i - 2; temp < L.elem[j]; j--)
			{
				L.elem[j + 1] = L.elem[j];
			}
			L.elem[j + 1] = temp;
		}
	}
}

void ShellInsert(List& L,int dk)
{
	int temp, j;
	for (int i = dk; i < L.length; i++)
	{
		if (L.elem[i] < L.elem[i - dk])
		{
			temp = L.elem[i];
			L.elem[i] = L.elem[i - dk];
			for (j = i - dk; j >= 0 && (temp < L.elem[j]); j -= dk)
				L.elem[j + dk] = L.elem[j];
			L.elem[j + dk] = temp;
		}
	}
}

void ShellSort(List& L,int n)
{
	int num = n,t=0,dlta=1,temp;
	while (num != 0)
	{
		t++;
		num /= 2;
	}
	temp = t + 1;
	t--;
	while (t)
	{
		dlta *= 2;
		t--;
	}
	dlta *= 2;
	for (int k = 0; k < temp; k++)
	{
		dlta /= 2;
		ShellInsert(L, dlta + 1);
	}
}

void BubbleSort(List& L)
{
	for (int i = 0; i < L.length; i++)
	{
		for (int j = 0; j < L.length-1; j++)
		{
			if (L.elem[j] > L.elem[j + 1])
			{
				int temp = L.elem[j];
				L.elem[j] = L.elem[j + 1];
				L.elem[j + 1] = temp;
			}
		}
	}
}

int PartSort(List& L, int low, int high)
{
	int temp;
	temp = L.elem[low];
	int i = low, j = high;
	while (i < j)
	{
		while (i < j && L.elem[j] >= temp)
			j--;
		L.elem[i] = L.elem[j];
		while (i < j && L.elem[i] <= temp)
			i++;
		L.elem[j] = L.elem[i];
	}
	L.elem[i] = temp;
	return i;
}

void QuickSort(List& L,int low,int high)
{
	queue<int> part;
	int mid = PartSort(L, 0, L.length - 1);
	part.push(0);
	part.push(mid-1);
	part.push(mid + 1);
	part.push(L.length - 1);
	while (!part.empty())
	{
		int start = part.front();
		part.pop();
		int end = part.front();
		part.pop();
		if (start == end||end<start)
			continue;
		mid = PartSort(L, start, end);
		part.push(start);
		part.push(mid - 1);
		part.push(mid + 1);
		part.push(end);
	}
}

void SelectSort(List& L)
{
	int minposition, minn;
	for (int i = 0; i < L.length; i++)
	{
		minn = L.elem[i];
		minposition = i;
		for (int j = i; j < L.length; j++)
		{
			if (L.elem[j] < minn)
			{
				minn = L.elem[j];
				minposition = j;
			}
		}
		if (minposition != i)
		{
			int temp = L.elem[i];
			L.elem[i] = L.elem[minposition];
			L.elem[minposition] = temp;
		}
	}
}

void HeapAdjust(List& L, int s, int m)
{
	int temp = L.elem[s];
	for (int j = 2 * s+1; j <= m; j =2*j+1)
	{
		if (j < m && L.elem[j] < L.elem[j + 1])
			j++;
		if (temp > L.elem[j])
			break;
		L.elem[s] = L.elem[j];
		s = j;
	}
	L.elem[s] = temp;
}

void HeapSort(List& L)
{
	for (int i = (L.length - 1) / 2; i >= 0; i--)
		HeapAdjust(L, i, L.length - 1);
	for (int i = L.length - 1; i >= 1; i--)
	{
		int temp = L.elem[0];
		L.elem[0] = L.elem[i];
		L.elem[i] = temp;
		HeapAdjust(L, 0, i - 1);
	}
}
int level = 0;
void Merge(List L, List& L1, int i, int m, int n)
{
	int k = i, j = m + 1, t = i;
	if (i == L.length - 1)
	{
		L1.elem[i] = L.elem[i];
	}
	else
	{
		while (t <= m && j <= n)
		{
			if (L.elem[t] < L.elem[j])
			{
				L1.elem[k] = L.elem[t];
				t++;
				k++;
			}
			else
			{
				L1.elem[k] = L.elem[j];
				k++;
				j++;
			}
		}
		while (t <= m)
		{
			L1.elem[k] = L.elem[t];
			t++;
			k++;
		}
		while (j <= n)
		{
			L1.elem[k] = L.elem[j];
			j++;
			k++;
		}
	}
}

void MSort(List& L, List& L1)
{
	int n = 1;
	level = 0;
	while (n < L.length)
	{
		int t = 0, s = 0, m = 0;
		while (t < L.length)
		{
			m = t + n - 1;
			s = m + n;
			if (m > L.length - 1)
			{
				m = L.length - 2;
			}
			if (s > L.length - 1)
			{
				s = L.length - 1;
			}
			if (s - L.length + 1 <= n && s - L.length + 1 > 0)
			{
				s = L.length - 1;
			}
			if (level % 2 == 0)
			{
				Merge(L, L1, t, m, s);
			}
			else
			{
				Merge(L1, L, t, m, s);
			}
			t = s + 1;
		}
		n *= 2;
		level++;
	}
}

void RadixUse(fstream &fp)
{
	int max = -10000;
	list l;
	Initlist(l);
	for (int i = 0; i <= 9; i++)
	{
		Initlist(f[i]);
		Initlist(e[i]);
	}
	int n, data;
	fp >> n;
	for (int i = 1; i <= n; i++)
	{
		fp >> data;
		if (data > max)
			max = data;
		insert(l, data);
	}
	int j = 0;
	while (max)
	{
		j++;
		max /= 10;
	}
	clock_t startTime, endTime;
	startTime = clock();//计时开始
	RadixSort(l, j);
	endTime = clock();
	cout << "The run time is: " << (double)(endTime - startTime - temp) / CLOCKS_PER_SEC << "s" << endl;
	temp = 0;
	//Traver(l);
	delete l;
}
List L, L1;
void InsertUse(fstream& fp)
{
	int n,data;
	fp >> n;
	InitList(L);
	for (int i = 1; i <= n; i++)
	{
		fp >> data;
		Insert(L, data, i);
	}
	clock_t startTime, endTime;
	startTime = clock();//计时开始
	InsertSort(L);
	endTime = clock();
	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	//Traverse(L);
	freelist(L);
}

void ShellUse(fstream& fp)
{
	int n, data;
	fp >> n;
	InitList(L);
	for (int i = 1; i <= n; i++)
	{
		fp >> data;
		Insert(L, data, i);
	}
	clock_t startTime, endTime;
	startTime = clock();//计时开始
	ShellSort(L,n);
	endTime = clock();
	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	//freelist(L);
	freelist(L);
}

void BubbleUse(fstream& fp)
{
	int n, data;
	fp >> n;
	InitList(L);
	for (int i = 1; i <= n; i++)
	{
		fp >> data;
		Insert(L, data, i);
	}
	clock_t startTime, endTime;
	startTime = clock();//计时开始
	BubbleSort(L);
	endTime = clock();
	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	//Traverse(L);
	freelist(L);
}

void QuickUse(fstream& fp)
{
	int n, data;
	fp >> n;
	InitList(L);
	for (int i = 1; i <= n; i++)
	{
		fp >> data;
		Insert(L, data, i);
	}
	clock_t startTime, endTime;
	startTime = clock();//计时开始
	QuickSort(L,0,n-1);
	endTime = clock();
	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	//Traverse(L);
	freelist(L);
}

void SelectUse(fstream& fp)
{
	int n, data;
	fp >> n;
	InitList(L);
	for (int i = 1; i <= n; i++)
	{
		fp >> data;
		Insert(L, data, i);
	}
	clock_t startTime, endTime;
	startTime = clock();//计时开始
	SelectSort(L);
	endTime = clock();
	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	//Traverse(L);
	freelist(L);
}

void HeapUse(fstream& fp)
{
	int n, data;
	fp >> n;
	InitList(L);
	for (int i = 1; i <= n; i++)
	{
		fp >> data;
		Insert(L, data, i);
	}
	clock_t startTime, endTime;
	startTime = clock();//计时开始
	HeapSort(L);
	endTime = clock();
	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	//Traverse(L);
	freelist(L);
}

void MergeUse(fstream& fp)
{
	InitList(L);
	InitList(L1);
	int n, data;
	fp >> n;
	L1.length = n;
	for (int i = 1; i <= n; i++)
	{
		fp >> data;
		Insert(L, data, i);
	}
	clock_t startTime, endTime;
	startTime = clock();//计时开始
	MSort(L,L1);
	endTime = clock();
	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	/*if (level % 2 == 0)
		Traverse(L);
	else
		Traverse(L1);*/
	freelist(L);
	freelist(L1);
}

int main()
{
	fstream fp;
	while (1)
	{
		string file;
		cin >> file;
		if (file == "#")
		{
			break;
		}
		cout << "1.基数 2.插入 3.希尔 4.冒泡 5.快速 6.选择 7.堆排 8.归并" << endl;
		fp.open(file, ios::in);
		RadixUse(fp);
		fp.close();
		fp.open(file, ios::in);
		InsertUse(fp);
		fp.close();
		fp.open(file, ios::in);
		ShellUse(fp);
		fp.close();
		fp.open(file, ios::in);
		BubbleUse(fp);
		fp.close();
		fp.open(file, ios::in);
		QuickUse(fp);
		fp.close();
		fp.open(file, ios::in);
		SelectUse(fp);
		fp.close();
		fp.open(file, ios::in);
		HeapUse(fp);
		fp.close();
		fp.open(file, ios::in);
		MergeUse(fp);
		fp.close();
	}
}
