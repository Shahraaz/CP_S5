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
    vector<pair<int, int>> x, y;
    ll ans = 0;
    vector<int> one(n);
    vector<int> two(n);
    for (auto &x : one)
        cin >> x;
    for (auto &x : two)
        cin >> x;
    for (size_t i = 0; i < n; i++)
    {
        int a = one[i], b = two[i];
        // cin >> a >> b;
        ans += abs(a - b);
        if (a < b)
            x.pb({a, b});
        else
            y.pb({b, a});
    }
    sort(all(x));
    sort(all(y));
    db(x);
    db(y);
    db(ans);
    ll res = ans;
    {
        int last = 0;
        int ptr = 0;
        for (auto &a : x)
        {
            while (ptr < y.size() && y[ptr].first <= a.first)
            {
                last = max(last, y[ptr].second);
                ++ptr;
            }
            if (ptr > 0)
                res = min(res, ans - 2 * (min(a.second, last) - a.first));
            db(a, ptr, last, res);
        }
    }
    {
        int last = 0;
        int ptr = 0;
        for (auto &a : y)
        {
            while (ptr < x.size() && x[ptr].first <= a.first)
            {
                last = max(last, x[ptr].second);
                ++ptr;
            }
            if (ptr > 0)
                res = min(res, ans - 2 * (min(a.second, last) - a.first));
            db(a, ptr, last, res);
        }
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}