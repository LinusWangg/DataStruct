#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<stack>
#include<fstream>
#include<iomanip>
using namespace std;
struct people {
	char gender = 'f';
	char name[20]=" ";
	int born_year=0;
	int born_month=0;
	int born_day=0;
	bool marriage=0;
	char address[20]=" ";
	char couple[20]=" ";
	bool alive=1;
	int die_year=0;
	int die_month=0;
	int die_day=0;
};
typedef struct CSNode {
	people data;
	int number;
	struct CSNode* firstchild, * nextsibling;
}CSNode,*CSTree;
queue<CSNode*> cstree;
int InitCSTree(CSTree& T)
{
	T = (CSNode*)malloc(sizeof(struct CSNode));
	if (!T)
	{
		cout << "�ռ��ڴ�����ʧ�ܣ�" << endl;
		return 0;
	}
	T->number = 0;
	return 1;
}
CSNode* parent = (CSNode*)malloc(sizeof(struct CSNode));
CSNode* silding = (CSNode*)malloc(sizeof(struct CSNode));
CSNode* temp = (CSNode*)malloc(sizeof(struct CSNode));
void Createman(people& man)
{
	cout << "Plz Enter the name:";
	cin >> man.name;
	cout << "Plz Enter the gender:";
	cin >> man.gender;
	cout << "Plz Enter the birth:";
	cin >> man.born_year >> man.born_month >> man.born_day;
	cout << "Plz Enter the condition of marriage:";
	cin >> man.marriage;
	if (man.marriage == 1)
	{
		cout << "Plz Enter the couple name:";
		cin >> man.couple;
	}
	cout << "Plz Enter the address:";
	cin >> man.address;
	cout << "Plz Enter the condition of liveth;";
	cin >> man.alive;
	if (man.alive == 1)
	{
		man.die_year = 0;
		man.die_month = 0;
		man.die_day = 0;
	}
	else if (man.alive == 0)
	{
		cout << "Plz Enter the day of death:";
		cin >> man.die_year >> man.die_month >> man.die_day;
	}
}

void Createman(people& man,fstream &fp)
{
	fp >> man.name;
	fp >> man.gender;
	fp >> man.born_year >> man.born_month >> man.born_day;
	fp >> man.marriage;
	if (man.marriage == 1)
	{
		fp >> man.couple;
	}
	fp >> man.address;
	fp >> man.alive;
	if (man.alive == 1)
	{
		man.die_year = 0;
		man.die_month = 0;
		man.die_day = 0;
	}
	else if (man.alive == 0)
	{
		fp >> man.die_year >> man.die_month >> man.die_day;
	}
}

int Find(CSTree T, CSTree& parent, CSTree& silbing, char *name)//ֱ���Ҹ��׺��ֵܵĽڵ㶨λ�����Ҹо�������ĺ���
{
	int flag = 0;
	temp = T;
	parent = T;
	if (strcmp(temp->data.name,name)==0)
	{
		silbing = temp;
		return 1;
	}
	cstree.push(temp);
	while (!cstree.empty()&&flag==0)
	{
		temp = cstree.front();
		cstree.pop();
		if (temp->firstchild)
		{
			parent = temp;
			temp = temp->firstchild;
			while (temp)
			{
				if (strcmp(temp->data.name, name) == 0)
				{
					flag = 1;
					silbing = temp;
					break;
				}
				cstree.push(temp);
				temp = temp->nextsibling;
			}
		}
	}
	while (!cstree.empty())
	{
		cstree.pop();
	}
	return flag;
}

void Showman(people man)
{
	cout << "������" << man.name << " ";
	cout << "�������£�" << man.born_year << "��" << man.born_month << "��" << man.born_day << "�� ";
	if (man.marriage == 1)
	{
		if (man.gender == 'f')
		{
			cout << "�ɷ�" << man.couple<<" ";
		}
		else
		{
			cout << "���ӣ�" << man.couple<<" ";
		}
	}
	else if (man.marriage == 0)
	{
		cout << "��δ��顣 ";
	}
	cout << "��ַ��" << man.address << endl;
}

