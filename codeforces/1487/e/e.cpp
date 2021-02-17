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
    vector<int> n(4);
    for (auto &x : n)
        cin >> x;
    vector<vector<ll>> costs(4);
    vector<vector<ll>> dp(4);
    for (size_t i = 0; i < 4; i++)
    {
        costs[i].resize(n[i]);
        dp[i].resize(n[i], -1);
        for (auto &x : costs[i])
            cin >> x;
    }
    dp[0] = vector<ll>(n[0], 0);
    for (size_t i = 1; i < 4; i++)
    {
        multiset<pair<ll, int>> myset;
        for (size_t j = 0; j < n[i - 1]; j++)
            if (dp[i - 1][j] != -1)
                myset.insert({costs[i - 1][j] + dp[i - 1][j], j});
        int m;
        cin >> m;
        vector<vector<int>> lhs(n[i]);
        for (size_t i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            --a, --b;
            lhs[b].pb(a);
        }
        for (size_t j = 0; j < lhs.size(); j++)
        {
            for (auto &x : lhs[j])
                if (dp[i - 1][x] != -1)
                    myset.erase({costs[i - 1][x] + dp[i - 1][x], x});
            if (myset.size())
            {
                auto mini = *myset.begin();
                dp[i][j] = mini.first;
            }
            for (auto &x : lhs[j])
                if (dp[i - 1][x] != -1)
                    myset.insert({costs[i - 1][x] + dp[i - 1][x], x});
        }
        db(i, dp[i]);
    }
    ll res = LLONG_MAX;
    for (size_t j = 0; j < n[3]; j++)
        if (dp[3][j] != -1)
            res = min(res, dp[3][j] + costs[3][j]);
    if(res == LLONG_MAX)
        res = -1;
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
        solveCase();
    return 0;
}