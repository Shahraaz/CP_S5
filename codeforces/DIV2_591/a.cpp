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
    ll n;
    cin >> n;
    int temp = n / 4;
    int res = MOD;
    for (auto &x : {temp - 2, temp - 1, temp, temp + 1, temp + 2})
        for (auto &y : {temp - 2, temp - 1, temp, temp + 1, temp + 2})
        {
            int z = n - x - y, now = 0;
            if (z < 0)
            {
                z = 1;
                now += 1 - z;
            }
            if (x > 0 && y > 0)
                res = min(res, now + abs(x + y - (z)));
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
