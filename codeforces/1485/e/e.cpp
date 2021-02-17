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
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<ll> level(n), dist(n), curr(n), dp(n), vis(n), par(n);
    vector<vector<int>> on_single_level(n);
    for (size_t i = 1; i < n; i++)
    {
        int p;
        cin >> p;
        --p;
        adj[p].pb(i);
        adj[i].pb(p);
        // level[i] = level[p] + 1;
        // db(i, level[i]);
        // on_single_level[level[i]].pb(i);
    }
    queue<int> Q;
    Q.push(0);
    vis[0] = 1;
    while (Q.size())
    {
        auto top = Q.front();
        on_single_level[level[top]].pb(top);
        Q.pop();
        for (auto &x : adj[top])
            if (!vis[x])
            {
                vis[x] = 1;
                par[x] = top;
                level[x] = level[top] + 1;
                Q.push(x);
            }
    }

    on_single_level[0].pb(0);
    for (size_t i = 1; i < n; i++)
        cin >> curr[i];
    for (int i = 1; i < n; i++)
    {
        if (on_single_level[i].empty())
            continue;
        db(i, on_single_level[i]);
        vector<pair<int, int>> order;
        for (auto &x : on_single_level[i])
            order.pb({curr[x], x});
        sort(all(order));
        set<pair<ll, int>> left, right;
        for (auto &x : order)
        {
            int c = x.first;
            int idx = x.second;
            dp[idx] = max({dp[idx], dp[par[idx]] + abs(c - order.front().first), dp[par[idx]] + abs(c - order.back().first)});
            right.insert(make_pair(dp[par[idx]] + curr[idx], idx));
        }
        for (auto &x : order)
        {
            int c = x.first;
            int idx = x.second;
            right.erase(make_pair(dp[par[idx]] + curr[idx], idx));
            if (right.size())
                dp[idx] = max({dp[idx], (right.rbegin())->first - curr[idx]});
            if (left.size())
                dp[idx] = max({dp[idx], (left.rbegin())->first + curr[idx]});
            left.insert(make_pair(dp[par[idx]] - curr[idx], idx));
            db(idx, dp[idx]);
        }
    }
    // cout << dp[0] << '\n';
    ll res = 0;
    for (size_t i = 0; i < n; i++)
        res = max(res, dp[i]);
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
        solveCase();
    return 0;
}