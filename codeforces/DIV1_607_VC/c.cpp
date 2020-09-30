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
    int k;
    cin >> k;
    int n = 2 * k;
    vector<vector<pair<ll, ll>>> adj(n);
    for (size_t i = 1; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    vector<int> order;
    vector<int> vis(n, 0);
    queue<int> Q;
    Q.push(0);
    vis[0] = true;
    while (Q.size())
    {
        auto top = Q.front();
        Q.pop();
        order.pb(top);
        for (auto &x : adj[top])
            if (!vis[x.f])
            {
                vis[x.f] = 1;
                Q.push(x.f);
            }
    }
    reverse(all(order));
    vector<int> sizes(n);
    fill(all(vis), 0);
    for (auto &x : order)
    {
        sizes[x] = 1;
        vis[x] = 1;
        for (auto &y : adj[x])
            if (vis[y.f])
                sizes[x] += sizes[y.f];
    }
    ll mini = 0, maxi = 0;
    for (size_t i = 0; i < n; i++)
        for (auto &y : adj[i])
        {
            if (i > y.f)
                continue;
            int mimi = min(sizes[i], sizes[y.f]);
            if (mimi & 1)
                mini += y.s;
            db(mimi, n - mimi, i, y);
            maxi += min(n - mimi, mimi) * 1LL * y.s;
        }
    cout << mini << ' ' << maxi << '\n';
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
