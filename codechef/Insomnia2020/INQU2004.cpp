// Optimise

// #pragma GCC optimize("O2")
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

const int _n = 2e5 + 10;
// vector<int> Fact(_n), Inv(_n);
const int kmod = 1000000007;
const int mod = 1000000007;

// map<ll, int> P2;

int power(int base, ll index, int mod = kmod)
{
    if (index == 0)
        return 1;
    int temp = power(base, index / 2, mod);
    temp = (temp * 1LL * temp) % mod;
    if (index & 1)
        temp = (temp * 1LL * base) % mod;
    return temp;
}

int mod_inv(int x, int mod = kmod)
{
    return power(x, mod - 2, mod);
}

void fib(ll n, ll &x, ll &y)
{
    if (n == 0)
    {
        x = 0;
        y = 1;
        return;
    }

    if (n & 1)
    {
        fib(n - 1, y, x);
        y = (y + x) % mod;
    }
    else
    {
        ll a, b;
        fib(n >> 1, a, b);
        y = (a * a + b * b) % mod;
        x = (a * b + a * (b - a + mod)) % mod;
    }
}

ll INF = 1e18 - 1;

void solveCase()
{
    ll n;
    n = INF;
    INF -= 20000;
    cin >> n;
    ll x, y;
    fib(n, x, y);
    ll num = y;
    ll den = power(2, n - 1);
    db(num, den);
    cout << (num * 1LL * mod_inv(den)) % MOD << '\n';
}

int32_t main()
{
    // pre();
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    t = 1e5;
    cin >> t;
    // F[0] = F[1] = 1;
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
