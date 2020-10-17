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

const int NAX = 2000 + 5, MOD = 1000000007;

const ll INF = 1e18;
ll dp[NAX];
ll a[NAX], l[NAX], r[NAX];
ll n, k;

void solveCase()
{
    cin >> n >> k;
    for (size_t i = 0; i < n; i++)
        cin >> l[i] >> r[i] >> a[i];
    for (size_t i = 0; i < NAX; i++)
        dp[i] = INF;
    dp[0] = 0;
    for (size_t i = 0; i < n; i++)
    {
        ll rem = k, total = dp[i];
        if (total >= INF)
            continue;
        for (size_t j = i; j < n; j++)
        {
            ll cntReload = (max(0LL, a[j] - rem) + k - 1) / k;
            if (cntReload > r[j] - l[j])
                break;
            ll newRem = rem + cntReload * k - a[j];
            total += a[j];
            if (j + 1 < n)
            {
                if (l[j] + cntReload < l[j + 1])
                    dp[j + 1] = min(dp[j + 1], total + newRem);
            }
            else
                dp[j + 1] = min(dp[j + 1], total);
            rem = newRem;
        }
    }
    if (dp[n] >= INF)
        dp[n] = -1;
    cout << dp[n] << '\n';
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
