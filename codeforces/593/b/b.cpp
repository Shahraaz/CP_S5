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
    ll x1, x2;
    cin >> x1 >> x2;
    vector<pair<ll, ll>> points1, points2;
    ll maxy = LLONG_MIN, miny = LLONG_MAX;
    for (size_t i = 0; i < n; i++)
    {
        ll k, b;
        cin >> k >> b;
        auto y1 = k * x1 + b;
        auto y2 = k * x2 + b;
        db(i, y1, y2);
        // if (y1 > y2)
        //     swap(y1, y2);
        // if (k >= 0)
        // {
            points1.pb({y1, y2});
        // }
        // else
        // {
        //     points2.pb({y1, y2});
        // }
    }
    sort(all(points1));
    sort(all(points2));
    auto check = [](vector<pair<ll, ll>> &points) -> bool {
        if (points.empty())
            return false;
        db(points);
        for (size_t i = 0; i + 1 < points.size(); i++)
            if (points[i + 1].second < points[i].second)
                return true;
        return false;
    };
    auto check2 = [](vector<pair<ll, ll>> a, vector<pair<ll, ll>> b) -> bool {
        if (a.empty() || b.empty())
            return false;
        return false;
    };
    if (check(points1) || check(points2) || check2(points1, points2))
        cout << "YES\n";
    else
        cout << "NO\n";
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