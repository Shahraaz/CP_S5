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
    ll n, k;
    cin >> n >> k;
    vector<ll> h(n);
    for (auto &x : h)
        cin >> x;
    vector<ll> minhl(n, -MOD), maxhl(n, -MOD);
    db(n, k);
    db(h);
    {
        minhl[0] = maxhl[0] = h[0];
        for (size_t i = 1; i < n; i++)
        {
            ll pmax = maxhl[i - 1] + k - 1;
            ll pmin = max(0LL, minhl[i - 1] - k + 1);
            pmax = min(pmax, h[i] + k - 1);
            pmin = max(pmin, h[i]);
            db(i, pmax, pmin);
            if (pmin > pmax)
            {
                cout << "NO\n";
                return;
            }
            maxhl[i] = pmax;
            minhl[i] = pmin;
        }
    }
    if (minhl[n - 1] <= h[n - 1] && h[n - 1] <= maxhl[n - 1])
        cout << "YES\n";
    else
        cout << "NO\n";
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