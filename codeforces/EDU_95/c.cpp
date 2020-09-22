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

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    a.pb(0);
    a.pb(0);
    vector<int> dp[2];
    dp[0] = vector<int>(n + 2, MOD);
    dp[1] = vector<int>(n + 2, MOD);
    dp[0][n] = dp[1][n] = 0;
    dp[0][n + 1] = dp[1][n + 1] = 0;
    const int ME = 0, OTHER = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        dp[ME][i] = min(dp[ME][i], dp[OTHER][i + 1]);
        dp[ME][i] = min(dp[ME][i], dp[OTHER][i + 2]);

        dp[OTHER][i] = min(dp[OTHER][i], a[i] + dp[ME][i + 1]);
        dp[OTHER][i] = min(dp[OTHER][i], a[i] + a[i + 1] + dp[ME][i + 2]);
    }
    cout << dp[OTHER][0] << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
