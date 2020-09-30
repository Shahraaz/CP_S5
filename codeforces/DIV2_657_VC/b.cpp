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
    ll l, r, m;
    cin >> l >> r >> m;
    ll maxi = m + r - l;
    ll mini = m + l - r;
    db(mini, maxi);
    const long double EPS = 1e-6;
    for (ll a = l; a <= r; a++)
    {
        long double miniii = mini / (a * (long double)1);
        long double maxiii = maxi / (a * (long double)1);
        db(l, r, m, a, miniii, maxiii);
        auto next = ceil(maxiii);
        for (auto n : {next - 2, next - 1, next, next + 1, next + 2})
        {
            if (n <= 0)
                continue;
            ll temp = m - next * a;
            if (l - r <= temp && temp <= r - l)
            {
                for (ll b = l; b <= r; b++)
                {
                    auto c = n * a + b - m;
                    if (l <= c && c <= r)
                    {
                        cout << a << ' ' << b << ' ' << c << '\n';
                        return;
                    }
                }
            }
        }
        next = ceil(miniii);
        for (auto n : {next - 2, next - 1, next, next + 1, next + 2})
        {
            if (n <= 0)
                continue;
            ll temp = m - next * a;
            if (l - r <= temp && temp <= r - l)
            {
                for (ll b = l; b <= r; b++)
                {
                    auto c = n * a + b - m;
                    if (l <= c && c <= r)
                    {
                        cout << a << ' ' << b << ' ' << c << '\n';
                        return;
                    }
                }
            }
        }
    }
    assert(false);
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
