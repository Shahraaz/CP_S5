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
    ll now = 0, arrive = 0;
    ll b_prev = 0;
    vector<ll> a(n), b(n);
    for (size_t i = 0; i < n; i++)
        cin >> a[i] >> b[i];
    for (size_t i = 0; i < n; i++)
    {
        ll tmi;
        cin >> tmi;
        tmi += a[i];
        if (i > 0)
            tmi -= b[i - 1];
        now += tmi;
        arrive = now;
        ll diff = (b[i] - a[i] + 1) / 2;
        ll diff2 = b[i] - now;
        db(now, tmi, diff, diff2, a[i], b[i]);
        diff = max({diff, diff2});
        now += diff;
    }
    cout << arrive << '\n';
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