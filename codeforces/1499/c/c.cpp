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
    vector<ll> c(n);
    for (auto &x : c)
        cin >> x;
    ll res = LLONG_MAX;
    ll prevOddmin = LLONG_MAX, prevOddSum = 0, Ocnt = 0;
    ll prevEvenmin = LLONG_MAX, prevEvenSum = 0, Ecnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (i & 1)
        {
            Ocnt++;
            prevOddmin = min(prevOddmin, c[i]);
            prevOddSum += c[i];
        }
        else
        {
            Ecnt++;
            prevEvenmin = min(prevEvenmin, c[i]);
            prevEvenSum += c[i];
        }
        if (prevOddmin == LLONG_MAX || prevEvenmin == LLONG_MAX)
            continue;
        ll now = 0;
        now += prevOddSum + prevEvenSum;
        now -= prevEvenmin;
        now -= prevOddmin;
        now += (n - Ocnt + 1) * prevOddmin;
        now += (n - Ecnt + 1) * prevEvenmin;
        res = min(res, now);
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