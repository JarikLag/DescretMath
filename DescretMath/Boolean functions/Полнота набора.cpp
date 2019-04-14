// CF.cpp: определяет точку входа для консольного приложения.
//

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <ctime>
using namespace std;

typedef long long LL;

int toInt(string s)
{
	int rez = 0;
	for (int i = 0; i < s.length(); i++)
	{
		rez += (s[i] - '0') * (1 << i);
	}
	return rez;
}

string toString(int x, int size)
{
	string s;
	while (x != 0)
	{
		s += ((x % 2) + '0');
		x /= 2;
	}
	while (s.length() != size)
	{
		s += '0';
	}
	return s;
}

bool compareStrings(string a, string b)
{
	for (int i = 0; i < a.length(); i++)
	{
		if (b[i] < a[i])
			return false;
	}
	return true;
}

int main()
{
	int n;
	cin >> n;
	vector<string> table(n);
	for (int i = 0; i < n; i++)
	{
		int s;
		cin >> s >> table[i];
	}

	bool saveZero = true,
		saveOne = true,
		monoton = true,
		line = true,
		selfDual = true;

	for (int i = 0; i < n; i++)
	{
		if (table[i][0] != '0')
			saveZero = false;
	}

	for (int i = 0; i < n; i++)
	{
		if (table[i][table[i].length() - 1] != '1')
			saveOne = false;
	}

	for (int i = 0; i < n; i++)
	{
		int sz = table[i].size();
		if (sz == 1)
		{
			selfDual = false;
			break;
		}
		for (int j = 0; j < sz / 2; j++)
		{
			if (table[i][j] == table[i][sz - 1 - j])
			{
				selfDual = false;
				break;
			}
		}
		if (!selfDual)
			break;
	}

	for (int i = 0; i < n; i++)
	{
		int sz = table[i].length();
		for (int k = 0; k < sz; k++)
		{
			string start = toString(k, log2(sz)), end = toString(sz - 1, log2(sz)), now;
			char check = table[i][k];
			int cl = k;
			now = start;
			while (1)
			{
				if (compareStrings(start, now))
				{
					if (check > table[i][toInt(now)])
					{
						monoton = false;
						break;
					}
				}
				if (now == end)
					break;
				cl++;
				now = toString(cl, log2(sz));
			}
			if (!monoton)
				break;
		}
		if (!monoton)
			break;
	}
	
	for (int i = 0; i < n; i++)
	{
		int sz = table[i].length();
		string xor;
		vector<int> arr(sz);
		for (int j = 0; j < sz; j++)
			arr[j] = (table[i][j] - '0');
		xor += (arr[0] + '0');
		int cnt = 1;
		for (int j = 1; j < sz; j++)
		{
			for (int k = 0; k < sz - cnt; k++)
			{
				arr[k] = (arr[k] ^ arr[k + 1]);
			}
			xor += (arr[0] + '0');
			cnt++;
		}
		for (int j = 1; j < xor.length(); j++)
		{
			if (j & (j - 1) != 0)
			{
				if (xor[j] == '1')
				{
					line = false;
					break;
				}
			}
		}
		if (!line)
			break;
	}
	if (!saveOne && !saveZero && !selfDual && !monoton && !line)
	{
		cout << "YES";
	}
	else
	{
		cout << "NO";
	}
	return 0;
}