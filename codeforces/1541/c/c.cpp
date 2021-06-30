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
    vector<ll> d(n);
    for (auto &x : d)
    {
        cin >> x;
    }
    sort(all(d));
    ll res = 0, sum = 0, pref = 0;
    for (size_t i = 1; i < n; i++)
    {
        res += d[i] - d[i - 1];
        pref += i * 1LL * (d[i] - d[i - 1]);
        res -= pref;
        db(i, res, pref, sum);
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
        solveCase();
    return 0;
}