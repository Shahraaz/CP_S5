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
    int n;
    ll x, y;
    cin >> n;
    cin >> x >> y;
    if (y < n)
    {
        cout << -1 << '\n';
        return;
    }
    // auto one = y / n, two = y % n;
    vector<ll> a(n, 1);
    ll a1, b;
    a1 = 0, b = 0;
    a[0] += y - n;
    for (size_t i = 0; i < n; i++)
    {
        // a[i] = one;
        // a[i] += two;
        // two = 0;
        a1 += a[i] * a[i];
        b += a[i];
        db(i, a[i]);
    }
    db(a1, b);
    if (a1 >= x && b <= y)
    {
        for (auto &x : a)
        {
            cout << x << '\n';
        }
    }
    else
        cout << -1 << '\n';
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
