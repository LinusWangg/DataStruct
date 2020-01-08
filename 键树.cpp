#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<queue>
#include<fstream>
#include<stack>
#include<map>
#include<vector>
#include<iomanip>
using namespace std;
typedef struct CSNode {
	char data;
	struct CSNode* firstchild, * nextsilbing;
}CSNode, * CSTree;
map<string, string> mp;
int InitCSTree(CSTree& T)
{
	T = (CSNode*)malloc(sizeof(struct CSNode));
	T->data = '#';
	T->firstchild = NULL;
	T->nextsilbing = NULL;
	return 1;
}

int InsertString(CSTree& T, string a)
{
	CSNode* child, * silb;
	CSNode* temp = (CSNode*)malloc(sizeof(struct CSNode));
	if (T == NULL)
	{
		InitCSTree(T);
		child = T;
		InitCSTree(child->firstchild);
		child = child->firstchild;
		for (int i = 0; i < a.size(); i++)
		{
			child->data = a[i];
			InitCSTree(child->firstchild);
			child = child->firstchild;
		}
		child->data = '$';
		return 1;
	}
	else
	{
		temp = T->firstchild;
		int pos = 0, flag = 0;
		while (temp)
		{
			if (temp->data == a[pos])
			{
				flag = 0;
				if (!temp->firstchild)
					break;
				temp = temp->firstchild;
				pos++;
				continue;
			}
			else
			{
				if (pos >= a.size())
					break;
				if (temp->data != a[pos])
					flag = 1;
				if (temp->nextsilbing == NULL)
					break;
			}
			temp = temp->nextsilbing;
		}
		if (pos >= a.size())
		{
			silb = (CSNode*)malloc(sizeof(CSNode));
			silb->data = '$';
			silb->firstchild = NULL;
			temp->nextsilbing = silb;
			silb->nextsilbing = NULL;
			return 1;
		}
		if (!temp->nextsilbing && flag == 1)
		{
			silb = (CSNode*)malloc(sizeof(CSNode));
			silb->data = a[pos];
			silb->nextsilbing = NULL;
			temp->nextsilbing = silb;
			InitCSTree(silb->firstchild);
			silb = silb->firstchild;
			for (int i = pos + 1; i < a.size(); i++)
			{
				silb->data = a[i];
				InitCSTree(silb->firstchild);
				silb = silb->firstchild;
			}
			silb->data = '$';
		}
		if (flag == 0)
		{
			if (pos == a.size())
				cout << "该单词已存在" << endl;
			else
			{
				for (int i = pos + 1; i < a.size(); i++)
				{
					InitCSTree(temp->firstchild);
					temp = temp->firstchild;
					temp->data = a[i];
				}
				InitCSTree(temp->firstchild);
				temp = temp->firstchild;
				temp->data = '$';
			}
		}
	}
}

int DeleteString(CSTree& T, string a)
{
	stack<CSNode*> ss;
	CSNode* temp = T;
	CSNode* temp2 = (CSNode*)malloc(sizeof(CSNode));
	CSNode* temp3 = (CSNode*)malloc(sizeof(CSNode));
	if (T == NULL)
	{
		cout << "字典不存在" << endl;
		return 0;
	}
	ss.push(T);
	temp = T->firstchild;
	int pos = 0, flag = 0;
	while (temp)
	{
		if (temp->data == a[pos])
		{
			flag = 0;
			if (!temp->firstchild)
				break;
			ss.push(temp);
			temp = temp->firstchild;
			pos++;
			continue;
		}
		temp = temp->nextsilbing;
	}
	int i = 0;
	while (ss.size() != 1)
	{
		temp2 = ss.top();
		ss.pop();
		temp3 = ss.top();
		if (temp2->firstchild && i == 0)
		{
			CSNode* temp4 = (CSNode*)malloc(sizeof(CSNode));
			temp4 = temp2->firstchild;
			if (temp4->data == '$')
			{
				temp2->firstchild = temp4->nextsilbing;
			}
			else
			{
				while (temp4->nextsilbing->data != '$')
					temp4 = temp4->nextsilbing;
				CSNode* temp5 = temp4->nextsilbing;
				temp4->nextsilbing = temp5->nextsilbing;
				free(temp5);
			}
			i++;
			return 1;
		}
		CSNode* temp4 = (CSNode*)malloc(sizeof(CSNode));
		temp4 = temp3->firstchild;
		if (temp4 == temp2)
		{
			temp3->firstchild = temp2->nextsilbing;
			temp2 = NULL;
			continue;
		}
		while (temp4->nextsilbing != temp2)
		{
			temp4 = temp4->nextsilbing;
		}
		temp4->nextsilbing = temp2->nextsilbing;
		temp2 = NULL;
		i++;
	}
	return 1;
}

