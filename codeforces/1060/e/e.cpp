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

ll res = 0;

vector<int> adj[NAX];
int n;
ll dp[NAX], sz[NAX], dpg[NAX];

void dfs(int node, int par)
{
    sz[node] = 1;
    for (auto &x : adj[node])
        if (x != par)
        {
            dfs(x, node);
            sz[node] += sz[x];
            if (par != -1)
                dpg[par] += sz[x] + dp[x];
            dp[node] += 1;
        }
    dp[node] += dpg[node];
    db("dfs", node, par, sz[node], dp[node], dpg[node]);
}

void dfs_reroot(int node, int par)
{
    res += dp[node];

    ll sumdpg = 0;

    for (auto &x : adj[node])
        sumdpg += sz[x] + dp[x];
    for (auto &x : adj[node])
        if (x != par)
        {
        }
}

void solveCase()
{
    cin >> n;
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(0, -1);
    dfs_reroot(0, 0);
    cout << res << '\n';
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