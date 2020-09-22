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

void solveCase()
{
    ll x, y, k;
    cin >> x >> y >> k;
    ll ky = k * (y + 1) - 1;
    ll temp = ceil(1.0 * ky / (x - 1));
    db(temp * x, k * y, k);
    ll res = LLONG_MAX;
    for (auto curr : {temp - 2, temp - 1, temp, temp + 1, temp})
    {
        if (curr < 0)
            continue;
        ll sticks = x * curr - (curr - 1) - k * y;
        ll torches = k;
        if (sticks >= k)
            res = min(res, curr + k);
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
    cin >> t;
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
