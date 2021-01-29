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
const int NAX = 301, MOD = 1000000007;

vector<map<int, int>> number_line(NAX);
ll dp[NAX][2 * NAX];
bool isComputed[NAX][2 * NAX];

void solveCase()
{
    int n = 300, m = 1e5, k = 300;
    cin >> n >> m >> k;
    for (size_t i = 0; i < m; i++)
    {
        int l = 1, r = n, c = 1;
        cin >> l >> r >> c;
        --l, --r;
        for (size_t j = l; j <= r; j++)
        {
            auto it = number_line[j].find(r + 1);
            if (it == number_line[j].end() || it->second > c)
                number_line[j][r + 1] = c;
            // number_line[j].pb({r + 1, c});
        }
    }
    dp[n][0] = 0;
    isComputed[n][0] = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < k; j++)
        {
            if (isComputed[i + 1][j])
            {
                if (!isComputed[i][j])
                    dp[i][j] = dp[i + 1][j];
                else
                    dp[i][j] = min(dp[i][j], dp[i + 1][j]);
                isComputed[i][j] = 1;
            }
            for (auto &x : number_line[i])
            {
                int rptr = x.first;
                ll c = x.second;
                int new_cnt = j + (rptr - i);
                if (isComputed[rptr][j])
                {
                    ll cost = dp[rptr][j] + c;
                    if (!isComputed[i][new_cnt])
                    {
                        isComputed[i][new_cnt] = 1;
                        dp[i][new_cnt] = cost;
                    }
                    else
                        dp[i][new_cnt] = min(dp[i][new_cnt], cost);
                }
            }
        }
    }
    ll ret = LLONG_MAX;
    for (size_t i = 0; i < n; i++)
        for (size_t j = k; j <= 2 * k; j++)
            if (isComputed[i][j])
                ret = min(ret, dp[i][j]);
    if (ret == LLONG_MAX)
        ret = -1;
    cout << ret << '\n';
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