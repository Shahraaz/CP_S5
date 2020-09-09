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

const int NAX = 1000 + 5, MOD = 1000000007;

int n, a1, a2, a3, a4;
int dp[NAX][1 << 12];
string g[4];

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    auto get = [&](int idx) -> int {
        int mask = 0;
        for (size_t i = 0; i < 3; i++)
            if (idx + i < n)
                for (size_t j = 0; j < 4; j++)
                    if (g[j][idx + i] == '.')
                        mask |= 1 << (j + 4 * i);
        return mask;
    };
    int ans = MOD;

    auto process = [&](int col, int curr) {
        if (dp[col][curr] == MOD)
            return;
        if (col == n)
        {
            ans = min(ans, dp[col][curr]);
            return;
        }
        if ((curr & 15) == 15)
        {
            dp[col + 1][(curr / 16) | get(col + 1)] = min(dp[col + 1][(curr / 16) | get(col + 1)], dp[col][curr]);
            return;
        }

        for (size_t i = 0; i < 4; i++)
        {
            int CUR = curr | (1 << i);
            dp[col][CUR] = min(dp[col][CUR], dp[col][curr] + a1);
        }

        for (size_t i = 0; i < 3; i++)
        {
            int CUR = curr;
            for (size_t j = 0; j < 2; j++)
                for (size_t k = 0; k < 2; k++)
                    CUR |= 1 << (i + j + 4 * k);
            dp[col][CUR] = min(dp[col][CUR], dp[col][curr] + a2);
        }

        for (size_t i = 0; i < 2; i++)
        {
            int CUR = curr;
            for (size_t j = 0; j < 3; j++)
                for (size_t k = 0; k < 3; k++)
                    CUR |= 1 << (i + j + 4 * k);
            dp[col][CUR] = min(dp[col][CUR], dp[col][curr] + a3);
        }

        if (col + 4 >= n)
            ans = min(ans, dp[col][curr] + a4);
        else
            dp[col + 4][get(col + 4)] = min(dp[col + 4][get(col + 4)], dp[col][curr] + a4);
    };

    cin >> n >> a1 >> a2 >> a3 >> a4;
    for (size_t i = 0; i < 4; i++)
        cin >> g[i];
    for (size_t i = 0; i < NAX; i++)
        for (int j = (1 << 12) - 1; j >= 0; j--)
            dp[i][j] = MOD;
    dp[0][get(0)] = 0;
    for (size_t i = 0; i < n + 1; i++)
        for (int j = 0; j < (1 << 12); j++)
            process(i, j);
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
