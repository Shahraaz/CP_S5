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
const int NAX = 1e5 + 5, MOD = 1000000007;

vector<pair<int, int>> adj[NAX];

void solveCase()
{
    int n;
    cin >> n;
    vector<pair<pair<int, int>, ll>> edges;
    for (size_t i = 0; i + 1 < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        edges.pb({{u, v}, w});
        adj[u].pb({v, i});
        adj[v].pb({u, i});
    }
    ll best = LLONG_MAX;
    for (size_t i = 0; i + 1 < n; i++)
    {
        int src1 = edges[i].first.first;
        int src2 = edges[i].first.second;
        vector<int> sz1(n);
        vector<ll> dp1(n);

        function<void(int, int)> dfs = [&](int node, int par) -> void
        {
            sz1[node]++;
            for (auto &x : adj[node])
            {
                if (x.first == par)
                    continue;
                if (x.second == i)
                    continue;
                dfs(x.first, node);
                sz1[node] += sz1[x.first];
                dp1[node] += dp1[x.first] + edges[x.second].second * sz1[x.first] * (n - sz1[x.first]);
            }
        };
        dfs(src1, src1);
        dfs(src2, src2);

        function<ll(int, int)> dfs_reroot = [&](int node, int par) -> ll
        {
            ll best = dp1[node];
            auto sz_node = sz1[node];
            auto dp_node = dp1[node];

            for (auto &x : adj[node])
            {
                if (x.first == par)
                    continue;
                if (x.second == i)
                    continue;
                auto sz_x = sz1[x.first];
                auto dp_x = dp1[x.first];

                dp1[node] -= dp1[x.first];
                dp1[node] -= edges[x.second].second * sz1[x.first] * (n - sz1[x.first]);
                sz1[node] -= sz1[x.first];

                sz1[x.first] += sz1[node];
                dp1[x.first] += dp1[node];
                dp1[x.first] += edges[x.second].second * sz1[node] * (n - sz1[node]);

                best = min(best, dfs_reroot(x.first, node));

                sz1[x.first] = sz_x;
                dp1[x.first] = dp_x;
                sz1[node] = sz_node;
                dp1[node] = dp_node;
            }
            return best;
        };
        auto a = dfs_reroot(src1, src1);
        auto b = dfs_reroot(src2, src2);
        best = min(best, a + b + edges[i].second * sz1[src1] * sz1[src2]);
    }
    cout << best << '\n';
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