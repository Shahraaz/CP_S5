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
    vector<ll> man, dimond;
    for (size_t i = 0; i < 2 * n; i++)
    {
        int x, y;
        cin >> x >> y;
        x = abs(x);
        y = abs(y);
        if (x == 0)
            dimond.pb(y);
        else
            man.pb(x);
    }
    sort(all(dimond));
    sort(all(man));
    using ld = long double;
    ld res = 0;
    for (size_t i = 0; i < n; i++)
    {
        res += sqrtl(dimond[i] * dimond[i] + man[i] * man[i]);
    }
    cout << fixed << setprecision(10);
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