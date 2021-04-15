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
const int NAX = 101 + 5, MOD = 1000000007;

// int dp[NAX][NAX][2];
// int dp_prev[NAX][NAX][2];

void solveCase()
{
    int n, k;
    cin >> n >> k;
    db(n, k);
    vector<vector<int>> adj(n);
    vector<int> dist(n, MOD), par(n, -1);
    dist[0] = 1;
    for (size_t i = 1; i < n; i++)
    {
        int p;
        cin >> p;
        --p;
        par[i] = p;
        adj[p].pb(i);
        dist[i] = dist[p] + 1;
        db(i, dist[i]);
    }
    int res = MOD;
    vector<int> path;
    for (int i = 0; i < n; i++)
    {
        int k1 = k - dist[i];
        int node = i;
        set<int> ss;
        while (node != -1)
        {
            ss.insert(node);
            node = par[node];
        }
        vector<int> path1;
        function<void(int)> dfs = [&](int node) -> void {
            if (node == i)
            {
                path1.pb(node);
                return;
            }
            if (ss.count(node) == 0)
            {
                if (k1 <= 0)
                    return;
                --k1;
            }
            path1.pb(node);
            for (auto &x : adj[node])
                if (k1 > 0 && ss.count(x) == 0)
                {
                    dfs(x);
                    path1.pb(node);
                }
            for (auto &x : adj[node])
                if (ss.count(x))
                    dfs(x);
        };
        dfs(0);
        db(i, k1, path1);
        if (k1 <= 0)
            if (res > path1.size())
            {
                res = path1.size();
                path = path1;
            }
    }
    cout << res - 1 << '\n';
    for (auto &x : path)
        cout << x + 1 << ' ';
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