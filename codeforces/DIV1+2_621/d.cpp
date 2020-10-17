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

int n, m, k;
vector<int> adj[NAX];
int isSpecial[NAX];

void solveCase()
{
    cin >> n >> m >> k;
    for (size_t i = 0; i < k; i++)
    {
        int x;
        cin >> x;
        --x;
        isSpecial[x] = 1;
    }
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    auto dj = [&](int src, int dest) -> vector<int> {
        vector<int> dist(n, MOD);
        dist[src] = 0;
        queue<int> Q;
        Q.push(src);
        while (Q.size())
        {
            auto top = Q.front();
            // db(top);
            Q.pop();
            for (auto &x : adj[top])
                if (dist[x] == MOD)
                {
                    dist[x] = dist[top] + 1;
                    Q.push(x);
                }
        }
        return dist;
    };
    auto from1 = dj(0, n - 1);
    auto fromn = dj(n - 1, 0);
    db(from1);
    db(fromn);
    set<pair<int, int>> s;
    vector<int> vecc[n];
    for (size_t i = 0; i < n; i++)
    {
        // db(i, isSpecial[i]);
        if (isSpecial[i])
        {
            s.insert({fromn[i], i});
            vecc[from1[i]].pb(i);
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        if (vecc[i].empty())
            continue;
        db(s);
        db(i, vecc[i]);
        for (auto &x : vecc[i])
        {
            s.erase({fromn[x], x});
            if (s.size())
            {
                auto last = *(--s.end());
                res = max(res, 1 + last.f + i);
            }
        }
        db(s);
    }
    if (res > from1[n - 1])
        res = from1[n - 1];
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
