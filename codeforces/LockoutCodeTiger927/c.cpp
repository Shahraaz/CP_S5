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

const int NAX = 2e6 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

// int cnt[NAX];

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

void Solution::solveCase()
{
    int n;
    cin >> n;
    int p;
    cin >> p;
    map<int, int> cnt;
    vector<int> vals;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        cnt[x]++;
        vals.pb(x);
    }
    if (p == 1)
    {
        cout << (n & 1) << '\n';
        return;
    }
    sort(all(vals));
    // vals.erase(unique(all(vals)), vals.end());
    // int a =
    // for (size_t i = 0; i < vals.size(); i++)
    // {
    // }
    ll a = 1;
    ll maxDiff = 0;
    int ekbar = 0;
    int prevIdx = MOD;
    for (int i = vals.size() - 1; i >= 0; i--)
    {
        int j = vals[i];
        db(j, cnt[j]);
        if (j + 25 < prevIdx)
        {
            
        }
        else
        {

        }
    }
    cout << maxDiff << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
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
