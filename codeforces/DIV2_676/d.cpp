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
    ll x, y;
    cin >> x >> y;
    map<ll, map<ll, ll>> dist;
    cin >> dist[1][1] >> dist[0][1] >> dist[-1][0];
    cin >> dist[-1][-1] >> dist[0][-1] >> dist[1][0];
    priority_queue<pair<ll, pair<int, int>>> Q;
    for (auto &x : dist)
        for (auto &y : x.s)
            Q.push({-y.s, {x.f, y.f}});
    dist[0][0] = 0;
    while (Q.size())
    {
        auto top = Q.top();
        Q.pop();
        top.f = -top.f;
        if (abs(top.s.f) > 3 || abs(top.s.s) > 3)
            continue;
        // db(top);
        if (top.f != dist[top.s.f][top.s.s])
            continue;
        for (auto x : {-1, 0, 1})
            for (auto y : {-1, 0, 1})
                if (dist[x].count(y))
                {
                    int x1 = top.s.f + x;
                    int y1 = top.s.s + y;
                    if (dist[x1].count(y1) == 0 || (top.f + dist[x][y]) < dist[x1][y1])
                    {
                        dist[x1][y1] = (top.f + dist[x][y]);
                        Q.push({-dist[x1][y1], {x1, y1}});
                    }
                }
    }
    ll res = LLONG_MAX;
    auto sign = [](ll x) -> int {
        return x != 0 ? abs(x) / x : 0;
    };
    res = min(res, abs(x) * dist[sign(x)][0] + abs(y) * dist[0][sign(y)]);
    if (abs(x) <= abs(y))
        res = min(res, abs(x) * dist[sign(x)][sign(y)] + (abs(y) - abs(x)) * dist[0][sign(y)]);
    if (abs(x) >= abs(y))
        res = min(res, abs(y) * dist[sign(x)][sign(y)] + (abs(x) - abs(y)) * dist[sign(x)][0]);
    cout << res << '\n';
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
