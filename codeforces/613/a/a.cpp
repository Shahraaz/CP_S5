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

// #define int long double

using ld = long double;
using Point = complex<ld>;
#define x real()
#define y imag()

void solveCase()
{
    int32_t n;
    cin >> n;
    Point p;
    int x1, y1;
    cin >> x1 >> y1;
    p = Point(x1, y1);
    db(p);
    Point points[n];
    ld mini = LLONG_MAX, maxi = 0;
    for (size_t i = 0; i < n; i++)
    {
        cin >> x1 >> y1;
        points[i] = Point(x1, y1);
        // cin >> points[i];
        points[i] -= p;
        db(points[i]);
        ld temp = norm(points[i]);

        mini = min(mini, temp);
        maxi = max(maxi, temp);
    }
    for (size_t i = 0; i < n; i++)
    {
        int32_t next = (i + 1) % n;
        Point perp = points[i] - points[next];
        db(points[i], points[next], perp);
        perp = conj(perp);
        db(perp);
        auto one = perp.x * points[i].x + perp.y * points[i].y;
        auto two = perp.x * points[next].x + perp.y * points[next].y;
        auto det = one * two;
        db(i, one, two, det, perp);
        if (one < 0 && two < 0)
        {
            perp = conj(perp);
            ld d = (perp.x * points[i].x + perp.y * points[i].y);
            d *= d;
            d /= norm(perp);
            mini = min(mini, d);
        }
    }
    const long double pi = acosl(-1);
    db("outside");
    cout << fixed << setprecision(10);
    cout << pi * (maxi - mini) << '\n';
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