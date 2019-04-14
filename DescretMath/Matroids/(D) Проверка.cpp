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
#include <bitset>
using namespace std;
 
typedef long long LL;
 
const LL INF = 1e18;
 
vector<bool> isIndep(2048, false);
vector<int> numbers;
 
inline int getSize(int i) {
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = (i + (i >> 4)) & 0x0f0f0f0f;
    i = i + (i >> 8);
    i = i + (i >> 16);
    return i & 0x3f;
}
 
int main() {
    #ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #else
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    #endif
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, x = 0;
        cin >> a;
        for (int j = 0; j < a; ++j) {
            cin >> b;
            x |= (1 << (b - 1));
        }
        numbers.push_back(x);
        isIndep[x] = true;
    }
    if (!isIndep[0]) {
        cout << "NO";
        return 0;
    }
    for (int i = 0; i < numbers.size(); ++i) {
        for (int j = 0; j < numbers[i]; ++j) {
            if ((numbers[i] | j) == numbers[i]) {
                if (!isIndep[j]) {
                    cout << "NO";
                    return 0;
                }
            }
        }
    }
    for (int i = 0; i < numbers.size(); ++i) {
        for (int j = 0; j < numbers.size(); ++j) {
            if (getSize(numbers[i]) > getSize(numbers[j])) {
                int tmp = numbers[i] & ~numbers[j], pos;
                bool flag = false;
                string binary = bitset<32>(tmp).to_string();
                for (int k = binary.size() - 1; k >= 0; --k) {
                    if (binary[k] == '1') {
                        pos = (1 << (binary.size() - 1 - k));
                        if (isIndep[numbers[j] | pos]) {
                            flag = true;
                            break;
                        }
                    }
                }
                if (!flag) {
                    cout << "NO";
                    return 0;
                }
            }
        }
    }
    cout << "YES";
    return 0;
}