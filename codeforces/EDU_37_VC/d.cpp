// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

set<int> adj[NAX];
set<int> unvisited;

int dfs(int node)
{
    db(node);
    db(unvisited);
    int sz = 1;
    for (auto it = unvisited.begin(); it != unvisited.end();)
        if (adj[node].find(*it) == adj[node].end())
        {
            auto x = *it;
            unvisited.erase(x);
            sz += dfs(x);
            it = unvisited.lower_bound(x);
        }
        else
            ++it;
    return sz;
}

void solveCase()
{
    int n, m;
    cin >> n >> m;
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    vector<int> res;
    for (size_t i = 1; i <= n; i++)
        unvisited.insert(i);
    for (size_t i = 1; i <= n; i++)
        if (unvisited.find(i) != unvisited.end())
        {
            unvisited.erase(i);
            res.pb(dfs(i));
        }
    sort(all(res));
    cout << res.size() << '\n';
    for (auto &x : res)
        cout << x << ' ';
    cout << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
