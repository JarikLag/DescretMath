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

int toIntFromBinary(string s)
{
	int rez = 0;
	for (int i = 0; i < s.length(); i++)
	{
		rez += (s[i] - '0') * (1 << i);
	}
	return rez;
}

string toBinaryString(int x, int size)
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
	reverse(s.begin(), s.end());
	return s;
}

string toRandomString(int x, int size, int sys)
{
	string s;
	while (x != 0)
	{
		s += ((x % sys) + '0');
		x /= sys;
	}
	while (s.length() != size)
	{
		s += '0';
	}
	reverse(s.begin(), s.end());
	return s;
}

int toInt(string s)
{
	int p = 0, ans = 0;
	for (int i = s.length() - 1; i >= 0; i--)
	{
		ans += (s[i] - '0') * pow(10, p);
		p++;
	}
	return ans;
}

int op[101][10];
bool used[101][10];
int p[10][3] = { { 4, 6, -1 },
{ 8, 6, -1 },
{ 7, 9, -1 },
{ 8, 4, -1 },
{ 3, 9, 0 },
{ -1, -1, -1 },
{ 1, 7, 0 },
{ 6, 2, -1 },
{ 1, 3, -1 },
{ 4, 2, -1 } };

LL dp[41][41];

bool correctPrefix(string s)
{
	stack<char> now;
	for (int i = 0; i < s.length(); i++)
	{
		if (now.empty())
		{
			if (s[i] == ']' || s[i] == ')')
			{
				return false;
			}
			else
			{
				now.push(s[i]);
			}
		}
		else if (s[i] == ']' && now.top() == '(')
		{
			return false;
		}
		else if (s[i] == ')' && now.top() == '[')
		{
			return false;
		}
		else if (s[i] == ']' && now.top() == '[')
		{
			now.pop();
		}
		else if (s[i] == ')' && now.top() == '(')
		{
			now.pop();
		}
		else
		{
			now.push(s[i]);
		}
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	freopen("num2brackets.in", "r", stdin);
	freopen("num2brackets.out", "w", stdout);
	dp[0][0] = 1;
	for (int i = 1; i < 41; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (j != 0)
				dp[i][j] += dp[i][j - 1];
			dp[i][j] += dp[i - 1][j];
		}
	}
	LL num;
	int len;
	cin >> len >> num;
	int cl = 0, op = 0;
	char alf[4] = { '(', ')', '[', ']' };
	string wow, s;
	for (int i = 0; i < len * 2; i++)
	{
		int ind = 0;
		while (ind < 2)
		{
			int ncl = cl, nop = op;
			if (ind == 0)
			{
				nop++;
				wow.push_back('(');
			}
			else
			{
				ncl++;
				wow.push_back(')');
			}
			if (correctPrefix(wow))
				if (num >= dp[len - ncl][len - nop])
					num -= dp[len - ncl][len - nop];
				else
				{
					s += wow.back();
					break;
				}
			ind++;
			wow.pop_back();
		}
		if (s[i] == '(')
			op++;
		else
			cl++;
	}
	cout << s;
	return 0;
}