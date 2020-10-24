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

void solveCase()
{
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    --a, --b;
    vector<int> adj[n];
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<int> comp(n);
    function<void(int, int)> dfs_comp = [&](int node, int id) -> void {
        comp[node] = id;
        for (auto &x : adj[node])
            if (x != a && comp[x] == 0)
                dfs_comp(x, id);
    };
    int comp_cnt = 0;
    for (size_t i = 0; i < n; i++)
        if (i != a && comp[i] == 0)
            dfs_comp(i, ++comp_cnt);
    db(comp);
    vector<int> vis(n);
    function<void(int)> dfs = [&](int node) -> void {
        if (vis[node])
            return;
        vis[node] = 1;
        for (auto &x : adj[node])
            if (x != b && vis[x] == 0)
                dfs(x);
    };
    dfs(a);
    db(vis);
    ll cnt1 = 0, cnt2 = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (i != a && comp[i] != comp[b])
            cnt1++;
        if (i != b && comp[i] == comp[b] && !vis[i])
            cnt2++;
    }
    cout << cnt1 * cnt2 << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
