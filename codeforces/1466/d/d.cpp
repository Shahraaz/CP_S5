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

void solveCase()
{
    int n;
    cin >> n;
    vector<int> wt(n), degree(n);
    ll res = 0;
    for (size_t i = 0; i < n; i++)
    {
        cin >> wt[i];
        res += wt[i];
    }
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        degree[u - 1]++;
        degree[v - 1]++;
    }
    priority_queue<pair<int, int>> Q;
    for (size_t i = 0; i < n; i++)
        if (degree[i] != 1)
            Q.push({wt[i], degree[i] - 1});
    cout << res << ' ';
    for (size_t i = 1; i < n - 1; i++)
    {
        if (Q.size())
        {
            auto top = Q.top();
            Q.pop();
            res += top.first;
            top.second--;
            if (top.second)
                Q.push(top);
        }
        cout << res << ' ';
    }
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}