int Insertman(CSTree& T)
{
	char name[20],relation[20];
	people man;
	cout << "��������ֱϵ���������ϵ(����ǵ�һ�˾�������):";
	cin >> name >> relation;
	if (strcmp(relation, "����") == 0)
	{
		if (T->number==0)
		{
			Createman(man);
			T->data = man;
			T->firstchild = NULL;
			T->nextsibling = NULL;
			T->number++;
			return 1;
		}
		else if (T->number != 0)
		{
			Createman(man);
			CSNode* p = (CSNode*)malloc(sizeof(struct CSNode));
			if (p == NULL)
			{
				cout << "����ʧ�ܣ�" << endl;
				return -1;
			}
			p->data = man;
			p->nextsibling = NULL;
			p->firstchild = T;
			T = p;
			T->number++;
			return 1;
		}
	}
	else if (strcmp(relation, "���") == 0 || strcmp(relation, "�ܵ�") == 0 || strcmp(relation, "���") == 0 || strcmp(relation, "����") == 0 || strcmp(relation, "����") == 0 || strcmp(relation, "Ů��") == 0)
	{
		if (T->number == 0)
		{
			cout << "������û����" << endl;
			return -1;
		}
		else if (T->number == 1&&(strcmp(relation, "���") == 0 || strcmp(relation, "�ܵ�") == 0))
		{
			cout << "�������ݲ����ö���" << endl;
			return -1;
		}
		else
		{
			Createman(man);
			CSNode* p = (CSNode*)malloc(sizeof(struct CSNode));
			if (p == NULL)
			{
				cout << "����ʧ�ܣ�" << endl;
				return -1;
			}
			p->data = man;
			p->firstchild = NULL;
			p->nextsibling = NULL;
			if (strcmp(relation, "�ܵ�") == 0 || strcmp(relation, "����") == 0)
			{
				int t=Find(T, parent, silding, name);
				if (t == 0)
				{
					cout << "�Ҳ�������" << endl;
					return -1;
				}
				p->nextsibling = silding->nextsibling;
				silding->nextsibling = p;
				p->firstchild = NULL;
				T->number++;
			}
			else if (strcmp(relation, "���") == 0 || strcmp(relation, "���") == 0)
			{
				int t=Find(T, parent, silding, name);
				if (t == 0)
				{
					cout << "�Ҳ�������" << endl;
					return -1;
				}
				CSNode* temp = (CSNode*)malloc(sizeof(struct CSNode));
				temp = parent->firstchild;
				if (temp == silding)
				{
					p->nextsibling = temp;
					parent->firstchild = p;
					T->number++;
				}
				else
				{
					while (temp->nextsibling != silding)
					{
						temp = temp->nextsibling;
					}
					temp->nextsibling = p;
					p->nextsibling = silding;
					T->number++;
				}
			}
			else if (strcmp(relation, "����") == 0 || strcmp(relation, "Ů��") == 0)
			{
				if (parent == NULL)
				{
					cout << "����ʧ��" << endl;
					return -1;
				}
				int t=Find(T, silding, parent,name);
				if (t == 0)
				{
					cout << "�Ҳ�������" << endl;
					return -1;
				}
				if (!parent->firstchild)
				{
					parent->firstchild = p;
				}
				else
				{
					p->nextsibling = parent->firstchild;
					parent->firstchild = p;
				}
				T->number++;
			}
			return 1;
		}
	}
	return 1;
}

