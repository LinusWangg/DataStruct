#include<iostream>
using namespace std;
int main()
{
	int num = 1, flag = 0,sum=0,temp=2;
	cin >> num;
	if (num == 0)
	{
		cout << 0 << endl;
		return 0;
	}
	if (num == 1)
	{
		sum += 1;

	}
	if (num == 2)
	{
		sum += 2;
		flag = 1;
		temp += 2;
	}
	while (num != 0)
	{
		cin >> num;
		if (num == 0)
			break;
		else if (num == 1)
		{
			flag = 0;
			sum += 1;
			temp = 2;
		}
		else if (num == 2 && flag == 0)
		{
			sum += 2;
			flag = 1;
			temp += 2;
		}
		else if (num == 2 && flag == 1)
		{
			sum += temp;
			flag = 1;
			temp += 2;
		}
	}
	cout << sum;
}