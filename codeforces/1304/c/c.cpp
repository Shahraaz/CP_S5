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
#define int ll

void solveCase()
{
    int n;
    cin >> n;

    int l, r, prev = 0;
    cin >> l;
    r = l;

    map<int, pair<int, int>> ranges;
    bool ok = true;
    for (size_t i = 0; i < n; i++)
    {
        int t, low, row;
        cin >> t >> low >> row;
        if (ranges.find(t) == ranges.end())
            ranges[t] = {low, row};
        else
        {
            ranges[t].first = max(ranges[t].first, low);
            ranges[t].second = min(ranges[t].second, row);
            if (ranges[t].first > ranges[t].second)
                ok = false;
        }
    }
    if (!ok)
    {
        cout << "NO" << '\n';
        return;
    }
    for (auto &x : ranges)
    {
        int lim = x.first - prev;
        prev += lim;
        l -= lim;
        r += lim;
        l = max(l, x.second.first);
        r = min(r, x.second.second);
        if (l > r)
        {
            cout << "NO" << '\n';
            return;
        }
    }
    cout << "YES\n";
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