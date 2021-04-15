#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    long long x, y, k;
    cin >> x >> y >> k;
    for (size_t i = 0; i < k; i++)
    {
        if (i % 2 == 0)
        {
            if (x & 1)
                --x;
            y += x / 2;
            x = x / 2;
        }
        else
        {
            if (y & 1)
                --y;
            x += y / 2;
            y = y / 2;
        }
    }
    cout << x << ' ' << y << '\n';
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