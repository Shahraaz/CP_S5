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

void yes()
{
    cout << "Yes\n";
    exit(0);
}

void no()
{
    cout << "No\n";
    exit(0);
}

void solveCase()
{
    ll k, l, r, t, x, y;
    cin >> k >> l >> r >> t >> x >> y;
    vector<bool> cache(x, 0);
    db(k, l, r, t, x, y);
    if (y == x)
    {
        db("y == x");
        while (t > 0)
        {
            db(k, l, r, t, x, y);
            if (k + y <= r)
            {
                k += y;
            }
            if (l <= k - x)
                k -= x;
            else
                no();
            if (cache[k % x])
                yes();
            cache[k % x] = 1;
            t--;
        }
        yes();
    }
    else if (y > x)
    {
        while (t > 0)
        {
            ll r1 = (r - k - x) / (y - x);
            r1 = min(r1, (r - k) / (y - x));
            ll l1 = (l - k - x) / (y - x);
            l1 = min(l1, (l - k) / (y - x));
            db(k, l, r, t, x, y);
            db(r1);
            if (r1 > 0 && k + y <= r)
            {
                k += r1 * (y - x);
                t -= r1;
            }
            else // if (r1 <= 0)
            {
                db(k, k % x);
                ll temp = (k - l) / x;
                db(temp);
                if (temp)
                {
                    k -= x * temp;
                    t -= temp;
                }
                else
                    no();
                db(k, k % x);
                if (cache[k % x])
                    yes();
                cache[k % x] = 1;
                // t--;
            }
        }
        yes();
    }
    else // if (y < x)
    {
        if (k + y <= r)
            k += y;
        db(k, l, x, y);
        ll time = (k - l - y) / (x - y);
        db(time, t);
        if (time >= t)
            yes();
        else
            no();
    }
    // yes();
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