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

const int NAX = 500 + 5, MOD = 1000000007;
int n, m, k;
vector<int> vecc[NAX];
// int k;

void solveCase()
{
    cin >> n >> m >> k;
    string str;
    vector<int> dp(501, MOD);
    dp[0] = 0;
    for (size_t i = 0; i < n; i++)
    {
        cin >> str;
        db(i);
        vector<int> curr(m + 1, MOD);
        vector<int> dp_next(501, MOD);
        int die = 0;
        for (int l = 0; l < m; l++)
        {
            int cur = die;
            for (int r = m - 1; r >= l; r--)
            {
                curr[cur] = min(curr[cur], r - l + 1);
                cur += (str[r] == '1');
            }
            die += (str[l] == '1');
        }
        curr[die] = 0;
        for (size_t j = 0; j <= k; j++)
            for (size_t x = 0; x + j <= k && x <= m; x++)
                dp_next[j + x] = min(dp_next[j + x], dp[j] + curr[x]);
        dp.swap(dp_next);
    }
    int res = MOD;
    for (size_t i = 0; i <= k; i++)
        res = min(res, dp[i]);
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
