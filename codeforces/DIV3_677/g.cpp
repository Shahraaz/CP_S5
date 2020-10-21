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

#define int ll

const int NAX = 1000 + 5, MOD = 1000000007;
int n, m, k;
vector<pair<int, int>> adj[NAX];
int dist[NAX][NAX];

void comp(int src)
{
    db(src);
    for (size_t i = 0; i < n; i++)
        dist[src][i + 1] = MOD;
    dist[src][src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
    Q.push({0, src});
    while (Q.size())
    {
        auto top = Q.top();
        db(top);
        Q.pop();
        if (top.f == dist[src][top.s])
            for (auto &x : adj[top.s])
                if (dist[src][x.f] > x.s + top.f)
                {
                    dist[src][x.f] = x.s + top.f;
                    Q.push({dist[src][x.f], x.f});
                }
    }
    db("~", src);
}

void solveCase()
{
    cin >> n >> m >> k;
    for (size_t i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    for (size_t i = 0; i < n; i++)
        comp(i + 1);
    db("a");
    ll res = 0;
    vector<pair<int, int>> routes(k);
    for (auto &x : routes)
    {
        cin >> x.f >> x.s;
        res += dist[x.f][x.s];
    }
    db("b");
    for (size_t i = 1; i <= n; i++)
        for (auto &x : adj[i])
        {
            ll tempRes = 0;
            db(i, x);
            for (auto &r : routes)
            {
                if (r.f == r.s)
                    continue;
                ll now = dist[r.f][r.s];
                ll next = dist[r.f][i] + dist[x.f][r.s];
                now = min(now, next);
                next = dist[r.f][x.f] + dist[i][r.s];
                now = min(now, next);
                tempRes += now;
            }
            res = min(res, tempRes);
        }
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