struct cmp {
	bool operator()(string x, string y)
	{
		return x > y;
	}
};
priority_queue<string,vector<string>,cmp> s;
stack<CSNode*> n;
void Traverse(CSTree T)
{
	string temp;
	CSNode* t = T;
	t = t->firstchild;
	while (t || !n.empty())
	{
		while (t)
		{
			if (t->data == '$')
			{
				n.push(t);
				temp.push_back(t->data);
				s.push(temp);
				t = t->firstchild;
			}
			if (t == NULL)
				break;
			temp.push_back(t->data);
			n.push(t);
			t = t->firstchild;
			if (t == NULL)
				break;
			if (t->data == '$')
			{
				n.push(t);
				temp.push_back(t->data);
				s.push(temp);
				t = t->firstchild;
			}
		}
		if (!s.empty())
		{
			t = n.top();
			n.pop();
			t = t->nextsilbing;
			temp.pop_back();
		}
	}
	while (!s.empty())
	{
		string out = s.top();
		s.pop();
		out.pop_back();
		cout << setw(15) << left << out << setw(15) << left << mp[out] << endl;
	}
	while (!s.empty())
		s.pop();
	while (!n.empty())
		n.pop();
}

void Search(CSTree T, string a)
{
	string temp;
	CSNode* t = T;
	t = t->firstchild;
	while (t || !n.empty())
	{
		while (t)
		{
			if (t->data == '$')
			{
				n.push(t);
				temp.push_back(t->data);
				s.push(temp);
				t = t->firstchild;
			}
			if (t == NULL)
				break;
			temp.push_back(t->data);
			n.push(t);
			t = t->firstchild;
			if (t == NULL)
				break;
			if (t->data == '$')
			{
				n.push(t);
				temp.push_back(t->data);
				s.push(temp);
				t = t->firstchild;
			}
		}
		if (!s.empty())
		{
			t = n.top();
			n.pop();
			t = t->nextsilbing;
			temp.pop_back();
		}
	}
	while (!s.empty())
	{
		string out = s.top();
		s.pop();
		out.pop_back();
		string::size_type idx;
		idx = out.find(a);
		if (idx == string::npos)
			continue;
		else
			cout << setw(15) <<left<< out << setw(15) <<left<< mp[out] << endl;
	}
	while (!s.empty())
		s.pop();
	while (!n.empty())
		n.pop();
}

void CreateCSTree(CSTree& T)
{
	fstream fp;
	fp.open("1.txt", ios::in);
	while (!fp.eof())
	{
		string temp,trans;
		fp >> temp>>trans;
		int flag = 0;
		map<string, string>::iterator it;
		it = mp.begin();
		while (it != mp.end())
		{
			if (it->first == temp)
			{
				flag = 1;
				break;
			}
			it++;
		}
		if (flag == 1)
			continue;
		else
			InsertString(T, temp);
		mp.insert({ temp,trans });
	}
	fp.close();
}

void modify(CSTree& T, string a, string b)
{
	DeleteString(T, a);
	InsertString(T, b);
}

int exist(string a)
{
	map<string, string>::iterator it=mp.begin();
	while (it != mp.end())
	{
		if (it->first == a)
		{
			return 0;
		}
		it++;
	}
	return 1;
}

void menu(CSTree& T)
{
	while (1)
	{
		string a,trans;
		cout << "1.插入元素 " << "2.删除元素 " << "3.退出 " << "4.模糊查找 " << "5.查看字典 " <<"6.修改单词"<< endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			cout << "输入添加单词和翻译" << endl;
			cin >> a >> trans;
			if (exist(a) == 0)
			{
				cout << "该单词已存在" << endl;
			}
			else
			{
				InsertString(T, a);
				mp.insert({ a,trans });
			}
		}
		else if (choice == 2)
		{
			cout << "输入删除元素" << endl;
			cin >> a;
			if (exist(a) == 0)
			{
				DeleteString(T, a);
				mp.erase(a);
			}
			else
			{
				cout << "该单词不存在" << endl;
			}
		}
		else if (choice == 3)
		{
			break;
		}
		else if (choice == 4)
		{
			cout << "输入字符串" << endl;
			cin >> a;
			Search(T, a);
		}
		else if (choice == 5)
		{
			Traverse(T);
		}
		else if (choice == 6)
		{
			cout << "输入你要修改的单词和修改后的单词以及翻译" << endl;
			string mod, after;
			cin >> mod >> after >> trans;
			if (exist(mod) == 0)
			{
				modify(T, mod, after);
				mp.erase(mod);
				mp.insert({ after, trans });
			}
			else
			{
				cout << "该单词不存在" << endl;
			}
		}
	}
}

int main()
{
	CSTree T;
	T = NULL;
	CreateCSTree(T);
	menu(T);
}