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
    vector<int> tag(n), s(n);
    vector<ll> dp(n);
    for (auto &x : tag)
        cin >> x;
    for (auto &x : s)
        cin >> x;
    for (size_t i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (tag[i] == tag[j])
                continue;
            ll dpi = dp[i], dpj = dp[j];
            dp[i] = max(dp[i], dpj + abs(s[i] - s[j]));
            dp[j] = max(dp[j], dpi + abs(s[i] - s[j]));
        }
    }
    cout << *max_element(all(dp)) << '\n';
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