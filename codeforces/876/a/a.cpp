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
    int a[3];
    cin >> n;
    cin >> a[0] >> a[1] >> a[2];
    int curr = 0;
    int res = 0;
    n--;
    if (n)
    {
        res = INT_MAX;
        res = min(res, n * a[0]);
        res = min(res, n * a[1]);
        res = min(res, a[0] + (n - 1) * a[2]);
        res = min(res, a[1] + (n - 1) * a[2]);
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}