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
    vector<ll> d;
    map<ll, int> mp;
    for (size_t i = 0; i < 2 * n; i++)
    {
        ll x;
        cin >> x;
        if (mp[x] == 1)
        {
            mp[x] = 0;
            d.pb(x);
        }
        else
            mp[x] = 1;
    }
    sort(all(d));
    db(n, d);
    if (d.size() != n)
    {
        cout << "NO\n";
        return;
    }
    if (n == 1)
    {
        if (d[0] & 1)
        {
            cout << "NO\n";
            return;
        }
        else
        {
            cout << "YES\n";
            return;
        }
    }
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
    {
        if (d[i] & 1)
        {
            cout << "NO\n";
            return;
        }
        if (i + 1 < n)
        {
            int right = n - 1 - i;
            int left = n + i + 1;
            db(i, left, right);
            ll diff = d[i + 1] - d[i];
            assert(right != left);
            ll den = left - right;
            db(i, diff, 2);
            if (diff % (den) || diff == 0)
            {
                cout << "NO\n";
                return;
            }
            a[i + 1] = diff / (den);
            // if (i > 0)
            //     a[i] += a[i - 1];
            a[i + 1] += a[i];
        }
    }
    db(a);
    ll temp = d[0] - 2 * accumulate(all(a), 0LL);
    db(temp, 2 * n);
    if (temp % (2 * n))
    {
        cout << "NO\n";
        // cout << "YES\n";
        return;
    }
    temp /= 2 * n;
    db(temp);
    if (temp > 0)
    {
        // for (auto &x : a)
        //     x += temp;
        // vector<ll> a2 = a;
        // for (auto &x : a)
        //     a2.pb(-x);
        // sort(all(a2));
        // db(a2);
        // for (size_t i = 0; i < 2 * n; i++)
        // {
        //     ll newtemp = 0;
        //     for (size_t j = 0; j < 2 * n; j++)
        //     {
        //         // db(i, j, newtemp);
        //         if (i > j)
        //             newtemp += a2[i] - a2[j];
        //         else
        //             newtemp += a2[j] - a2[i];
        //         // db(i, j, a[i] - a[j], a[j] - a[i], newtemp);
        //         // newtemp += abs(a[i] - a[j]);
        //     }
        //     db(i, newtemp);
        // }

        cout << "YES\n";
    }
    else
        cout << "NO\n";
}

int32_t main()
{
    srand(time(NULL));
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