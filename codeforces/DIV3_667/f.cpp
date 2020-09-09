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

const int NAX = 200 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

int dp[NAX][NAX][NAX];

void Solution::solveCase()
{
    int n, k;
    cin >> n >> k;
    string s, t;
    cin >> s >> t;
    for (size_t i = 0; i < NAX; i++)
        for (size_t j = 0; j < NAX; j++)
            for (size_t k = 0; k < NAX; k++)
                dp[i][j][k] = -MOD;
    auto self_max = [](int &a, int b) {
        a = max(a, b);
    };
    dp[0][0][0] = 0;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j <= k; j++)
            for (size_t cnt0 = 0; cnt0 <= n; cnt0++)
            {
                if (dp[i][j][cnt0] == -MOD)
                    continue;
                db(i, j, cnt0, dp[i][j][cnt0]);
                int e0 = s[i] == t[0];
                int e1 = s[i] == t[1];
                int e01 = t[0] == t[1];
                self_max(dp[i + 1][j][cnt0 + e0], dp[i][j][cnt0] + (e1 ? cnt0 : 0));
                self_max(dp[i + 1][j + 1][cnt0 + 1], dp[i][j][cnt0] + (e01 ? cnt0 : 0));
                self_max(dp[i + 1][j + 1][cnt0 + e01], dp[i][j][cnt0] + cnt0);
            }
    int ans = 0;
    for (size_t j = 0; j <= k; j++)
        for (size_t cnt0 = 0; cnt0 <= n; cnt0++)
            ans = max(ans, dp[n][j][cnt0]);
    cout << ans << '\n';
}

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
