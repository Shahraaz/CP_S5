#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    long long res = 0;
    vector<long long> sz(n), dp(n);
    function<void(int, int)> dfs = [&](int node, int par) -> void {
        sz[node] = 1;
        for (auto &x : adj[node])
        {
            if (x == par)
                continue;
            dfs(x, node);
            sz[node] += sz[x];
            dp[node] += dp[x];
        }
        dp[node] += sz[node];
        db(node, dp[node], sz[node]);
    };
    dfs(0, 0);
    function<void(int, int)> dfs2 = [&](int node, int par) -> void {
        db(node, dp[node], sz[node]);
        res = max(res, dp[node]);
        auto sz_node = sz[node];
        auto dp_node = dp[node];
        for (auto &x : adj[node])
        {
            if (x == par)
                continue;
            auto sz_x = sz[x];
            auto dp_x = dp[x];

            dp[node] -= dp[x];
            dp[node] -= sz[node];

            sz[node] -= sz[x];

            dp[node] += sz[node];

            dp[x] -= sz[x];

            sz[x] = n;

            dp[x] += sz[x];
            dp[x] += dp[node];

            dfs2(x, node);

            dp[node] = dp_node;
            sz[node] = sz_node;

            sz[x] = sz_x;
            dp[x] = dp_x;
        }
    };
    dfs2(0, 0);
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