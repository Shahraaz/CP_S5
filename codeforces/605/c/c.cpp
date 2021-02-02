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
const int NAX = 2e6 + 5, MOD = 1000000007;

using ld = long double;
using coord_t = long long;
using coord2_t = long long;

// typedef long long coord_t;  // coordinate type
// typedef long long coord2_t; // must be big enough to hold 2*max(|coordinate|)^2

struct Point
{
    coord_t x, y;
    bool operator<(const Point &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
};

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
coord2_t cross(const Point &O, const Point &A, const Point &B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(vector<Point> &P)
{
    size_t n = P.size(), k = 0;
    if (n < 3)
        return P;
    vector<Point> H(2 * n);
    // Sort points lexicographically
    sort(P.begin(), P.end());
    // Build lower hull
    for (size_t i = 0; i < n; ++i)
    {
        while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0)
            k--;
        H[k++] = P[i];
    }
    // Build upper hull
    for (size_t i = n - 1, t = k + 1; i > 0; --i)
    {
        while (k >= t && cross(H[k - 2], H[k - 1], P[i - 1]) <= 0)
            k--;
        H[k++] = P[i - 1];
    }
    H.resize(k - 1);
    return H;
}

double polygonArea(vector<Point> Polygon)
{
    // Initialze area
    long long area = 0;
    int n = Polygon.size();
    // Calculate value of shoelace formula
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        area += ((ll)Polygon[j].x + Polygon[i].x) * (Polygon[j].y - Polygon[i].y);
        // area += (X[j] + X[i]) * (Y[j] - Y[i]);
        j = i; // j is previous vertex to i
    }

    // Return absolute value
    return abs(area / 2.0);
}

void solveCase()
{
    int n;
    cin >> n;
    ll p, q;
    cin >> p >> q;
    vector<Point> polygon;
    set<pair<int, int>> ss;
    int maxx = 0, maxy = 0;
    for (size_t i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        maxx = max(x, maxx);
        maxy = max(y, maxy);
        if (ss.count({x, y}) == 0)
        {
            ss.insert({x, y});
            polygon.pb(Point{x, y});
            // cin >> polygon[i].x >> polygon[i].y;
        }
    }
    // polygon.pb(Point{0, 0});
    // polygon.pb(Point{maxx, 0});
    // polygon.pb(Point{0, maxy});
    polygon = convex_hull(polygon);
    const ld EPS = 1e-10;
    auto intersect = [&](Point a, Point b, Point c, Point d, bool &ok) -> pair<ld, ld> {
        if (a.x > b.x)
            swap(a, b);
        ok = true;
        auto oa = cross(c, d, a);
        auto ob = cross(c, d, b);
        // auto oc = cross(a, b, c);
        // auto od = cross(a, b, d);

        pair<ld, ld> ret;
        ret.first = (ld)a.x * ob - (ld)b.x * oa;
        ret.second = (ld)a.y * ob - (ld)b.y * oa;

        if ((abs(ob - oa)) <= EPS)
        {
            // ok = false;
            ret.first = b.x;
            ret.second = b.y;
            return ret;
        }

        ret.first /= ob - oa;
        ret.second /= ob - oa;
        db(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y);
        db(ret.first, ret.second);

        if (a.x <= (ret.first + EPS) && ret.first <= (b.x + EPS))
            ;
        else
            ok = false;

        if (a.y > b.y)
            swap(a, b);
        if (a.y <= (ret.second + EPS) && ret.second <= (b.y + EPS))
            ;
        else
            ok = false;

        return ret;
    };
    ld res = 2e15;
    auto compute = [&](pair<ld, ld> point) -> ld {
        db(point, point.first <= EPS, point.second <= EPS);
        if (point.first <= EPS)
            return 1e15;
        if (point.second <= EPS)
            return 1e15;
        ld ret = max(p / point.first, q / point.second);
        db(ret);

        return ret;
    };
    ll pNAX = p * NAX, qNAX = q * NAX;
    Point inf{pNAX, qNAX};
    db(inf.x, inf.y);
    for (size_t i = 0; i < polygon.size(); i++)
    {
        db(polygon[i].x, polygon[i].y);
        int j = (1 + i) % polygon.size();
        res = min(res, compute(pair<ld, ld>(polygon[i].x, polygon[i].y)));
        if (i == j)
            continue;
        bool ok = false;
        auto point = intersect(polygon[i], polygon[j], Point{0, 0}, inf, ok);
        db(ok, point);
        if (ok)
        {
            res = min(res, compute(point));
        }
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}