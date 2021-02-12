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
    ll n, m;
    cin >> n >> m;
    ll total = n * (n + 1) / 2;
    ll blanks = n - m;
    if (blanks == 0)
    {
        cout << total << '\n';
        return;
    }
    db(n, m);
    ll smallsize = (n - m) / (m + 1);
    db(smallsize);
    ll largesize = (n - m) / (m + 1) + 1;
    db(largesize);
    ll largecnt = (n - m) % (m + 1);
    db(largecnt);
    ll smallcnt = (blanks - largecnt * largesize);
    if (smallsize)
        smallcnt /= smallsize;
    db(smallsize);
    cout << total - smallcnt * (smallsize) * (smallsize + 1) / 2 - largecnt * (largesize) * (largesize + 1) / 2 << '\n';
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