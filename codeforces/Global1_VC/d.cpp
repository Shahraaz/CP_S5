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

const int NAX = 1e6, MOD = 1000000007;

int cnt[NAX + 5];
int dp[NAX + 5][3][3];
int n;

// int solve(int i, int t1, int t2)
// {
//     if (i > NAX)
//         return 0;
//     int &ret = dp[i][t1][t2];
//     if (ret >= 0)
//         return ret;
//     int now_i = cnt[i] - t1 - t2;
//     int now_i_plus_1 = cnt[i + 1] - t1 - t2;
//     int now_i_plus_2 = cnt[i + 2] - t2;
//     int lim = min({2, now_i_plus_1, now_i_plus_2, cnt[i + 3]});
//     ret = 0;
//     for (int t3 = 0; t3 <= lim; t3++)
//         ret = max(ret, (cnt[i + 1] - t3) / 3 + t3 + solve(i + 1, t2, t3));
//     return ret;
// }

void self_max(int &a, int b)
{
    a = max(a, b);
}

void solveCase()
{
    int m;
    cin >> n;
    cin >> m;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        cnt[x]++;
    }
    // cout << solve(0, 0, 0) << '\n';
    for (size_t i = 0; i <= m; i++)
        for (int t1 = 0; t1 <= 2; t1++)
            for (int t2 = 0; t2 <= 2; t2++)
            {
                int &ret = dp[i][t1][t2];
                // if (dp[i][t1][t2] > 0)
                //     cout << i << ' ' << t1 << ' ' << t2 << ' ' << ret << '\n';
                int now_i_plus_1 = cnt[i + 1] - t1 - t2;
                int now_i_plus_2 = cnt[i + 2] - t2;
                int lim = min({2, now_i_plus_1, now_i_plus_2, cnt[i + 3]});
                for (int t3 = 0; t3 <= lim; t3++)
                    self_max(dp[i + 1][t2][t3], (now_i_plus_1 - t3) / 3 + t3 + ret);
            }
    int res = 0;
    for (int t1 = 0; t1 <= 2; t1++)
        for (int t2 = 0; t2 <= 2; t2++)
            self_max(res, dp[m + 1][t1][t2]);
    cout << res << '\n';
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
