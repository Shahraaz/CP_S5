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
    long long n, k;
    cin >> n >> k;
    long long res = LLONG_MAX;
    long long dec = 0;
    for (size_t i = 1; i <= n; i++)
    {
        long long p, s;
        cin >> p >> s;
        if (i % 5 == 0)
            dec += k;
        s -= dec;
        if (s > 0)
            res = min(res, p);
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
        solveCase();
    return 0;
}