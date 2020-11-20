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
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n);
    vector<vector<pair<int, int>>> ch(n);
    vector<int> degree(n);
    vector<int> mark(n);
    vector<int> can(n);
    vector<int> ans(n);
    vector<int> ct(n), A;
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        degree[u]++;
        degree[v]++;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    if (k * (k - 1LL) > 2 * m)
    {
        cout << -1 << '\n';
        return;
    }
    set<pair<int, int>> Q;
    for (size_t i = 0; i < n; i++)
        Q.insert({degree[i], i});
    int cnt = 1;
    while (Q.size())
    {
        auto it = *Q.begin();
        // db(Q);
        if (it.first >= k)
        {
            cout << 1 << '\n';
            cout << Q.size() << '\n';
            for (auto &x : Q)
                cout << x.second + 1 << ' ';
            cout << '\n';
            return;
        }
        else
        {
            Q.erase(it);
            mark[it.second] = cnt++;
            A.pb(it.second);
            for (auto &u : adj[it.second])
                if (!mark[u])
                {
                    Q.erase({degree[u], u});
                    Q.insert({--degree[u], u});
                }
        }
    }
    for (auto &i : A)
    {
        int nxt = 0;
        db(i, adj[i], ch[i]);
        for (auto &u : adj[i])
            if (mark[u] > mark[i])
                ct[nxt++] = u, can[u] = 1;
        for (auto &u : ch[i])
            if (!can[u.first])
                ans[u.second] = false;
        for (size_t j = 0; j < nxt; j++)
            can[ct[j]] = false;
        if (nxt != k - 1)
            continue;
        ans[i] = true;
        sort(ct.begin(), ct.begin() + nxt, [&](int u, int v) -> bool {
            return mark[u] < mark[v];
        });
        for (size_t j = 0; j < nxt; j++)
            for (size_t k = j + 1; k < nxt; k++)
                ch[ct[j]].pb({ct[k], i});
    }
    for (auto &i : A)
    {
        if (!ans[i])
            continue;
        cout << 2 << '\n';
        cout << i + 1 << ' ';
        for (auto &v : adj[i])
            if (mark[v] > mark[i])
                cout << v + 1 << ' ';
        cout << '\n';
        return;
    }
    cout << -1 << '\n';
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
        solveCase();
    return 0;
}