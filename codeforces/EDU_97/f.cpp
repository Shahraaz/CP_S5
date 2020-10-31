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

const int NAX = 5e3 + 5, MOD = 998244353;

int add(int a, int b)
{
    a += b;
    if (a >= MOD)
        a -= MOD;
    return a;
}

int sub(int a, int b)
{
    a -= b;
    if (a < 0)
        a += MOD;
    return a;
}

int mul(int a, int b)
{
    return (a * 1LL * b) % MOD;
}

int dp[NAX][NAX];
int pdp[NAX][NAX];
int lastLess[NAX];
int cntLess[NAX];
int a[NAX];
int n;

void solveCase()
{
    cin >> n;
    for (size_t i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);
    for (size_t i = 0; i < n; i++)
    {
        cntLess[i] = 0;
        lastLess[i] = -1;
        for (size_t j = 0; j < n; j++)
            if (a[j] * 2 <= a[i])
            {
                lastLess[i] = j;
                cntLess[i]++;
            }
    }
    for (size_t i = 0; i < n; i++)
    {
        dp[i][1] = 1;
        pdp[i + 1][1] = add(pdp[i][1], dp[i][1]);
    }
    for (size_t k = 2; k <= n; k++)
        for (size_t i = 0; i < n; i++)
        {
            if (cntLess[i] + 1 >= k)
                dp[i][k] = add(mul(dp[i][k - 1], add(cntLess[i], sub(2, k))), pdp[lastLess[i] + 1][k - 1]);
            else
                dp[i][k] = 0;
            db(i, k, dp[i][k]);
            pdp[i + 1][k] = add(pdp[i][k], dp[i][k]);
        }
    cout << dp[n - 1][n] << '\n';
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
