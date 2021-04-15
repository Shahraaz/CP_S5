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
    long long X, d;
    cin >> X >> d;
    vector<long long> res;
    ll prev = 1 - d;
    while (X)
    {
        ll cnt = 1;
        while (true)
        {
            ll cnt_sq = (1 << (cnt + 1)) - 1;
            if (cnt_sq > X)
                break;
            cnt++;
        }
        X -= (1 << cnt) - 1;
        ll curr = prev + d;
        prev = curr;
        for (size_t i = 0; i < cnt; i++)
            res.pb(curr);
    }
    cout << res.size() << '\n';
    for (auto &x : res)
    {
        cout << x << ' ';
    }
    cout << '\n';
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