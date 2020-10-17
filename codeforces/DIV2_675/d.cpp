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
    int n, m;
    cin >> n >> m;
    n = m;
    pair<int, int> s, f;
    cin >> f.f >> f.s;
    cin >> s.f >> s.s;
    vector<pair<int, int>> vecc(n + 1);
    vector<pair<int, int>> xCord;
    vector<pair<int, int>> yCord;
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        vecc[i] = make_pair(x, y);
        xCord.emplace_back(x, i);
        yCord.emplace_back(y, i);
    }
    sort(all(xCord));
    sort(all(yCord));
    vector<pair<int, int>> adj[n + 2];
    ll dist = abs(f.f - s.f);
    dist += abs(f.s - s.s);

    adj[0].emplace_back(dist, n + 1);
    db(vecc);
    db(xCord);
    db(yCord);
    for (int i = 1; i <= n; i++)
    {
        int dist = abs(vecc[i].f - f.f);
        dist = min(dist, abs(vecc[i].s - f.s));

        db(i, dist, f, vecc[i]);
        adj[0].emplace_back(dist, i);

        dist = abs(vecc[i].f - s.f);
        dist += abs(vecc[i].s - s.s);

        db(i, dist, s, vecc[i]);
        adj[i].emplace_back(dist, n + 1);

        db(i, vecc[i]);
        auto it = lower_bound(all(xCord), make_pair(vecc[i].f, i));
        if (it != xCord.end())
        {
            auto neXt = next(it);
            if (neXt != xCord.end())
            {
                int j = neXt->s;
                int x = neXt->f;

                db("xCord next", j, x);
                adj[i].emplace_back(abs(x - vecc[i].f), j);
                // adj[j].emplace_back(abs(x - vecc[i].f), i);
            }
        }

        if (it != xCord.begin())
        {
            auto neXt = prev(it);
            int j = neXt->s;
            int x = neXt->f;

            db("xCord prev", j, x);
            adj[i].emplace_back(abs(x - vecc[i].f), j);
            // adj[j].emplace_back(abs(x - vecc[i].f), i);
        }

        it = lower_bound(all(yCord), make_pair(vecc[i].s, i));
        if (it != yCord.end())
        {
            auto neXt = next(it);
            if (neXt != yCord.end())
            {
                int j = neXt->s;
                int x = neXt->f;

                db("yCord next", j, x);
                adj[i].emplace_back(abs(x - vecc[i].s), j);
                // adj[j].emplace_back(abs(x - vecc[i].f), i);
            }
        }

        if (it != yCord.begin())
        {
            auto neXt = prev(it);
            int j = neXt->s;
            int x = neXt->f;

            db("yCord prev", j, x);
            adj[i].emplace_back(abs(x - vecc[i].s), j);
            // adj[j].emplace_back(abs(x - vecc[i].f), i);
        }
    }
    for (size_t i = 0; i <= n + 1; i++)
    {
        db(i, adj[i]);
    }

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> Q;
    vector<ll> Dist(n + 2, LLONG_MAX);
    Q.push({0, 0});
    Dist[0] = 0;
    while (Q.size())
    {
        auto top = Q.top();
        Q.pop();
        int idx = top.s;
        ll d = top.f;
        if (d != Dist[idx])
            continue;
        db(top);
        db(Dist);
        db(adj[idx]);
        for (auto &child : adj[idx])
        {
            db(child.s, Dist.size());
            if (child.f + d < Dist[child.s])
            {
                Dist[child.s] = child.f + d;
                Q.push({Dist[child.s], child.s});
            }
        }
    }
    cout << Dist[n + 1] << '\n';
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
