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
const int NAX = 5000 + 5, MOD = 1000000007;

int n, m;
string A, B;
int dp[NAX][NAX][2];

int solve(int id1, int id2, int t)
{
    if (id1 == n || id2 == m || t == 2)
        return 0;
    auto &ret = dp[id1][id2][t];
    if (ret >= 0)
        return ret;
    if (t == 0)
    {
        ret = solve(id1, id2, 1);
        ret = max(ret, solve(id1 + 1, id2, 0));
        ret = max(ret, solve(id1, id2 + 1, 0));
    }
    else
    {
        ret = 0;
        ret = max(ret, solve(id1, id2 + 1, 1) - 1);
        ret = max(ret, solve(id1 + 1, id2, 1) - 1);
        ret = max(ret, 4 * (A[id1] == B[id2]) + solve(id1 + 1, id2 + 1, 1) - 2);
    }
    db(id1, id2, t, ret);
    return ret;
}

void solveCase()
{
    cin >> n >> m;
    // n = 5000, m = 5000;
    cin >> A >> B;
    // for (size_t i = 0; i < n; i++)
    //     A.pb('A');
    // for (size_t i = 0; i < m; i++)
    //     B.pb('A');
    memset(dp, 0, sizeof dp);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            auto &ret = dp[i][j][1];
            ret = max(ret, dp[i + 1][j][1] - 1);
            ret = max(ret, dp[i][j + 1][1] - 1);
            ret = max(ret, 4 * (A[i] == B[j]) + dp[i + 1][j + 1][1] - 2);
            {
                auto &ret = dp[i][j][0];
                ret = dp[i][j][1];
                ret = max(ret, dp[i + 1][j][0]);
                ret = max(ret, dp[i][j + 1][0]);
            }
        }
    }
    cout << max(dp[0][0][0], dp[0][0][1]) << '\n';
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