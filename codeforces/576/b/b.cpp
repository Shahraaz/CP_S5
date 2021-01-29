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
    vector<int> p(n);
    vector<vector<int>> adj(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> p[i];
        --p[i];
        if (i != p[i])
        {
            adj[i].pb(p[i]);
            adj[p[i]].pb(i);
        }
    }
    vector<int> vis(n);
    vector<pair<int, int>> edges;
    function<int(int, int)> dfs = [&](int node, int par) -> int {
        for (auto &x : adj[node])
            if (x != par)
            {
                if (!vis[x])
                {
                    vis[x] = 1;
                    edges.pb({x, node});
                    // edges.pb({p[x], p[node]});
                    dfs(x, node);
                }
                else
                    return false;
            }
        return true;
    };
    int node = -1;
    for (size_t i = 0; i < n; i++)
    {
        if (vis[i])
            continue;
        vis[i] = 1;
        if (dfs(i, i))
        {
            node = i;
            break;
        }
        edges.clear();
    }
    if (node == -1)
    {
        cout << "NO\n";
        return;
    }
    fill(all(vis), false);
    dfs(node, node);
    for (size_t i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            vis[i] = 1;

            
        }
    }
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