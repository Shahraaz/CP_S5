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

ll sum_of_dig(ll n)
{
    ll ret = 0;
    while (n)
    {
        ret += n % 10;
        n /= 10;
    }
    return ret;
}

ll min_no_with_sum(int x)
{
    ll ret = 0;
    while (x)
    {
        if (x > 9)
        {
            ret = ret * 10 + 9;
            x -= 9;
        }
        else
        {
            ret = ret * 10 + x;
            x -= x;
        }
    }
    db(x, ret);
    return ret;
}

void solveCase()
{
    ll n;
    cin >> n;
    // ll res = sum_of_dig(n);
    // for (int i = 0; i <= n; i++)
    // {
    //     ll one = sum_of_dig(i), two = sum_of_dig(n - i);
    //     // db(i, n - i, one + two);
    //     res = max(res, one + two);
    // }
    // cout << res << '\n';
    {
        ll res1 = sum_of_dig(n);
        ll a = 0, b = n, c = 1;
        for (int i = 0; i <= 108; i++)
        {
            ll a = min_no_with_sum(i);
            if (0 <= a && a <= n)
            {
                ll b = n - a;
                res1 = max(res1, sum_of_dig(a) + sum_of_dig(b));
            }
        }
        // assert(res == res1);
        cout << res1 << '\n';
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