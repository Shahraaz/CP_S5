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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    vector<int> degree(n), vis(n), par(n, -1), dist(n, -1);
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;

        degree[u]++;
        degree[v]++;

        adj[u].pb(v);
        adj[v].pb(u);
    }
    deque<int> Q;
    int param = 0, node = -1;
    ++k;
    for (size_t i = 0; i < n; i++)
        if (degree[i] == 1)
        {
            Q.pb(i);
            vis[i] = 1;
        }
    while (Q.size())
    {
        deque<int> P;
        for (auto &x : Q)
            for (auto &y : adj[x])
                if (!vis[y])
                {
                    if (dist[y] == -1)
                        dist[y] = dist[x] + 1;
                    else if (dist[y] != (dist[x] + 1))
                    {
                        cout << "No\n";
                        return;
                    }

                    degree[y]--;
                    if (degree[y] == 1)
                    {
                        vis[y] = 1;
                        P.pb(y);
                    }
                }
        db(Q, P);
        int d = -1;
        for (auto &x : P)
        {
            if (d == -1)
                d = dist[x];
            else if (d != dist[x])
            {
                cout << "No\n";
                return;
            }
            int cnt = 0, cnt2 = 0;
            for (auto &y : adj[x])
            {
                if (vis[y])
                {
                    cnt++;
                    db(x, y, par[y]);
                    if (par[y] == -1)
                        par[y] = x;
                    else
                    {
                        if (node == -1)
                            node = y;
                        else if (node != y)
                        {
                            cout << "No\n";
                            return;
                        }
                    }
                }
                else
                    cnt2++;
            } // db(adj[x]);
            db(x, cnt, cnt2, adj[x]);
            db(cnt, cnt2);
            if (cnt < 3 || cnt2 > 1)
            {
                cout << "No\n";
                return;
            }
            if (cnt2 == 0)
            {
                if (node == -1)
                    node = x;
                else if (node != x)
                {
                    cout << "No\n";
                    return;
                }
            }
        }
        Q = P;
        ++param;
    }
    db(param, k);
    if (param == k && node != -1)
        cout << "Yes\n";
    else
        cout << "No\n";
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