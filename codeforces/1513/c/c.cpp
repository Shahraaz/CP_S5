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

const int kmod = 1000000007;

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

// const int _n = 2e5 + 10;
// vector<int> Fact(_n), Inv(_n);

// void pre()
// {
//     Fact[0] = 1;
//     for (int i = 1; i < _n; ++i)
//         Fact[i] = mul(Fact[i - 1], i);
//     Inv[_n - 1] = mod_inv(Fact[_n - 1]);
//     for (int i = _n - 2; i >= 0; --i)
//         Inv[i] = mul(Inv[i + 1], (1 + i));
// }

// int ncr(int n, int r)
// {
//     if (n < 0 || r < 0 || n - r < 0)
//         return 0;
//     return mul(Fact[n], mul(Inv[r], Inv[n - r]));
// }

// int npr(int n, int r)
// {
//     if (n < 0 || r < 0 || n - r < 0)
//         return 0;
//     return mul(Fact[n], Inv[n - r]);
// }

vector<vector<vector<int>>> dp(NAX, vector<vector<int>>(10, vector<int>(10)));

void pre()
{
    for (size_t i = 0; i < 10; i++)
        dp[0][i][i] = 1;
    for (size_t j = 0; j + 1 < NAX; j++)
    {
        for (size_t i = 0; i <= 9; i++)
        {
            for (size_t k = 0; k < 9; k++)
                dp[j + 1][i][k + 1] = add(dp[j + 1][i][k + 1], dp[j][i][k]);
            dp[j + 1][i][0] = add(dp[j + 1][i][0], dp[j][i][9]);
            dp[j + 1][i][1] = add(dp[j + 1][i][1], dp[j][i][9]);
        }
    }
}

void solveCase()
{
    int n, m;
    cin >> n >> m;
    int res = 0;
    auto N = to_string(n);
    for (auto &c : N)
        for (size_t i = 0; i < 10; i++)
            res = add(res, dp[m][c - '0'][i]);
    cout << res << '\n';
}

int32_t main()
{
    pre();
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}