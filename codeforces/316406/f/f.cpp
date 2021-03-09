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
    ll n, k, d;
    cin >> n >> k >> d;
    vector<ll> a(n);
    for (auto &x : a)
        cin >> x;
    sort(all(a));
    vector<ll> cntRight(3 * n + 2), dp(3 * n + 2);
    cntRight[n - 1] = 1;
    dp[n] = 1;
    int rptr = n - 1;
    for (int i = n - 1; i >= 0; i--)
    {
        cntRight[i] = dp[i + 1] + cntRight[i + 1];
        while (rptr > i)
        {
            auto diff = abs(a[rptr] - a[i]);
            if (diff <= d)
                break;
            --rptr;
        }
        int rrptr = i + k - 1;
        if (rrptr <= rptr)
        {
            ll diff = cntRight[rrptr] - cntRight[rptr + 1];
            if (diff > 0)
                dp[i] = 1;
        }
        db(i, rptr, rrptr, dp[i]);
    }
    if (dp[0])
        cout << "YES\n";
    else
        cout << "NO\n";
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