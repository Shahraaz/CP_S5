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
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> xy(n);
    for (auto &x : xy)
        cin >> x.first >> x.second;
    int res = MOD;
    for (size_t i = 0; i < n; i++)
    {
        bool ok = true;

        for (size_t j = 0; j < n; j++)
        {
            int top = j;
            if ((abs(xy[i].first - xy[top].first) + abs(xy[i].second - xy[top].second)) <= k)
                ;
            else
                ok = false;
        }
        if (ok)
            res = 1;
        // res = min(res, *max_element(all(dist)));
    }
    if (res == MOD)
        res = -1;
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