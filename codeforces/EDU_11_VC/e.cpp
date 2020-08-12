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

const int NAX = 2e5 + 5, MOD = 1000000007;

const int _n = 1e6 + 10;
vector<int> Fact(_n), Inv(_n);
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

struct Solution
{
    Solution()
    {
        pre();
    }
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        int res = power(m, n);
        // int aux_sum = 0;
        // vector<int> prefSum(n + 1);
        // for (size_t i = 0; i < prefSum.size(); i++)
        //     prefSum[i] = mul(power(m - 1, i), power(m, n - i));
        // for (size_t i = 1; i < prefSum.size(); i++)
        //     prefSum[i] = add(prefSum[i - 1], prefSum[i]);
        // auto rangeSum = [&](int lptr, int rptr) {
        //     if (lptr == 0)
        //         return prefSum[rptr];
        //     return (prefSum[rptr] - prefSum[lptr] + MOD) % MOD;
        // };
        for (int len = 1; len <= n; len++)
        {
            // int temp = 0;
            // for (int xLen = len; xLen <= n; xLen++)
            //     temp = add(temp, mul(power(m - 1, xLen - len), power(m, n - xLen)));
            // temp = mul(temp, ncr(n, len));
            // temp = mul(temp, power(m, len));
            res = add(res, mul(mul(power(m, len), power(m - 1, n - len)), ncr(n, len - 1)));
        }
        cout << res << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
