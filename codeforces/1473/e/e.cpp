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

vector<vector<pair<int, ll>>> adj(4 * NAX);

void solveCase()
{
    int n, m;
    cin >> n >> m;
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u, --v;

        adj[u].pb({v, w});
        adj[v].pb({u, w});

        adj[u + n].pb({v + n, w});
        adj[v + n].pb({u + n, w});

        adj[u + 2 * n].pb({v + 2 * n, w});
        adj[v + 2 * n].pb({u + 2 * n, w});

        adj[u + 3 * n].pb({v + 3 * n, w});
        adj[v + 3 * n].pb({u + 3 * n, w});

        adj[u].pb({v + n, 0});
        adj[v].pb({u + n, 0});

        adj[u].pb({v + 2 * n, 2 * w});
        adj[v].pb({u + 2 * n, 2 * w});

        adj[u + n].pb({v + 3 * n, 2 * w});
        adj[v + n].pb({u + 3 * n, 2 * w});

        adj[u + 2 * n].pb({v + 3 * n, 0});
        adj[v + 2 * n].pb({u + 3 * n, 0});
    }
    // for (size_t i = 0; i < 3 * n; i++)
    // {
    //     db(i, adj[i]);
    // }

    const ll INF = 1e18;
    vector<ll> dist(4 * n, INF);
    vector<bool> vis(4 * n, false);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> Q;
    dist[0] = 0;
    // vis[0] = 1;
    Q.push({0, 0});
    while (Q.size())
    {
        auto top = Q.top();
        Q.pop();
        ll d = top.first;
        int node = top.second;
        if (vis[node])
            continue;
        vis[node] = 1;
        db(node, d);
        for (auto &c : adj[node])
            if (!vis[c.first] && (d + c.second) < dist[c.first])
            {
                dist[c.first] = d + c.second;
                Q.push({dist[c.first], c.first});
            }
    }
    db(dist);
    for (auto &x : adj[0])
    {
        if (x.first < n)
        {
            db(x.first + 3 * n);
            dist[x.first + 3 * n] = min(dist[x.first + 3 * n], x.second);
        }
    }
    for (size_t i = 1; i < n; i++)
        cout << dist[3 * n + i] << ' ';
    cout << '\n';
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