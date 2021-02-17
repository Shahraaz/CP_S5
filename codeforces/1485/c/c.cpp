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
    ll a, b;
    cin >> a >> b;
    ll res = 0;
    for (ll b_c = 1; b_c <= b;)
    {
        ll d = a / (b_c + 1);
        if (d == 0)
            break;
        ll rhs = a / (d);
        // rhs = min(rhs, b);
        db(b_c, d, rhs);
        ll l = b_c, r = rhs - 1;
        r = min(r, b);
        if (d < l)
        {
            res += (r - l + 1) * 1LL * d;
        }
        else
        {
            while (l <= r)
            {
                db(l - 1, d);
                res += min(l - 1, d);
                ++l;
            }
        }
        b_c = rhs;
        // db(a, b_c, a / (b_c + 1));
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