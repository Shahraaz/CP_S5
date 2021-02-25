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
    ll n;
    cin >> n;
    ll res = n;
    vector<ll> factors;
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            factors.pb(i);
            // res = i;
            // break;
        }
    }
    if (n > 1)
        factors.pb(n);

    if (factors.size() == 1)
    {
        cout << factors.back() << '\n';
    }
    // else if (factors.size() == 2)
    // {
    //     cout << factors.back() << '\n';
    // }
    else
        cout << 1 << '\n';
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