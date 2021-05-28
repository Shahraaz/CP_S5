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
    int n, m;
    cin >> n >> m;
    db(n, m);
    vector<set<pair<int, int>>> intervals(3 * n);
    for (size_t i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        --x, --y;
        db(x, y);
        if (y < x)
            y += n;
        intervals[x].insert({y - x, i});
        intervals[x + n].insert({y - x, i});
    }
    vector<int> res(n);
    int cnt = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if (intervals[i].empty())
        {
            if (cnt)
                res[i] = (i + 1 < n) ? res[i + 1] + 1 : 0;
            continue;
        }
        cnt++;
        int now = i + (intervals[i].size() - 1) * n + (intervals[i].begin())->first;
        res[i] = max((i + 1 < n) ? res[i + 1] + 1 : 0, now);
        db(i, res[i], now, intervals[i]);
    }
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