void TraverseFT(CSTree T)
{
	ofstream fout("output.txt");
	int i = 0;
	if (T == NULL)
		return;
	temp = T;
	stack<CSNode*> cstree1;
	while (!cstree1.empty() || temp)
	{
		while (temp)
		{
			for (int j = 0; j <= i; j++)
			{
				cout << "  ";
				fout << "  ";
			}
			cout << "-";
			fout << "-";
			Showman(temp->data);
			fout << "������" << temp->data.name << " ";
			fout << "�������£�" << temp->data.born_year << "��" << temp->data.born_month << "��" << temp->data.born_day << "�� ";
			if (temp->data.marriage == 1)
			{
				if (temp->data.gender == 'f')
				{
					fout << "�ɷ�" << temp->data.couple << " ";
				}
				else
				{
					fout << "���ӣ�" << temp->data.couple << " ";
				}
			}
			else if (temp->data.marriage == 0)
			{
				fout << "��δ��顣 ";
			}
			fout << "��ַ��" << temp->data.address << endl;
			fout << endl;
			cstree1.push(temp);
			temp = temp->firstchild;
			i++;
		}
		if (!cstree1.empty())
		{
			temp = cstree1.top();
			cstree1.pop();
			temp = temp->nextsibling;
			i--;
		}
	}
}

int CreateCSTree(CSTree& T)
{
	fstream fp;
	fp.open("1.txt",ios::in);
	int n;
	fp >> n;
	while (n--)
	{
		char name[20], relation[20];
		fp >> name >> relation;
		if (strcmp(relation, "����")==0)
		{
			if (T->number == 0)
			{
				Createman(T->data,fp);
				T->firstchild = NULL;
				T->nextsibling = NULL;
				T->number++;
			}
			else if (T->number != 0)
			{
				
				CSNode* p = (CSNode*)malloc(sizeof(struct CSNode));
				if (p == NULL)
				{
					cout << "����ʧ�ܣ�" << endl;
					fp.close();
					return -1;
				}
				Createman(p->data,fp);
				p->nextsibling = NULL;
				p->firstchild = T;
				T = p;
				T->number++;
			}
		}
		else if (strcmp(relation,"���")==0|| strcmp(relation, "�ܵ�") == 0 || strcmp(relation, "���") == 0 || strcmp(relation, "����") == 0 || strcmp(relation, "����") == 0 || strcmp(relation, "Ů��") == 0)
		{
			if (T->number == 0)
			{
				cout << "������û����" << endl;
				return -1;
			}
			else if (T->number == 1 && (strcmp(relation, "���") == 0 || strcmp(relation, "�ܵ�") == 0))
			{
				cout << "�������ݲ����ö���" << endl;
				return -1;
			}
			else
			{
				CSNode* p = (CSNode*)malloc(sizeof(struct CSNode));
				if (p == NULL)
				{
					cout << "����ʧ�ܣ�" << endl;
					return -1;
				}
				Createman(p->data,fp);
				p->firstchild = NULL;
				p->nextsibling = NULL;
				if (strcmp(relation, "�ܵ�") == 0 || strcmp(relation, "����") == 0)
				{
					int t=Find(T, parent, silding, name);
					if (t == 0)
					{
						cout << "�Ҳ�������" << endl;
						return -1;
					}
					p->nextsibling = silding->nextsibling;
					silding->nextsibling = p;
					p->firstchild = NULL;
					T->number++;
				}
				else if (strcmp(relation, "���") == 0 ||strcmp(relation, "���") == 0)
				{
					int t=Find(T, parent, silding, name);
					if (t == 0)
					{
						cout << "�Ҳ�������" << endl;
						return -1;
					}
					CSNode* temp = (CSNode*)malloc(sizeof(struct CSNode));
					temp = parent->firstchild;
					if (temp == silding)
					{
						p->nextsibling = temp;
						parent->firstchild = p;
						T->number++;
					}
					else
					{
						while (temp->nextsibling != silding)
						{
							temp = temp->nextsibling;
						}
						temp->nextsibling = p;
						p->nextsibling = silding;
						T->number++;
					}
				}
				else if (strcmp(relation, "����") == 0 || strcmp(relation, "Ů��") == 0)
				{
					if (parent == NULL)
					{
						cout << "����ʧ��" << endl;
						fp.close();
						return -1;
					}
					int t=Find(T, silding, parent, name);
					if (t == 0)
					{
						cout << "�Ҳ�������" << endl;
						return -1;
					}
					if (!parent->firstchild)
					{
						parent->firstchild = p;
					}
					else
					{
						p->nextsibling = parent->firstchild;
						parent->firstchild = p;
					}
					T->number++;
				}
			}
		}
	}
	fp.close();
	return 1;
}

