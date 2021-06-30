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

int dp[NAX];

void solveCase()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> xs(n);
    for (size_t i = 0; i < n; i++)
        cin >> xs[i].first >> xs[i].second;
    dp[m] = 0;
    for (int i = m - 1; i >= 0; i--)
    {
        dp[i] = m - i;
        for (size_t j = 0; j < n; j++)
        {
            int l = max(0, xs[j].first - xs[j].second);
            int r = min(m, xs[j].first + xs[j].second);
            if (l <= (i + 1) && (i + 1) <= r)
                dp[i] = min(dp[i], dp[i + 1]);
            if (i < l)
            {
                int cost = (l - i - 1);
                int rptr = min(m, r + cost);
                dp[i] = min(dp[i], cost + dp[rptr]);
            }
        }
    }
    cout << dp[0] << '\n';
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