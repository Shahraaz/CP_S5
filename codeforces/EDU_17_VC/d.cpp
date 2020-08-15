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

struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        vector<int> a[3];
        vector<ll> dp[3];
        for (size_t i = 0; i < 3; i++)
        {
            a[i].resize(n + 10);
            dp[i].resize(n + 10, -1e18);
            for (size_t j = 1; j <= n; j++)
                cin >> a[i][j];
        }
        dp[0][1] = a[0][1];
        dp[1][1] = a[1][1] + a[0][1];
        dp[2][1] = dp[1][1] + a[2][1];
        auto self_max = [](ll &a, ll b) -> void {
            a = max(a, b);
        };
        for (size_t j = 1; j <= n; j++)
        {
            self_max(dp[0][j + 1], dp[0][j] + a[0][j + 1]);
            self_max(dp[0][j + 1], dp[1][j] + a[0][j + 1] + a[1][j + 1]);
            self_max(dp[0][j + 1], dp[2][j] + a[0][j + 1] + a[1][j + 1] + a[2][j + 1]);

            self_max(dp[1][j + 1], dp[1][j] + a[1][j + 1]);
            self_max(dp[1][j + 1], dp[0][j] + a[0][j + 1] + a[1][j + 1]);
            self_max(dp[1][j + 1], dp[2][j] + a[2][j + 1] + a[1][j + 1]);

            self_max(dp[2][j + 1], dp[2][j] + a[2][j + 1]);
            self_max(dp[2][j + 1], dp[1][j] + a[2][j + 1] + a[1][j + 1]);
            self_max(dp[2][j + 1], dp[0][j] + a[0][j + 1] + a[1][j + 1] + a[2][j + 1]);


        }
        cout << dp[2][n] << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
