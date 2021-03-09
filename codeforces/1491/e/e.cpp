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
#define int ll

const int NAX = 2e5 + 5, MOD = 1000000007;

int n;
vector<pair<int, int>> adj[NAX];
vector<int> fib;
int sz[NAX];

pair<int, int> partition(int node, int par, int idx)
{
    sz[node] = 1;
    pair<int, int> ret(-1, -1);
    for (auto &x : adj[node])
        if (x.first != par && x.second)
        {
            auto now = partition(x.first, node, idx);
            sz[node] += sz[x.first];
            ret = max(ret, now);
        }
    if (sz[node] == fib[idx])
    {
        ret.first = node;
        ret.second = par;
    }
    if (idx > 0 && sz[node] == fib[idx - 1])
    {
        ret.first = node;
        ret.second = par;
    }
    return ret;
}

bool dfs(int node, int par, int idx)
{
    db(node, par, idx, sz[node]);
    if (idx <= 1)
        return true;
    auto p = partition(node, par, idx - 1);
    db(node, par, idx, p);
    if (p.first == -1)
        return false;
    int c = p.first, c_par = p.second;
    for (auto &x : adj[c])
        if (x.first == c_par)
            x.second = 0;
    for (auto &x : adj[c_par])
        if (x.first == c)
            x.second = 0;
    int c_idx = -1, node_idx = -1;
    if (fib[idx - 1] == sz[c])
    {
        c_idx = idx - 1;
        node_idx = idx - 2;
    }
    else
    {
        c_idx = idx - 2;
        node_idx = idx - 1;
    }
    return dfs(node, par, node_idx) && dfs(c, c_par, c_idx);
}

void solveCase()
{
    cin >> n;
    {
        int prev = 1, curr = 1;
        fib.pb(1);
        fib.pb(1);
        while ((curr + prev) <= n)
        {
            auto next = curr + prev;
            fib.pb(next);
            prev = curr;
            curr = next;
        }
    }
    db(n, fib);
    int k = fib.size() - 1;
    if (n != fib[k])
    {
        cout << "NO\n";
        return;
    }
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb({v, 1});
        adj[v].pb({u, 1});
    }
    if (dfs(0, 0, k))
        cout << "YES\n";
    else
        cout << "NO\n";
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