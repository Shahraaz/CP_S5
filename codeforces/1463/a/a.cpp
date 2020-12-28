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
    ll a, b, c;
    cin >> a >> b >> c;
    ll sum = a + b + c;
    if (sum % 9 == 0)
    {
        ll t = sum * 7 / 9;
        if (t / 7 <= min({a, b, c}))
        {
            cout << "Yes\n";
            return;
        }
    }
    cout << "No\n";
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