void Deleteman(CSTree& T)
{
	char name[20];
	cout << "����������Ҫ�������׵���������";
	cin >> name;
	int t=Find(T, parent, silding, name);
	if (t == 0)
	{
		cout << "�Ҳ�������" << endl;
		return;
	}
	if (silding == T)
	{
		cout << "���Ȳ��ɱ�" << endl;
	}
	else
	{
		if (parent->firstchild == silding)
		{
			parent->firstchild = silding->nextsibling;
			free(silding);
		}
		else
		{
			parent = parent->firstchild;
			while (parent->nextsibling != silding)
			{
				parent = parent->nextsibling;
			}
			parent->nextsibling = silding->nextsibling;
			free(silding);
		}
	}
}

void modifyinfo(CSTree& T)
{
	char name[20];
	cout << "����������Ҫ�޸���Ϣ����������";
	cin >> name;
	int t=Find(T, parent, silding, name);
	if (t == 0)
	{
		cout << "�Ҳ�������" << endl;
		return;
	}
	cout << "��ѡ����Ҫ�޸ĵ���:" << endl;
	cout << "1.���� " << "2.�������� " << "3.����״�� " << "4.����״�� " << "5.�������� " << "6.��ַ" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		cout << "��������Ҫ�޸ĵ�����:";
		cin >> silding->data.name;
	}
	if (choice == 2)
	{
		cout << "��������Ҫ�޸ĵ�����:";
		cin >> silding->data.born_year>>silding->data.born_month>>silding->data.born_day;
	}
	if (choice == 3)
	{
		cout << "��������Ҫ�޸ĵĻ���:";
		cin >> silding->data.marriage;
		if (silding->data.marriage == 1)
		{
			cout << "Plz Enter the couple name:";
			cin >> silding->data.couple;
		}
	}
	if (choice == 4)
	{
		cout << "��������Ҫ�޸ĵ�����״��:";
		cin >> silding->data.alive;
	}
	if (choice == 5)
	{
		cout << "��������Ҫ�޸ĵ���������:";
		cin >> silding->data.die_year>>silding->data.born_month>>silding->data.die_day;
	}
	if (choice == 6)
	{
		cout << "��������Ҫ�޸ĵĵ�ַ:";
		cin >> silding->data.address;
	}
}

int Findman(CSTree T)
{
	char name[20];
	cout << "��������Ҫ���ҵ��˵�������";
	cin >> name;
	int t=Find(T, parent, silding, name);
	if (t == 0)
	{
		cout << "�Ҳ�������" << endl;
		return -1;
	}
	cout << "����:" << silding->data.name;
	if (silding->data.marriage == 1)
	{
		if (silding->data.gender == 'f')
		{
			cout << " �ɷ�:" << silding->data.couple<<endl;
		}
		else
		{
			cout << " ����:" << silding->data.couple << endl;
		}
	}
	else if (silding->data.marriage == 0)
	{
		cout << " ��δ��飬������" << endl;
	}
	cout<< "����:" << parent->data.name <<" ĸ��:"<<parent->data.couple<< endl;
	silding = silding->firstchild;
	cout << "��Ů:";
	while (silding)
	{
		cout << silding->data.name << " ";
		silding = silding->nextsibling;
	}
	cout << endl;
	parent = parent->firstchild;
	cout << "�ֵܽ���:";
	while (parent)
	{
		if (parent->data.name==name)
		{
			cout << parent->data.name << " ";
		}
		parent = parent->nextsibling;
	}
	cout << endl;
	return 1;
}

