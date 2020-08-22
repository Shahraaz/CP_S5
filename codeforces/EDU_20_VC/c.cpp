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

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    ll n, k;
    cin >> n >> k;
    ll ansgcd = 0;
    vector<ll> factors;
    for (ll i = 1; i * i <= n; i++)
        if (n % i == 0)
        {
            factors.pb(i);
            factors.pb(n / i);
        }
    long double minSum = 0;
    if (k & 1)
        minSum = (k + 1.0) / 2 * k;
    else
        minSum = (k) / 2 * (k + 1.0);
    db(minSum, k);
    for (auto &x : factors)
    {
        ll sum = n / x;
        if (minSum <= sum)
            ansgcd = max(ansgcd, x);
    }
    if (ansgcd == 0)
        cout << -1 << '\n';
    else
    {
        ll sum = n / ansgcd;
        vector<ll> res;
        for (size_t i = 0; i < k; i++)
        {
            res.pb((i + 1));
            sum -= i + 1;
        }
        res.back() += sum;
        for (auto &x : res)
        {
            cout << x * ansgcd << ' ';
        }
        cout << '\n';
    }
}

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
