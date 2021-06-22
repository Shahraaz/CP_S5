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

const int _n = 2e5 + 10;
vector<int> Fact(_n), Inv(_n);

void pre()
{
    Fact[0] = 1;
    for (int i = 1; i < _n; ++i)
        Fact[i] = mul(Fact[i - 1], i);
    Inv[_n - 1] = mod_inv(Fact[_n - 1]);
    for (int i = _n - 2; i >= 0; --i)
        Inv[i] = mul(Inv[i + 1], (1 + i));
}

int ncr(int n, int r)
{
    if (n < 0 || r < 0 || n - r < 0)
        return 0;
    return mul(Fact[n], mul(Inv[r], Inv[n - r]));
}

int npr(int n, int r)
{
    if (n < 0 || r < 0 || n - r < 0)
        return 0;
    return mul(Fact[n], Inv[n - r]);
}

int dp[256][256], pre_comp[256 * 256], pre_comp2[256 * 256];
void solveCase()
{
    pre();
    int n, k;
    cin >> n >> k;
    if (k == 1)
    {
        cout << 1 << '\n';
        return;
    }
    for (size_t i = 0; i < 256 * 256; i++)
        pre_comp[i] = power(k, i);
    for (size_t i = 0; i < 256 * 256; i++)
        pre_comp2[i] = k == 1 ? 0 : power(k - 1, i);

    memset(dp, -1, sizeof dp);
    function<int(int, int)> solve = [&](int r, int c) -> int
    {
        if (r == 0 || c == 0)
            return 1;
        auto &ret = dp[r][c];
        if (ret >= 0)
            return ret;
        ret = 0;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
            {
                int temp = mul(ncr(r - 1, i), ncr(c - 1, j));
                temp = mul(temp, solve(i, j));

                int rem_rows = (r - 1 - i);
                int rem_cols = (c - 1 - j);
                int total = rem_rows * (c - 1) + rem_cols * (r - 1) - (rem_rows * rem_cols);

                temp = mul(temp, pre_comp2[total]);

                db(r, c, i, j, rem_rows, rem_cols, total);
                // r,c is 1
                int other = 0;
                other = pre_comp[i + j];
                // r,c is 0
                if (i && j)
                    other = add(other, mul(sub(pre_comp[i], pre_comp2[i]), sub(pre_comp[j], pre_comp2[j])));
                    
                ret = add(ret, mul(temp, other));
            }
        db(r, c, ret);
        return ret;
    };
    cout << solve(n, n) << '\n';
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