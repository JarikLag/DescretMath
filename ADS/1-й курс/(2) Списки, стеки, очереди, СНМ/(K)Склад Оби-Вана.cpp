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
    int val;
    Node *front = NULL, *back = NULL;
 
    Node()
    {}
 
    Node(int v, Node *f, Node *b)
    {
        val = v;
        front = f;
        back = b;
    }
};
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("kenobi.in", "r", stdin);
    freopen("kenobi.out", "w", stdout);
    int n, size = 0;
    cin >> n;
    Node *head = new Node, *tail = new Node, *center = new Node;
    for (int i = 0; i < n; i++)
    {
        string s;
        int a;
        cin >> s;
 
        if (s == "add")
        {
            cin >> a;
            Node *p = new Node;
            if (size == 0)
            {
                p->val = a;
                head = tail = center = p;
                size++;
            }
            else
            {
                p->val = a;
                p->front = tail;
                tail->back = p;
                tail = p;
                size++;
 
                if (size % 2 == 1)
                {
                    center = center->back;
                }
            }
        }
 
        else if (s == "take")
        {
            if (size == 0)
                continue;
            if (size == 1)
            {
                head = tail = center = new Node;
                size--;
                continue;
            }
            tail = tail->front;
            tail->back = NULL;
            size--;
            if (size % 2 == 0)
            {
                center = center->front;
            }
        }
 
        else if (s == "mum!")
        {
            if (size < 2)
                continue;
            if (size % 2 == 0)
            {
                tail->back = head;
                head->front = tail;
                head = center->back;
                Node *tmp = tail;
                tail = center;
                center = tmp;
                tail->back = NULL;
            }
            else
            {
                Node *tmp = center->front;
                tail->back = head;
                head->front = tail;
                head = center;
                center = tail;
                tail = tmp;
                tail->back = NULL;
            }
        }
    }
    Node *now = head;
    cout << size << endl;
    if (size == 0)
        return 0;
    while (now != NULL)
    {
        cout << now->val << ' ';
        now = now->back;
    }
    return 0;
}