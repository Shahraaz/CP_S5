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

using ld = long double;
const ld EPS = 1e-9;

bool leq(ld a, ld b) { return b - a >= -EPS; }
bool le(ld a, ld b) { return b - a > EPS; }
bool eq(ld a, ld b) { return abs(a - b) <= EPS; }

struct point
{
    ld x, y;

    point() {}
    point(ld x, ld y) : x(x), y(y) {}

    point operator+(const point &p) const { return point(x + p.x, y + p.y); }
    point operator-(const point &p) const { return point(x - p.x, y - p.y); }
    point operator/(const ld &t) const { return point(x / t, y / t); }
    point operator*(const ld &t) const { return point(x * t, y * t); }

    ld dot(const point &p)
    {
        return x * p.x + y * p.y;
    }

    ld cross(const point &p)
    {
        return x * p.y - y * p.x;
    }

    ld length() { return sqrtl(x * x + y * y); }
    point unit() { return (*this) / length(); }
};

pair<int, point> get_intersection(point &a1, point &v1, point &a2, point &v2)
{
    ld det = v1.cross(v2);
    if (eq(det, 0))
    {
        if (eq((a2 - a1).cross(v1), 0))
            return {-1, point(0, 0)};
        else
            return {0, point(0, 0)};
    }

    point x = a1 + v1 * ((a2 - a1).cross(v2) / det);
    return {1, x};
}

ld get_area(vector<point> &P)
{
    int n = P.size();
    ld ans = 0.0;

    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        ans += P[i].cross(P[j]);
    }

    return fabs(ans) / 2.0;
}

struct plane
{
    point p, pq;
    ld ang;
    plane() {}
    plane(point p, point q) : p(p), pq(q - p)
    {
        ang = atan2(pq.y, pq.x);
    }

    bool operator<(const plane &a) { return ang < a.ang; }
};

//con respecto al plano a, la interseccion de b y c NO esta a la izquierda?
bool is_bad(plane &a, plane &b, plane &c)
{
    int info;
    point x;
    tie(info, x) = get_intersection(b.p, b.pq, c.p, c.pq);
    if (info != 1)
        return false;
    return leq(a.pq.cross(x - a.p), 0); //le
}

const ld dinf = 1e100;
vector<point> plane_intersection(vector<plane> &p)
{
    vector<point> aux = {{-dinf, -dinf}, {dinf, -dinf}, {dinf, dinf}, {-dinf, dinf}};
    for (int i = 0; i < 4; i++)
    {
        int j = (i + 1) % 4;
        p.push_back(plane(aux[i], aux[j]));
    }

    sort(p.begin(), p.end());

    int n = p.size();
    vector<plane> dq(n + 10);
    int s = 1, e = 0;

    for (int i = 0; i < n; i++)
    {
        while (s < e && is_bad(p[i], dq[e], dq[e - 1]))
            e--;
        while (s < e && is_bad(p[i], dq[s], dq[s + 1]))
            s++;
        dq[++e] = p[i];

        //caso especial donde son planos paralelos
        if (s < e && eq(abs(dq[e].pq.cross(dq[e - 1].pq)), 0))
        {
            //si apuntan en lados contrarios
            if (leq(dq[e].pq.dot(dq[e - 1].pq), 0))
                return {};
            e--;
            if (leq(p[i].pq.cross(dq[e].p - p[i].p), 0))
            {
                dq[e] = p[i];
            }
        }
    }

    while ((e - s + 1) > 2 && is_bad(dq[s], dq[e], dq[e - 1]))
        e--;
    while ((e - s + 1) > 2 && is_bad(dq[e], dq[s], dq[s + 1]))
        s++;

    if ((e - s + 1) < 3)
        return {};
    vector<point> res;
    dq[e + 1] = dq[s];
    for (int i = s; i <= e; i++)
    {
        res.push_back(get_intersection(dq[i].p, dq[i].pq, dq[i + 1].p, dq[i + 1].pq).second);
    }
    return res;
}

void solveCase()
{
    int n;
    cin >> n;

    vector<plane> todos;
    vector<point> P;
    while (n--)
    {
        int c;
        cin >> c;
        P.clear();
        P.resize(c);

        for (int i = 0; i < c; i++)
            cin >> P[i].x >> P[i].y;

        for (int i = 0; i < c; i++)
        {
            int j = (i + 1) % c;
            todos.push_back(plane(P[i], P[j]));
        }
    }

    P = plane_intersection(todos);

    cout << fixed << setprecision(10) << get_area(P) << endl;
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