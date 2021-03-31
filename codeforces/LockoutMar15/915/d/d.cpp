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
const int NAX = 500 + 5, MOD = 1000000007;

int n, m;
vector<pair<int, int>> adj[NAX];
pair<int, int> edges[100000 + 1];
int vis[NAX], prev_edge[NAX], in_degree[NAX], instack[NAX];

bool isdel[100000 + 1];
deque<int> cyc;

bool iscyclic(int node)
{
    if (!vis[node])
    {
        vis[node] = 1;
        instack[node] = 1;
        for (auto &x : adj[node])
            if (!isdel[x.second])
            {
                if (!vis[x.first] && iscyclic(x.first))
                {
                    cyc.pb(x.second);
                    return true;
                }
                else if (instack[x.first])
                {
                    cyc.pb(x.second);
                    return true;
                }
            }
    }
    instack[node] = false;
    return false;
}

pair<int, deque<int>> find_cycle()
{
    memset(vis, 0, sizeof vis);
    memset(prev_edge, -1, sizeof prev_edge);
    memset(instack, -1, sizeof instack);
    for (size_t i = 0; i < n; i++)
    {
        cyc.clear();
        if (iscyclic(i))
        {
            db(i, cyc);
            return {1, cyc};
        }
    }
    return {0, {}};
}

void do_it(deque<int> cycle)
{
    db(cycle);
    for (auto &x : cycle)
    {
        db(x, edges[x]);
        isdel[x] = 1;
        auto ret = find_cycle();
        if (!ret.first)
        {
            cout << "YES\n";
            return;
        }
        isdel[x] = 0;
    }
    cout << "NO\n";
}

void solveCase()
{
    cin >> n >> m;
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        edges[i] = {u, v};
        adj[u].pb({v, i});
        // adj[v].pb({u, i});
    }
    auto ret = find_cycle();
    db(ret);
    if (ret.first)
    {
        do_it(ret.second);
    }
    else
        cout << "YES\n";
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