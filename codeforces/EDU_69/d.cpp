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
const int NAX = 3e5 + 5, MOD = 1000000007;

ll n, m, k;
int a[NAX];
ll pref[NAX];
ll dp[NAX][12];

void solveCase()
{
    cin >> n >> m >> k;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            dp[i][j] = -1e7;

        cin >> a[i];
        pref[i] = a[i];
        if (i > 0)
            pref[i] += pref[i - 1];
    }
    // memset(dp, -1, sizeof dp);
    auto rangeSum = [&](int l, int r) -> ll {
        return pref[r] - (l > 0 ? pref[l - 1] : 0);
    };
    ll res = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int rem = m - 1; rem >= 0; rem--)
        {
            int rptr = i + rem;
            if (rptr >= n)
                continue;
            dp[i][(rem + 1) % m] = rangeSum(i, rptr) - k;
        }
        for (int rem = m - 1; rem >= 0; rem--)
        {
            int rptr = i + m;
            if (rptr >= n)
                continue;
            auto temp = rangeSum(i, rptr - 1) + dp[i + m][rem] - k;
            dp[i][rem] = max(dp[i][rem], temp);
        }
        // #ifdef LOCAL
        db(i);
        for (size_t j = 0; j < m; j++)
        {
            // cout << dp[i][j] << ' ';
            res = max(res, dp[i][j]);
        } // cout << '\n';
          // #endif
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
        solveCase();
    return 0;
}