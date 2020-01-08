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
		cout << "空间内存申请失败！" << endl;
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

int Find(CSTree T, CSTree& parent, CSTree& silbing, char *name)//直接找父亲和兄弟的节点定位，自我感觉最巧妙的函数
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
	cout << "姓名：" << man.name << " ";
	cout << "出生年月：" << man.born_year << "年" << man.born_month << "月" << man.born_day << "日 ";
	if (man.marriage == 1)
	{
		if (man.gender == 'f')
		{
			cout << "丈夫：" << man.couple<<" ";
		}
		else
		{
			cout << "妻子：" << man.couple<<" ";
		}
	}
	else if (man.marriage == 0)
	{
		cout << "尚未结婚。 ";
	}
	cout << "地址：" << man.address << endl;
}

int Insertman(CSTree& T)
{
	char name[20],relation[20];
	people man;
	cout << "请输入其直系亲属与其关系(如果是第一人就输祖宗):";
	cin >> name >> relation;
	if (strcmp(relation, "祖宗") == 0)
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
				cout << "申请失败！" << endl;
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
	else if (strcmp(relation, "哥哥") == 0 || strcmp(relation, "弟弟") == 0 || strcmp(relation, "姐姐") == 0 || strcmp(relation, "妹妹") == 0 || strcmp(relation, "儿子") == 0 || strcmp(relation, "女儿") == 0)
	{
		if (T->number == 0)
		{
			cout << "家谱中没有人" << endl;
			return -1;
		}
		else if (T->number == 1&&(strcmp(relation, "哥哥") == 0 || strcmp(relation, "弟弟") == 0))
		{
			cout << "祖先列暂不设置多人" << endl;
			return -1;
		}
		else
		{
			Createman(man);
			CSNode* p = (CSNode*)malloc(sizeof(struct CSNode));
			if (p == NULL)
			{
				cout << "申请失败！" << endl;
				return -1;
			}
			p->data = man;
			p->firstchild = NULL;
			p->nextsibling = NULL;
			if (strcmp(relation, "弟弟") == 0 || strcmp(relation, "妹妹") == 0)
			{
				int t=Find(T, parent, silding, name);
				if (t == 0)
				{
					cout << "找不到此人" << endl;
					return -1;
				}
				p->nextsibling = silding->nextsibling;
				silding->nextsibling = p;
				p->firstchild = NULL;
				T->number++;
			}
			else if (strcmp(relation, "姐姐") == 0 || strcmp(relation, "哥哥") == 0)
			{
				int t=Find(T, parent, silding, name);
				if (t == 0)
				{
					cout << "找不到此人" << endl;
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
			else if (strcmp(relation, "儿子") == 0 || strcmp(relation, "女儿") == 0)
			{
				if (parent == NULL)
				{
					cout << "申请失败" << endl;
					return -1;
				}
				int t=Find(T, silding, parent,name);
				if (t == 0)
				{
					cout << "找不到此人" << endl;
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
			fout << "姓名：" << temp->data.name << " ";
			fout << "出生年月：" << temp->data.born_year << "年" << temp->data.born_month << "月" << temp->data.born_day << "日 ";
			if (temp->data.marriage == 1)
			{
				if (temp->data.gender == 'f')
				{
					fout << "丈夫：" << temp->data.couple << " ";
				}
				else
				{
					fout << "妻子：" << temp->data.couple << " ";
				}
			}
			else if (temp->data.marriage == 0)
			{
				fout << "尚未结婚。 ";
			}
			fout << "地址：" << temp->data.address << endl;
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
		if (strcmp(relation, "祖宗")==0)
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
					cout << "申请失败！" << endl;
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
		else if (strcmp(relation,"哥哥")==0|| strcmp(relation, "弟弟") == 0 || strcmp(relation, "姐姐") == 0 || strcmp(relation, "妹妹") == 0 || strcmp(relation, "儿子") == 0 || strcmp(relation, "女儿") == 0)
		{
			if (T->number == 0)
			{
				cout << "家谱中没有人" << endl;
				return -1;
			}
			else if (T->number == 1 && (strcmp(relation, "哥哥") == 0 || strcmp(relation, "弟弟") == 0))
			{
				cout << "祖先列暂不设置多人" << endl;
				return -1;
			}
			else
			{
				CSNode* p = (CSNode*)malloc(sizeof(struct CSNode));
				if (p == NULL)
				{
					cout << "申请失败！" << endl;
					return -1;
				}
				Createman(p->data,fp);
				p->firstchild = NULL;
				p->nextsibling = NULL;
				if (strcmp(relation, "弟弟") == 0 || strcmp(relation, "妹妹") == 0)
				{
					int t=Find(T, parent, silding, name);
					if (t == 0)
					{
						cout << "找不到此人" << endl;
						return -1;
					}
					p->nextsibling = silding->nextsibling;
					silding->nextsibling = p;
					p->firstchild = NULL;
					T->number++;
				}
				else if (strcmp(relation, "姐姐") == 0 ||strcmp(relation, "哥哥") == 0)
				{
					int t=Find(T, parent, silding, name);
					if (t == 0)
					{
						cout << "找不到此人" << endl;
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
				else if (strcmp(relation, "儿子") == 0 || strcmp(relation, "女儿") == 0)
				{
					if (parent == NULL)
					{
						cout << "申请失败" << endl;
						fp.close();
						return -1;
					}
					int t=Find(T, silding, parent, name);
					if (t == 0)
					{
						cout << "找不到此人" << endl;
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
	cout << "请输入你想要开出族谱的人姓名：";
	cin >> name;
	int t=Find(T, parent, silding, name);
	if (t == 0)
	{
		cout << "找不到此人" << endl;
		return;
	}
	if (silding == T)
	{
		cout << "祖先不可变" << endl;
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
	cout << "请输入你想要修改信息的人姓名：";
	cin >> name;
	int t=Find(T, parent, silding, name);
	if (t == 0)
	{
		cout << "找不到此人" << endl;
		return;
	}
	cout << "请选择你要修改的项:" << endl;
	cout << "1.姓名 " << "2.出生日期 " << "3.婚姻状况 " << "4.死亡状况 " << "5.死亡日期 " << "6.地址" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		cout << "请输入你要修改的姓名:";
		cin >> silding->data.name;
	}
	if (choice == 2)
	{
		cout << "请输入你要修改的生日:";
		cin >> silding->data.born_year>>silding->data.born_month>>silding->data.born_day;
	}
	if (choice == 3)
	{
		cout << "请输入你要修改的婚姻:";
		cin >> silding->data.marriage;
		if (silding->data.marriage == 1)
		{
			cout << "Plz Enter the couple name:";
			cin >> silding->data.couple;
		}
	}
	if (choice == 4)
	{
		cout << "请输入你要修改的死亡状况:";
		cin >> silding->data.alive;
	}
	if (choice == 5)
	{
		cout << "请输入你要修改的死亡日期:";
		cin >> silding->data.die_year>>silding->data.born_month>>silding->data.die_day;
	}
	if (choice == 6)
	{
		cout << "请输入你要修改的地址:";
		cin >> silding->data.address;
	}
}

int Findman(CSTree T)
{
	char name[20];
	cout << "请输入你要查找的人的姓名：";
	cin >> name;
	int t=Find(T, parent, silding, name);
	if (t == 0)
	{
		cout << "找不到此人" << endl;
		return -1;
	}
	cout << "姓名:" << silding->data.name;
	if (silding->data.marriage == 1)
	{
		if (silding->data.gender == 'f')
		{
			cout << " 丈夫:" << silding->data.couple<<endl;
		}
		else
		{
			cout << " 妻子:" << silding->data.couple << endl;
		}
	}
	else if (silding->data.marriage == 0)
	{
		cout << " 尚未结婚，至今单身。" << endl;
	}
	cout<< "父亲:" << parent->data.name <<" 母亲:"<<parent->data.couple<< endl;
	silding = silding->firstchild;
	cout << "子女:";
	while (silding)
	{
		cout << silding->data.name << " ";
		silding = silding->nextsibling;
	}
	cout << endl;
	parent = parent->firstchild;
	cout << "兄弟姐妹:";
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
	cout << "请输入你要查找的人的出生年月日：";
	cin >> year>>month>>day;
	temp = T;
	cstree.push(temp);
	while (!cstree.empty())
	{
		temp = cstree.front();
		if (temp->data.born_year == year && temp->data.born_month == month && temp->data.born_day == day)
		{
			cout << "你要查找的人为" << temp->data.name << endl;
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
	cout << "查无此人" << endl;
	return 0;
}

int FindNdynasty(CSTree T)
{
	queue<CSNode*> cstree1, cstree2;
	int n;
	cout << "请输入你要查看第几代族人:";
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
		cout << "找不到此人" << endl;
		return -1;
	}
	if (strcmp(parent1->data.name, name2) == 0)
	{
		if (parent1->data.gender == 'f')
		{
			cout << name2 << "是" << name1 << "的母亲" << endl;
		}
		else if (parent1->data.gender == 'm')
		{
			cout << name2 << "是" << name1 << "的父亲" << endl;
		}
		return 1;
	}
	if (strcmp(parent2->data.name, name1) == 0)
	{
		if (parent2->data.gender == 'f')
		{
			cout << name1 << "是" << name2 << "的母亲" << endl;
		}
		else if (parent2->data.gender == 'm')
		{
			cout << name1 << "是" << name2 << "的父亲" << endl;
		}
		return 1;
	}
	else
	{
		if (strcmp(parent1->data.name, parent2->data.name) == 0)
		{
			cout << name2 << "是" << name1 << "的兄弟姐妹" << endl;
			return 1;
		}
		Find(T, parent1, silding1, name1);
		Find(T, parent2, silding2, parent1->data.name);
		if (strcmp(parent2->data.name, name2) == 0)
		{
			if (parent2->data.gender == 'f')
			{
				cout << name2 << "是" << name1 << "的奶奶" << endl;
			}
			else if (parent2->data.gender == 'm')
			{
				cout << name2 << "是" << name1 << "的爷爷" << endl;
			}
			return 1;
		}
		Find(T, parent1, silding1, name2);
		Find(T, parent2, silding2, parent1->data.name);
		if (strcmp(parent2->data.name, name1) == 0)
		{
			if (parent2->data.gender == 'f')
			{
				cout << name1 << "是" << name2 << "的奶奶" << endl;
			}
			else if (parent2->data.gender == 'm')
			{
				cout << name1 << "是" << name2 << "的爷爷" << endl;
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
				cout << name1 << "与" << name2 << "为堂兄弟姐妹" << endl;
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
						cout << name2 << "是" << name1 << "的阿姨" << endl;
					}
					else
					{
						cout << name2 << "是" << name1 << "的叔叔" << endl;
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
						cout << name1 << "是" << name2 << "的阿姨" << endl;
					}
					else
					{
						cout << name1 << "是" << name2 << "的叔叔" << endl;
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
	cout << "                                              ||  1.查看家谱          ||\n";
	cout << "                                              ||  2.修改家谱人员信息  ||\n";
	cout << "                                              ||  3.查看某人详细信息  ||\n";
	cout << "                                              ||  4.将某人开除家谱    ||\n";
	cout << "                                              ||  5.添加家谱成员      ||\n";
	cout << "                                              ||  6.显示第n代         ||\n";
	cout << "                                              ||  7.判断两人关系      ||\n";
	cout << "                                              ||  8.按出生查找        ||\n";
	cout << "                                              ||  9.退出              ||" << endl;
	cout << "                                              ==========================" << endl;
	cout << "                                              请输入你的选择：";
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
			cout << "关系超过两代" << endl;
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