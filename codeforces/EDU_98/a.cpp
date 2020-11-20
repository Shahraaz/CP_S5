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

void solveCase()
{
    ll x, y;
    cin >> x >> y;
    ll res = LLONG_MAX;
    ll temp = min(x, y);
    x -= temp;
    y -= temp;
    if (x > 0 || y > 0)
        res = min(res, 2 * temp + 2 * x + 2 * y - 1);
    else
        res = 2 * temp;
    // res = min(res, 2 * x + y);
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
        solveCase();
    return 0;
}