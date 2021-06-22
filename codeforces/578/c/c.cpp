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
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    using ld = long double;
    ld low = -10000, high = 10000;
    auto check = [&](ld x) -> ld
    {
        ld res = 0, cumm = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            cumm += a[i] - x;
            if (cumm > res)
                res = cumm;
            if (cumm < 0)
                cumm = 0;
        }
        // db(x, res, cumm);
        cumm = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            cumm -= a[i] - x;
            if (cumm > res)
                res = cumm;
            if (cumm < 0)
                cumm = 0;
        }
        // db(x, res, cumm);
        return res;
    };
    while (abs(high - low) > 1e-14)
    {
        auto m1 = (2 * low + high) / 3;
        auto m2 = (low + 2 * high) / 3;
        db(low, high, check(m1), check(m2));
        if (check(m1) >= check(m2))
            low = m1;
        else
            high = m2;
    }
    cout << fixed << setprecision(10) << check(low) << '\n';
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