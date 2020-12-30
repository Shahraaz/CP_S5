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
    int n;
    cin >> n;
    vector<pair<ll, ll>> l, r, lr;
    for (size_t i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        if (x < y)
            r.pb({y, x});
        else if (x > y)
            l.pb({x, y});
        else
            lr.pb({x, y});
    }

    sort(all(l));
    sort(all(r));
    sort(all(lr));

    ll ret = 0;

    vector<pair<ll, ll>> res;
    while (l.size() + r.size() + lr.size())
    {
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
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}