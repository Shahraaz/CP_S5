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

void solveCase()
{
    ll c, m, x;
    cin >> c >> m >> x;
    ll low = 0, high = max({c, m, x});
    ll ans = low;
    auto check = [&](ll teams) -> bool {
        db(teams);
        db(c, m, x, teams);
        ll c1 = c - teams;
        ll m1 = m - teams;
        ll x1 = x + c1 + m1;
        x1 -= teams;
        return c1 >= 0 && m1 >= 0 && x1 >= 0;
    };
    while (low <= high)
    {
        ll mid = (low + high) >> 1;
        if (check(mid))
        {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else
            high = mid - 1;
    }
    cout << ans << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
