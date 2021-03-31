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
const int NAX = 2e5 + 5, MOD = 998244353;

const int kmod = 998244353;

int mul(int a, int b, int mod = kmod)
{
    return (long long)a * b % mod;
}

int add(int a, int b, int mod = kmod)
{
    a += b;
    if (a >= mod)
        a -= mod;
    return a;
}

int sub(int a, int b, int mod = kmod)
{
    a -= b;
    if (a < 0)
        a += mod;
    return a;
}

int power(int base, int index, int mod = kmod)
{
    if (index == 0)
        return 1;
    int temp = power(base, index / 2, mod);
    temp = mul(temp, temp, mod);
    if (index & 1)
        temp = mul(temp, base, mod);
    return temp;
}

int mod_inv(int x, int mod = kmod)
{
    return power(x, mod - 2, mod);
}

int dp[1001][1001][2][4];

void solveCase()
{
    string x, y;
    cin >> x >> y;
    int n = x.size();
    int m = y.size();
    memset(dp, -1, sizeof dp);
    function<int(int, int, int, int)> solve = [&](int i, int j, int prev, int mask) -> int {
        if (i == n && j == m)
            return mask == 3;
        auto &ret = dp[i][j][prev][mask];
        if (ret >= 0)
            return ret;
        ret = (mask == 3);
        char prevchar = '$';
        if (mask != 0)
        {
            if (prev == 0)
            {
                assert(i >= 1);
                prevchar = x[i - 1];
            }
            else
            {
                assert(j >= 1);
                prevchar = y[j - 1];
            }
        }
        if (i < n)
            if (prevchar != x[i])
                ret = add(ret, solve(i + 1, j, 0, mask | 1));
        if (j < m)
            if (prevchar != y[j])
                ret = add(ret, solve(i, j + 1, 1, mask | 2));
        return ret;
    };
    int res = 0;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            res = add(res, solve(i, j, 0, 0));
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
        solveCase();
    return 0;
}