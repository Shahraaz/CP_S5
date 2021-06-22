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
    vector<pair<ll, pair<ll, ll>>> rectangles;
    for (size_t i = 0; i < n; i++)
    {
        ll x, y;
        cin >> x >> y;
        rectangles.pb({x * y, {x, y}});
    }
    ll best = LLONG_MAX;
    sort(all(rectangles));
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (rectangles[j].second.first <= rectangles[i].second.first && rectangles[j].second.second <= rectangles[i].second.second)
                best = min(best, rectangles[i].first - rectangles[j].first);
        }
    }
    if (best == LLONG_MAX)
        best = -1;
    cout << best << '\n';
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