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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> ind(n);
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> v >> u;
        --u, --v;
        adj[u].pb(v);
        // adj[u].pb(v);
        ind[v]++;
    }
    priority_queue<int> Q;
    for (size_t i = 0; i < n; i++)
        if (ind[i] == 0)
            Q.push(i);
    vector<int> res(n);
    int idx = n;
    while (Q.size())
    {
        auto top = Q.top();
        Q.pop();
        res[top] = idx--;
        for (auto &x : adj[top])
        {
            ind[x]--;
            if (ind[x] == 0)
                Q.push(x);
        }
    }
    for (auto &x : res)
        cout << x << ' ';
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