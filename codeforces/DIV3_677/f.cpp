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

const int NAX = 70 + 5, MOD = 1000000007;

int dp[NAX][NAX][NAX][NAX];
int a[NAX][NAX];
int n, m, k, LIM;

int solve(int i, int j, int curr, int rem)
{
    if (i == n)
        return rem == 0 ? 0 : -MOD;
    if (curr == LIM || j == m)
        return solve(i + 1, 0, 0, rem);
    int &ret = dp[i][j][curr][rem];
    if (ret != -1)
        return ret;
    db(i, j, curr, rem);
    ret = solve(i, j + 1, curr, rem);
    ret = max(ret, a[i][j] + solve(i, j + 1, curr + 1, (rem + a[i][j]) % k));
    return ret;
}

void solveCase()
{
    memset(dp, -1, sizeof dp);
    cin >> n >> m >> k;
    LIM = m / 2;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            cin >> a[i][j];

    cout << solve(0, 0, 0, 0) << '\n';
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
