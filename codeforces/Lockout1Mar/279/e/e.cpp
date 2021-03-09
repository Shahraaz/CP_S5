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
    string str;
    cin >> str;
    int n = str.size();
    vector<int> dp(2, 0);
    dp[0] = str.back() == '1';
    dp[1] = 1;
    for (int i = n - 2; i >= 0; i--)
    {
        vector<int> next_dp(2, 0);
        int is_one = str[i] == '1';
        next_dp[1] = min(!is_one + dp[1], 1 + dp[0]);
        next_dp[0] = min(is_one + dp[0], 1 + next_dp[1]);
        db(i, str[i], dp, next_dp);
        dp = next_dp;
    }
    cout << min(dp[0], 1 + dp[1]) << '\n';
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