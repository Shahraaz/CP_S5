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
const int NAX = 2e5 + 5, MOD = 1000000007;

const int MAXN = 101, MAXA = 101 * 101 + 1;
ll dp[2][MAXN][MAXA];

void solveCase()
{
    int n;
    cin >> n;
    vector<pair<int, int>> bottles(n);
    ll sumb = 0;
    for (auto &[x, y] : bottles)
    {
        cin >> x >> y;
        sumb += y;
    }
    bool prev;
    bool next;
    memset(dp, -1, sizeof dp);
    dp[0][0][0] = dp[1][0][0] = 0;
    for (size_t i = 0; i < n; i++)
    {
        prev = i & 1;
        next = !prev;
        // memset(dp[next], 0, sizeof dp[next]);
        memcpy(dp[next], dp[prev], sizeof dp[next]);
        for (int k = 0; k < n; k++)
            for (int A = 0; A + bottles[i].first < MAXA; A++)
            {
                if (dp[prev][k][A] != -1)
                    dp[next][k + 1][A + bottles[i].first] = max(dp[next][k + 1][A + bottles[i].first], dp[prev][k][A] + bottles[i].second);
            }
    }
    using ld = long double;
    for (int k = 1; k <= n; k++)
    {
        ld res = 0;
        for (int A = 0; A < MAXA; A++)
        {
            if (dp[next][k][A] != -1)
                res = max(res, min((ld)A, (dp[next][k][A] + sumb) / (ld)2));
        }
        cout << res << ' ';
    }
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    cout << fixed << setprecision(10);
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}