int Findbirth(CSTree T)
{
	int year, month, day;
	cout << "��������Ҫ���ҵ��˵ĳ��������գ�";
	cin >> year>>month>>day;
	temp = T;
	cstree.push(temp);
	while (!cstree.empty())
	{
		temp = cstree.front();
		if (temp->data.born_year == year && temp->data.born_month == month && temp->data.born_day == day)
		{
			cout << "��Ҫ���ҵ���Ϊ" << temp->data.name << endl;
			while (!cstree.empty())
				cstree.pop();
			return 1;
		}
		cstree.pop();
		if (temp->firstchild)
		{
			temp = temp->firstchild;
			while (temp)
			{
				cstree.push(temp);
				temp = temp->nextsibling;
			}
		}
	}
	cout << "���޴���" << endl;
	return 0;
}

int FindNdynasty(CSTree T)
{
	queue<CSNode*> cstree1, cstree2;
	int n;
	cout << "��������Ҫ�鿴�ڼ�������:";
	cin >> n;
	int i = 1;
	temp = T;
	cstree1.push(temp);
	while (!cstree1.empty() || !cstree2.empty())
	{
		if (i == n)
		{
			break;
		}
		if (i % 2 == 1)
		{
			while (!cstree1.empty())
			{
				temp = cstree1.front();
				cstree1.pop();
				temp = temp->firstchild;
				while (temp)
				{
					cstree2.push(temp);
					temp = temp->nextsibling;
				}
			}
			i++;
		}
		else if (i % 2 == 0)
		{
			while (!cstree2.empty())
			{
				temp = cstree2.front();
				cstree2.pop();
				temp = temp->firstchild;
				while (temp)
				{
					cstree1.push(temp);
					temp = temp->nextsibling;
				}
			}
			i++;
		}
	}
	if (i % 2 == 0)
	{
		while (!cstree2.empty())
		{
			temp = cstree2.front();
			cstree2.pop();
			Showman(temp->data);
		}
	}
	else
	{
		while (!cstree1.empty())
		{
			temp = cstree1.front();
			cstree1.pop();
			Showman(temp->data);
		}
	}
	return 1;
}

