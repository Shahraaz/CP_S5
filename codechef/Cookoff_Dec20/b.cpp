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
    ll g = 0;
    vector<ll> p(m);
    for (size_t i = 0; i < m; i++)
    {
        cin >> p[i];
    }
    g = p[0];
    db(p);
    for (size_t i = 1; i < m; i++)
    {
        g = g / __gcd(g, p[i]) * p[i];
        if (g > n)
        {
            db("a");
            cout << n - 1 << '\n';
            return;
        }
        // else g <= n
    }
    db("b", g, n);
    // cout << t << '\n';
    if (n >= g)
        cout << n - g << '\n';
    else
    {
        cout << n - __gcd(n, g) << '\n';
    }
    // }
    // else
    // {
    //     // g > n
    //     cout << n - __gcd(n, g) << '\n';
    // }
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