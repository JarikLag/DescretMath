// CF.cpp: определяет точку входа для консольного приложения.
//

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <ctime>
using namespace std;

typedef long long LL;

int partition(vector<int> &a, int left, int right)
{
	int i = left, j = right, key;
	srand(0);
	key = a[rand() % (right - left + 1) + left];
	while (i <= j)
	{
		while (a[i] < key)
			i++;
		while (a[j] > key)
			j--;
		if (i <= j)
		{
			swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	return max(j, left);
}

int findOrderStatisticsRandom(vector<int> &a, int k, int left, int right)
{
	if (right == left)
	{
		return a[left];
	}
	int middle = partition(a, left, right);
	if (k <= middle)
	{
		return findOrderStatisticsRandom(a, k, left, middle);
	}
	else
	{
		return findOrderStatisticsRandom(a, k, middle + 1, right);
	}
}

int main() 
{
	//freopen("kth.in", "r", stdin);
	//freopen("kth.out", "w", stdout);
	int n, k;
	cin >> n >> k;
	vector<int> arr(n);
	int a, b, c, a1, a2;
	cin >> a >> b >> c >> a1 >> a2;
	arr[0] = a1, arr[1] = a2;
	for (int i = 2; i < n; i++)
	{
		arr[i] = a * arr[i - 2] + b * arr[i - 1] + c;
	}
	cout << findOrderStatisticsRandom(arr, k - 1, 0, arr.size() - 1);
	return 0;
}