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
    void solveCase()
    {
        ll m, d, w;
        cin >> m >> d >> w;
        if (d == 1)
        {
            // ll temp = d * (d + 1) / 2;
            // if (d - m > 0)
            //     temp -= (d - m) * (d - m) / 2;
            cout << 0 << '\n';
            return;
        }
        ll w1 = w;
        ll den = d - 1;
        ll g = __gcd(w1, den);
        w1 /= g;
        ll lim = min(d, m);
        ll maxt = lim / w1;
        ll res = 0;
        res += lim * maxt;
        res -= w1 * maxt * (maxt + 1) / 2;
        db(res, lim, maxt, w1);
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
