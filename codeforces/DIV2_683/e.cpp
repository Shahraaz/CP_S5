#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

int node_cnt = 1;
int left_node[NAX * 30];
int right_node[NAX * 30];

void add(int x, int id)
{
    auto curr = 0;
    for (int i = 30 - 1; i >= 0; i--)
        if (x & (1 << i))
        {
            if (right_node[curr] == -1)
                right_node[curr] = node_cnt++;
            curr = right_node[curr];
        }
        else
        {
            if (left_node[curr] == -1)
                left_node[curr] = node_cnt++;
            curr = left_node[curr];
        }
}

int dfs(int node)
{
    if (node == -1)
        return 0;
    if (left_node[node] == -1 && right_node[node] == -1)
        return 1;
    int curr_l = dfs(left_node[node]);
    int curr_r = dfs(right_node[node]);
    auto ret = 0;
    if (curr_l == 0)
        ret = curr_r;
    else if (curr_r == 0)
        ret = curr_l;
    else
        ret = max(curr_l, curr_r) + 1;
    db(node, ret, left_node[node], right_node[node]);
    return ret;
}

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    memset(left_node, -1, sizeof left_node);
    memset(right_node, -1, sizeof right_node);
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        add(a[i], i);
    }
    cout << n - dfs(0) << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}