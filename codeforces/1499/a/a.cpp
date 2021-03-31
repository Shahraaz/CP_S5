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
    int n, k1, k2, w, c;
    cin >> n >> k1 >> k2 >> w >> c;
    {
        int a = k1;
        int b = k2;
        if (a > b)
            swap(a, b);
        // a < b
        w -= a;
        w -= (b - a) / 2;
    }
    {
        int a = n - k2;
        int b = n - k1;
        if (a > b)
            swap(a, b);
        // a < b
        c -= a;
        c -= (b - a) / 2;
    }
    if (w <= 0 && c <= 0)
        cout << "YES\n";
    else
        cout << "NO\n";
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
        solveCase();
    return 0;
}