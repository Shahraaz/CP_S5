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

const int _n = 1000 + 10;
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

void solveCase()
{
    pre();
    int n, x, pos;
    cin >> n >> x >> pos;
    int lessElems = x - 1;
    int moreElems = n - lessElems - 1;
    int low = 0, high = n;
    int res = 1;
    set<int> vis;
    while (low < high)
    {
        int mid = (low + high) / 2;
        db(low, high, mid);
        db(lessElems, moreElems);
        db(pos);
        if (mid == pos)
            low = mid + 1;
        else if (mid < pos)
        {
            db("mid < pos");
            if (vis.find(mid) == vis.end())
            {
                vis.insert(mid);
                res = mul(res, lessElems);
                lessElems--;
                if (lessElems < 0)
                {
                    cout << 0 << '\n';
                    return;
                }
            }
            low = mid + 1;
        }
        else
        {
            db("mid > pos");
            if (vis.find(mid) == vis.end())
            {
                vis.insert(mid);
                res = mul(res, moreElems);
                moreElems--;
                if (moreElems < 0)
                {
                    cout << 0 << '\n';
                    return;
                }
            }
            high = mid;
        }
    }
    db(low, high);
    db(lessElems, moreElems);
    res = mul(res, Fact[lessElems + moreElems]);
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
