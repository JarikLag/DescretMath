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
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
using namespace std;
 
typedef long long LL;
 
const int INF = 1e9;
 
vector<int> myQueue;
int head = 0, tail = 0, getSize = 0;
 
void myReverse(int l, int r) {
    int n;
    if (l <= r) {
        n = (r - l + 1) / 2;
    }
    else {
        n = (myQueue.size() - l + r + 1) / 2;
    }
    for (int i = 0; i < n; ++i) {
        swap(myQueue[l], myQueue[r]);
        ++l, --r;
        if (l == myQueue.size()) {
            l = 0;
        }
        if (r < 0) {
            r += myQueue.size();
        }
    }
}
 
inline void push(int x) {
    if (getSize != myQueue.size()) {
        myQueue[tail] = x;
        tail = (tail + 1) % myQueue.size();
		++getSize;
    }
}
 
inline void pop() {
    head = (head + 1) % myQueue.size();
}
 
int main() {
    #ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #else
    freopen("fullham.in", "r", stdin);
    freopen("fullham.out", "w", stdout);
    #endif
    int n;
	scanf("%d\n", &n);
    vector<vector<int>> graph(n, vector<int>(n, 0));
    myQueue.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < i + 1; ++j) {
            char c;
			scanf("%c", &c);
            graph[j][i + 1] = graph[i + 1][j] = (c - '0');      
        }
		scanf("\n");
    }
    for (int i = 0; i < n; ++i) {
        push(i);
    }
    for (int i = 0; i <= n * (n - 1); ++i) {
        int first = (head + 1);
		if (first >= n)
			first %= n;
        int next = (first + 1);
		if (next >= n)
			next %= n;
        if (graph[myQueue[head]][myQueue[first]] == 0) {
            while (graph[myQueue[head]][myQueue[next]] == 0 || graph[myQueue[first]][myQueue[(next + 1) % n]] == 0) {
                next = (next + 1);
				if (next >= n)
					next %= n;
            }
            myReverse(first, next);
        }
        push(myQueue[head]);
        pop();
    }
    for (int i = 0; i < n; ++i) {
		printf("%d ", myQueue[head] + 1);
        pop();
    }
    return 0;
}