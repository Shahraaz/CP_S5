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

using ld = long double;
ld dp[52][5200];
int t[55], d[55];
ld p[55];

void solveCase()
{
    int n, r, m;
    cin >> n >> r >> m;
    p[0] = 1;
    for (size_t i = 1; i <= m; i++)
        cin >> t[i] >> p[i] >> d[i];
    t[m + 1] = n;
    int w = r - n - 1;
    const ld EPS = 1e-10;
    auto check = [&](ld temp) -> bool
    {
        for (int i = m; i >= 0; i--)
            for (int j = w; j >= 0; j--)
            {
                dp[i][j] = p[i] * (dp[i + 1][j] + t[i + 1] - t[i]);
                dp[i][j] += (1 - p[i]) * min(temp, (j + d[i] <= w ? dp[i + 1][j + d[i]] : 1e10) + t[i + 1] - t[i] + d[i]);
            }
        db(temp, dp[0][0]);
        return dp[0][0] <= temp;
    };
    ld low = 0, high = 1e11;
    while (abs(high - low) > EPS)
    {
        auto mid = (low + high) / 2;
        if (check(mid))
            high = mid;
        else
            low = mid;
    }
    cout << fixed << setprecision(8);
    cout << high << '\n';
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