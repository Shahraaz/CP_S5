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
    vector<ll> b(n);
    for (auto &x : b)
        cin >> x;

    vector<ll> dp(n), b_sum = b;
    for (size_t i = 1; i < n; i++)
        b_sum[i] += b_sum[i - 1];

    map<ll, ll> b_sum_dp;
    dp[0] = 1;
    b_sum_dp[0] = 1;
    ll dp_sum = 1;
    for (size_t i = 1; i < n; i++)
    {
        dp[i] += dp_sum - b_sum_dp[b_sum[i - 1]];

        while (dp[i] >= MOD)
            dp[i] -= MOD;
        while (dp[i] < 0)
            dp[i] += MOD;

        db(i, dp[i]);
        dp_sum += dp[i];
        if (dp_sum >= MOD)
            dp_sum -= MOD;
        // while (dp_sum < 0)
        //     dp_sum += MOD;

        b_sum_dp[b_sum[i - 1]] += dp[i];
        if (b_sum_dp[b_sum[i - 1]] >= MOD)
            b_sum_dp[b_sum[i - 1]] -= MOD;
        // while (dp_sum < 0)
        //     dp_sum += MOD;
    }
    cout << dp_sum << '\n';
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