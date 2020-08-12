// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase()
    {
        ll d, k, a, b, t;
        cin >> d >> k >> a >> b >> t;
        ll low = 1, high = d;
        ll ans = LLONG_MAX;
        function<ll(ll)> check = [&](ll x) -> ll {
            return ((x - 1) / k) * t + x * a + (d - x) * b;
        };
        db(ll(1e18));
        while (low + 50000 <= high)
        {
            ll t1 = (low + low + high) / 3;
            ll t2 = (low + high + high) / 3;
            auto a = check(t1), b = check(t2);
            db(low, high, ans, a, b);
            ans = min(ans, a);
            ans = min(ans, b);
            ans = min(ans, check(low));
            ans = min(ans, check(high));
            if (a > b)
                low = t1;
            else
                high = t2;
        }
        while (low <= high)
        {
            ll temp = check(low);
            db(low, temp);
            ans = min(ans, temp);
            low++;
        }
        cout << ans << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
