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

const int NAX = 2e5 + 5, MOD = 998244353 ;

const int _n = 1e5 + 10;
vector<int> Fact(_n), Inv(_n);
const int kmod = 998244353 ;

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
    return power(x, kmod - 2);
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

class Solution
{
private:
public:
    Solution()
    {
        pre();
    }
    ~Solution() {}
    void solveCase()
    {
        ll d;
        int q;
        cin >> d >> q;
        vector<ll> primes;
        for (ll i = 2; i * i <= d; i++)
            if (d % i == 0)
            {
                primes.pb(i);
                while (d % i == 0)
                    d /= i;
            }
        if (d > 1)
            primes.pb(d);
        while (q--)
        {
            ll x, y;
            cin >> x >> y;
            vector<int> up, dw;
            for (auto &p : primes)
            {
                int cnt = 0;
                while (x % p == 0)
                    --cnt, x /= p;
                while (y % p == 0)
                    ++cnt, y /= p;
                if (cnt > 0)
                    up.pb(cnt);
                else
                    dw.pb(-cnt);
            }
            int ans = mul(Fact[accumulate(all(up), 0)], Fact[accumulate(all(dw), 0)]);
            for (auto &it : up)
                ans = mul(ans, Inv[it]);
            for (auto &it : dw)
                ans = mul(ans, Inv[it]);
            cout << ans << '\n';
        }
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
