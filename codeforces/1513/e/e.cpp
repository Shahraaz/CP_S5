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

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    ll sum = 0;
    for (auto &x : a)
    {
        cin >> x;
        sum += x;
    }
    if (sum % n)
    {
        cout << "0\n";
        return;
    }
    sum /= n;
    int less = 0, eq = 0, more = 0;
    for (auto &x : a)
        if (x < sum)
            ++less;
        else if (x == sum)
            eq++;
        else
            more++;
    db(less, eq, more);
    db(a);
    if (less <= 1 || more <= 1)
    {
        map<int, int> cnt;
        for (auto &x : a)
            cnt[x]++;
        int res = Fact[n];
        for (auto &x : cnt)
            res = mul(res, Inv[x.second]);
        cout << res << '\n';
        return;
    }
    int res = mul(2, ncr(n, eq));
    res = mul(res, Fact[less]);
    res = mul(res, Fact[more]);
    map<int, int> cnt;
    for (auto &x : a)
        if (x != sum)
            cnt[x]++;
    for (auto &x : cnt)
        res = mul(res, Inv[x.second]);
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}