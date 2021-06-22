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

vector<int> adj[NAX];
int sz[NAX], clr[NAX], isgood[NAX], cnt[NAX];

void dfs(int node, int par)
{
    sz[node]++;
    cnt[clr[node]]++;
    // st[node] = tt++;
    isgood[node] = 1;
    for (auto &x : adj[node])
    {
        if (x == par)
            continue;
        dfs(x, node);
        sz[node] += sz[x];
        if ((clr[node] == clr[x]) && isgood[x])
            continue;
        else
            isgood[node] = false;
    }
    db(node, isgood[node], sz[node]);
    // en[node] = tt;
}

int n;

void dfs2(int node, int par)
{
    bool ok = true;
    for (auto &x : adj[node])
    {
        if (x == par)
            continue;
        ok = ok && isgood[x];
    }
    if (ok)
    {
        if (par == node)
        {
            cout << "YES\n"
                 << node + 1 << '\n';
            exit(0);
        }
        int rem = n - sz[node];
        cnt[clr[node]]--;
        for (auto &x : adj[node])
        {
            if (x == par)
                continue;
            cnt[clr[x]] -= sz[x];
        }
        if (cnt[clr[par]] == rem)
        {
            cout << "YES\n"
                 << node + 1 << '\n';
            exit(0);
        }
        cnt[clr[node]]++;
        for (auto &x : adj[node])
        {
            if (x == par)
                continue;
            cnt[clr[x]] += sz[x];
        }
    }
    for (auto &x : adj[node])
    {
        if (x == par)
            continue;
        dfs2(x, node);
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
    for (size_t i = 0; i < n; i++)
        cin >> clr[i];
    dfs(0, 0);
    dfs2(0, 0);
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