int Show(CSTree T)
{
	char name1[20], name2[20];
	cout << "PLz Enter the double name:";
	cin >> name1 >> name2;
	CSNode* parent1 = (CSNode*)malloc(sizeof(struct CSNode));
	CSNode* silding1 = (CSNode*)malloc(sizeof(struct CSNode));
	CSNode* parent2 = (CSNode*)malloc(sizeof(struct CSNode));
	CSNode* silding2 = (CSNode*)malloc(sizeof(struct CSNode));
	int t1=Find(T, parent1, silding1, name1);
	int t2=Find(T, parent2, silding2, name2);
	if (t1 == 0||t2==0)
	{
		cout << "�Ҳ�������" << endl;
		return -1;
	}
	if (strcmp(parent1->data.name, name2) == 0)
	{
		if (parent1->data.gender == 'f')
		{
			cout << name2 << "��" << name1 << "��ĸ��" << endl;
		}
		else if (parent1->data.gender == 'm')
		{
			cout << name2 << "��" << name1 << "�ĸ���" << endl;
		}
		return 1;
	}
	if (strcmp(parent2->data.name, name1) == 0)
	{
		if (parent2->data.gender == 'f')
		{
			cout << name1 << "��" << name2 << "��ĸ��" << endl;
		}
		else if (parent2->data.gender == 'm')
		{
			cout << name1 << "��" << name2 << "�ĸ���" << endl;
		}
		return 1;
	}
	else
	{
		if (strcmp(parent1->data.name, parent2->data.name) == 0)
		{
			cout << name2 << "��" << name1 << "���ֵܽ���" << endl;
			return 1;
		}
		Find(T, parent1, silding1, name1);
		Find(T, parent2, silding2, parent1->data.name);
		if (strcmp(parent2->data.name, name2) == 0)
		{
			if (parent2->data.gender == 'f')
			{
				cout << name2 << "��" << name1 << "������" << endl;
			}
			else if (parent2->data.gender == 'm')
			{
				cout << name2 << "��" << name1 << "��үү" << endl;
			}
			return 1;
		}
		Find(T, parent1, silding1, name2);
		Find(T, parent2, silding2, parent1->data.name);
		if (strcmp(parent2->data.name, name1) == 0)
		{
			if (parent2->data.gender == 'f')
			{
				cout << name1 << "��" << name2 << "������" << endl;
			}
			else if (parent2->data.gender == 'm')
			{
				cout << name1 << "��" << name2 << "��үү" << endl;
			}
			return 1;
		}
		Find(T, parent1, silding1, name1);
		Find(T, parent2, silding2, name2);
		Find(T, parent, silding, parent1->data.name);
		temp = parent->firstchild;
		while (temp)
		{
			if (strcmp(temp->data.name, parent2->data.name) == 0)
			{
				cout << name1 << "��" << name2 << "Ϊ���ֵܽ���" << endl;
				return 1;
			}
			temp = temp->nextsibling;
		}
		Find(T, parent, silding, name1);
		Find(T, parent, silding, parent->data.name);
		Find(T, parent, silding, parent->data.name);
		Find(T, parent, silding, parent->data.name);
		silding = parent->firstchild;
		while (silding)
		{
			temp = silding->firstchild;
			while (temp)
			{
				if (strcmp(temp->data.name, name2) == 0)
				{
					if (temp->data.gender == 'f')
					{
						cout << name2 << "��" << name1 << "�İ���" << endl;
					}
					else
					{
						cout << name2 << "��" << name1 << "������" << endl;
					}
					return 1;
				}
				temp = temp->nextsibling;
			}
			silding = silding->nextsibling;
		}
		Find(T, parent, silding, name2);
		Find(T, parent, silding, parent->data.name);
		Find(T, parent, silding, parent->data.name);
		Find(T, parent, silding, parent->data.name);
		silding = parent->firstchild;
		while (silding)
		{
			temp = silding->firstchild;
			while (temp)
			{
				if (strcmp(temp->data.name, name1) == 0)
				{
					if (temp->data.gender == 'f')
					{
						cout << name1 << "��" << name2 << "�İ���" << endl;
					}
					else
					{
						cout << name1 << "��" << name2 << "������" << endl;
					}
					return 1;
				}
				temp = temp->nextsibling;
			}
			silding = silding->nextsibling;
		}
	}
	return 0;
}

void menu(CSTree &T,int &flag)
{
	cout << "                                              ==========================" << endl;
	cout << "                                              ||  1.�鿴����          ||\n";
	cout << "                                              ||  2.�޸ļ�����Ա��Ϣ  ||\n";
	cout << "                                              ||  3.�鿴ĳ����ϸ��Ϣ  ||\n";
	cout << "                                              ||  4.��ĳ�˿�������    ||\n";
	cout << "                                              ||  5.��Ӽ��׳�Ա      ||\n";
	cout << "                                              ||  6.��ʾ��n��         ||\n";
	cout << "                                              ||  7.�ж����˹�ϵ      ||\n";
	cout << "                                              ||  8.����������        ||\n";
	cout << "                                              ||  9.�˳�              ||" << endl;
	cout << "                                              ==========================" << endl;
	cout << "                                              ���������ѡ��";
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		TraverseFT(T);
	}
	if (choice == 2)
	{
		modifyinfo(T);
	}
	if (choice == 3)
	{
		Findman(T);
	}
	if (choice == 4)
	{
		Deleteman(T);
	}
	if (choice == 5)
	{
		Insertman(T);
	}
	if (choice == 6)
	{
		FindNdynasty(T);
	}
	if (choice == 7)
	{
		int t=Show(T);
		if (t == 0)
		{
			cout << "��ϵ��������" << endl;
		}
	}
	if (choice == 8)
	{
		Findbirth(T);
	}
	if (choice == 9)
	{
		flag = 0;
	}
}

int main()
{
	CSTree T;
	InitCSTree(T);
	CreateCSTree(T);
	//fclose(stdin);
	int flag = 1;
	while (1)
	{
		menu(T, flag);
		if (flag == 0)
		{
			break;
		}
	}
	free(T);
	free(parent);
	free(silding);
	return 0;
}