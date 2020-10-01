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
    ll h, c, t;
    cin >> h >> c >> t;
    vector<int> candidates = {1};
    ll num = h - t;
    ll den = 2 * t - h - c;
    if (den > 0)
    {
        long double val = num;
        val /= den;
        auto numerical = int(val);
        candidates.pb(numerical - 2);
        candidates.pb(numerical - 1);
        candidates.pb(numerical);
        candidates.pb(numerical + 1);
        candidates.pb(numerical + 2);
    }
    long double minVal = h - t;
    ll minNuOfCups = 1;
    db(h, c, t);
    for (auto &x : candidates)
    {
        if (x > 0)
        {
            long double EPS = 1e-15;
            ll temp = (x + 1) * h + x * c;
            long double avgTemp = temp;
            avgTemp /= (2 * x + 1);
            db(avgTemp);
            avgTemp = abs(avgTemp - t);
            db(avgTemp, minVal, 2 * x + 1);
            if (abs(avgTemp - minVal) <= EPS)
            {
                minNuOfCups = min(2 * (long long)x + 1, minNuOfCups);
            }
            else if (avgTemp < minVal)
            {
                minVal = avgTemp;
                minNuOfCups = 2 * (long long)x + 1;
            }

            temp = (x)*h + x * c;
            avgTemp = temp;
            avgTemp /= (2 * x);
            db(avgTemp);
            avgTemp = abs(avgTemp - t);
            db(avgTemp, minVal, 2 * x);
            if (abs(avgTemp - minVal) <= EPS)
            {
                minNuOfCups = min(2 * (long long)x, minNuOfCups);
            }
            else if (avgTemp < minVal)
            {
                minVal = avgTemp;
                minNuOfCups = 2 * (long long)x;
            }
        }
    }
    cout << minNuOfCups << '\n';
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
