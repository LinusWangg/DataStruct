#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<fstream>
#include<errno.h>
#include<assert.h>
#include<bitset>
using namespace std;
typedef struct HTNode {
	int position;
	int weight;
	int flag;
	string code;
	struct HTNode* parent, * lchild, * rchild;
}HTNode, * HuffmanTree;
int word = 0;
int wordnum=0;
int words[300];
string code[100000];
char article[100000];
void Select(HuffmanTree* HF, int& s1, int& s2, int n)
{
	int k, w,i;
	w = INT_MAX;
	for (k = 1; k <= n; k++)
	{
		if (HF[k]->weight < w && HF[k]->flag == 0 && HF[k]->weight != 0)
		{
			w = HF[k]->weight;
			s1 = k;
		}
	}
	int j = s1;
	w = INT_MAX;
	for (k = 1; k <= n; k++)
	{
		if (HF[k]->weight < w && k != j && HF[k]->flag == 0 && HF[k]->weight != 0)
		{
			w = HF[k]->weight;
			s2 = k;
		}
	}
}

void HuffmanCoding(HuffmanTree* HF, int n)
{
	int s1, s2, i, j;
	for (i = n + 1; i <= 2 * n; i++)
	{
		Select(HF, s1, s2, i);
		HF[s1]->flag = 1;
		HF[s2]->flag = 1;
		HF[s1]->parent = HF[i];
		HF[s2]->parent = HF[i];
		HF[i]->lchild = HF[s1];
		HF[i]->rchild = HF[s2];
		HF[i]->weight = HF[s1]->weight + HF[s2]->weight;
		HF[i]->flag = 0;
	}
}

void HuffmanCode(HuffmanTree HF)
{
	if (HF->lchild != NULL)
	{
		code[HF->lchild->position] = code[HF->position] + '0';
		HuffmanCode(HF->lchild);
	}
	if (HF->rchild != NULL)
	{
		code[HF->rchild->position] = code[HF->position] + '1';
		HuffmanCode(HF->rchild);
	}
	return;
}

void bianma(HuffmanTree* HF)
{
	fstream file;
	file.open("code.txt", ios::in);
	assert(file.is_open());
	char c;
	int k = 1;
	int t = 0;
	file >> noskipws;
	while (!file.eof())
	{
		file >> c;
		words[c]++;
		article[wordnum] = c;
		wordnum++;
	}
	for (int i = 1; i <= 256; i++)
	{
		if (words[i])
			word++;
	}
	for (int i = 1; i <= 256; i++)
	{
		if (words[i])
		{
			HTNode* p = (HTNode*)malloc(sizeof(struct HTNode));
			p->position = i;
			p->weight = words[i];
			p->lchild = NULL;
			p->rchild = NULL;
			p->flag = 0;
			HF[k] = p;
			k++;
		}
	}
	for (int i = word + 1; i <= 2 * word; i++)
	{
		HTNode* p = (HTNode*)malloc(sizeof(struct HTNode));
		p->position = i+10000;
		p->weight = 0;
		p->lchild = NULL;
		p->rchild = NULL;
		p->flag = 0;
		HF[i] = p;
	}
	HuffmanCoding(HF, word);
	HuffmanCode(HF[2 * word-1]);
	file.close();
}

int s = 0;
char b = 0;
void WriteBit(char x, FILE* p)//∞ÀŒª¥Ê»Î
{
	if (x == '1')
		b |= 1 << 7 - s;
	else if (x == '0')
		b |= 0 << 7 - s;
	s++;
	if (s == 8) {
		fwrite(&b, sizeof(char), 1, p);
		b = 0;
		s = 0;
	}
}

void WriteCode(HuffmanTree *HF)
{
	FILE* file;
	errno_t err;
	err=fopen_s(&file,"recode.dat","w");
	for (int i = 0; i < wordnum; i++)
	{
		for (int j = 0; j < code[article[i]].size(); j++)
		{
			WriteBit(code[article[i]][j], file);
		}
	}
	fclose(file);
}

void yima(HuffmanTree* HF)
{
	HTNode* maxn, * temp;
	maxn = (HTNode*)malloc(sizeof(struct HTNode));
	temp = (HTNode*)malloc(sizeof(struct HTNode));
	maxn->weight = 0;
	int i = 0, m = 0;
	maxn = HF[2 * word - 1];
	FILE* fp;
	string rcode;
	errno_t err;
	err = fopen_s(&fp, "recode.dat", "rb");
	char t;
	temp = maxn;
	while (fread(&t, sizeof(char), 1, fp))
	{
		for (int i = 0; i < 8; i++)
		{
			if (((t >> 7) & 1) == 1)
				rcode += '1';
			else
				rcode += '0';
			t <<= 1;
		}
	}
	for (int i = 0; i < rcode.size(); i++)
	{
		if (rcode[i] == '0')
		{
			temp = temp->lchild;
			if (temp->lchild == NULL && temp->rchild == NULL)
			{
				cout << (char)temp->position;
				temp = maxn;
			}
		}
		else if (rcode[i] == '1')
		{
			temp = temp->rchild;
			if (temp->lchild == NULL && temp->rchild == NULL)
			{
				cout << (char)temp->position;
				temp = maxn;
			}
		}
	}
	fclose(fp);
}

void shouhuffmancode(HuffmanTree* HF)
{
	for (int i = 1; i <= word; i++)
	{
		if (HF[i]->weight == 0)
			continue;
		char c = HF[i]->position;
		cout << c << " " << HF[i]->weight << " " << code[HF[i]->position] << endl;
	}
}

int main()
{
	int i, n = 256;
	HuffmanTree* HF;
	HTNode* p;
	HF = (HuffmanTree*)malloc((2 * n + 1) * sizeof(HuffmanTree));
	bianma(HF);
	shouhuffmancode(HF);
	WriteCode(HF);
	yima(HF);
}
