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
#define int ll

const int NAX = 2e5 + 5, MOD = 1000000007;

const int _n = 2e5 + 10;
vector<int> Fact(_n), Inv(_n);
const int kmod = 1000000007;

int mul(int a, int b, int mod = kmod)
{
    return ((long long)(a % mod) * (b % mod)) % mod;
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
    int sum(int n)
    {
        return mul(n % MOD, mul((n + 1) % MOD, (MOD + 1) / 2));
    }
    int sum(int l, int r)
    {
        return sub(sum(r), sum(l - 1));
    }
    int calc(int n, int m)
    {
        m = min(m, n);
        int ans = 0;
        int minVal = m;
        for (int i = 1; i * i <= n; i++)
        {
            int lf = n / (i + 1), rg = n / i;
            // db(i, lf, rg, n / lf, n / rg);
            // db(n / (n / lf), n / (n / rg));
            rg = min(rg, m);
            if (lf >= rg)
                continue;
            minVal = lf;
            ans = add(ans, mul(i, sum(lf + 1, rg)));
        }
        for (int i = 1; i <= minVal; i++)
            ans = add(ans, mul(n / i, i));
        return ans;
    }
    Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        cout << sub(mul(n, m), calc(n, m)) << '\n';
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
