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
    ll x, y, l, r;
    cin >> x >> y >> l >> r;
    vector<ll> vecc;
    ll a = 1;
    while (true)
    {
        ll b = 1;
        if (b > r)
            break;
        while (true)
        {
            if (a + 0.0 + b >= LLONG_MAX)
                break;
            if (a + b > r)
                break;
            vecc.pb(a + b);
            if (b * 1.0 * y >= LLONG_MAX)
                break;
            b *= y;
        }
        if (a * 1.0 * x >= LLONG_MAX)
            break;
        a *= x;
    }
    vecc.pb(l - 1);
    vecc.pb(r + 1);
    sort(all(vecc));
    vecc.erase(unique(all(vecc)), vecc.end());
    ll res = 0;
    auto it = lower_bound(all(vecc), l);
    db(vecc);
    while (it != vecc.end())
    {
        if (l > r)
            break;
        while (it != vecc.end() && *it == l)
        {
            ++it;
            ++l;
        }
        ll r1 = r + 1;
        auto it2 = upper_bound(all(vecc), l);
        if (it2 != vecc.end())
            r1 = min(*it2, r1);
        db(l, r1);
        // db(vecc);
        res = max(res, r1 - l);
        l = max(l + 1, r1 + 1);
        db(l);
        it = lower_bound(all(vecc), l);
    }
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
