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
    ll n, c0, c1, h;
    cin >> n >> c0 >> c1 >> h;
    string str;
    cin >> str;
    int cnt_0 = count(all(str), '0');
    int cnt_1 = n - cnt_0;
    ll res = LLONG_MAX;
    for (size_t cnt_0_res = 0; cnt_0_res <= n; cnt_0_res++)
    {
        ll curr = 0;
        if (cnt_0_res <= cnt_0)
            curr += (cnt_0 - cnt_0_res) * h;
        else
            curr += -(cnt_0 - cnt_0_res) * h;
        curr += cnt_0_res * c0 + (n - cnt_0_res) * c1;
        res = min(res, curr);
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