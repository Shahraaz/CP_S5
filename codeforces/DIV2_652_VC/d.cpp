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

const int NAX = 2e6 + 5, MOD = 1000000007;

ll dp[NAX];

void pre()
{
    dp[3] = dp[4] = 4;
    for (size_t i = 5; i < NAX; i++)
    {
        if (i % 3)
        {
            dp[i] = dp[i - 1] + 2 * dp[i - 2];
            dp[i] %= MOD;
        }
        else
        {
            dp[i] = 4 + dp[i - 2] + 4 * dp[i - 3] + 4 * dp[i - 4];
            dp[i] %= MOD;
        }
        // db(i, dp[i]);
        // db(dp[i - 1] + 2 * dp[i - 2]);
        // db(4 + dp[i - 2] + 4 * dp[i - 3] + 4 * dp[i - 4]);
        // dp[i] = max(dp[i - 1] + 2 * dp[i - 2], 4 + dp[i - 2] + 4 * dp[i - 3] + 4 * dp[i - 4]);
        // if (dp[i] != max(dp[i - 1] + 2 * dp[i - 2], 4 + dp[i - 2] + 4 * dp[i - 3] + 4 * dp[i - 4]))
        // {
        //     // db(max(dp[i - 1] + 2 * dp[i - 2], 4 + dp[i - 2] + 4 * dp[i - 3] + 4 * dp[i - 4]));
        //     // db(dp[i - 1] + 2 * dp[i - 2], 4 + dp[i - 2] + 4 * dp[i - 3] + 4 * dp[i - 4]);
        //     db(i);
        //     exit(0);
        // }
    }
    // exit(0);
}

void solveCase()
{
    int n;
    cin >> n;
    cout << dp[n] << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    pre();
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
