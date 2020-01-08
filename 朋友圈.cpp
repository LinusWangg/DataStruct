#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int fx[30001];
int sum[30001];
int Find(int x)
{
	if (fx[x] == x)
		return x;
	return Find(fx[x]);
}

void add(int x,int y)
{
	int a = Find(x);
	int b = Find(y);
	if (a != b)
	{
		fx[b] = a;
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		fx[i] = i;
	while (m--)
	{
		int num, x, y;
		cin >> num;
		for (int i = 1; i <= num; i++)
		{
			if (i == 1)
				cin >> x;
			else
			{
				cin >> y;
				add(x, y);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		sum[Find(i)]++;
	}
	for (int i = 1; i <= n; i++)
	{
		ans = max(ans, sum[i]);
	}
	cout << ans;
}