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

struct Node
{
	LL var;
	int left, right;

	Node()
	{}

	Node(LL v, int l, int r)
	{
		var = v;
		left = l;
		right = r;
	}
};

vector<Node> arr;
priority_queue<pair<LL, int> > query;
vector<LL> sizes;

void dfs(int v, LL cnt)
{
	if (arr[v].left == -1 && arr[v].right == -1)
	{
		sizes[v] = cnt;
		return;
	}
	dfs(arr[v].left, cnt + 1);
	dfs(arr[v].right, cnt + 1);
}

int main()
{
	ios::sync_with_stdio(false);
	//freopen("huffman.in", "r", stdin);
	//freopen("huffman.out", "w", stdout);
	int n;
	cin >> n;
	arr.resize(n, Node(0, -1, -1));
	sizes.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i].var;
		query.push(make_pair(-arr[i].var, i));
	}
	while (query.size() > 1)
	{
		int find = query.top().second;
		query.pop();
		int sind = query.top().second;
		query.pop();
		arr.push_back(Node(arr[find].var + arr[sind].var, find, sind));
		query.push(make_pair(-(arr[find].var + arr[sind].var), arr.size() - 1));
	}
	dfs(query.top().second, 0);
	LL ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans += arr[i].var * sizes[i];
	}
	cout << ans;
	return 0;
}