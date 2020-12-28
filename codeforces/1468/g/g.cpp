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
using point = complex<ld>;

const ld EPS = 1e-8;

bool cmp(const point &a, const point &b)
{
    return a.real() < b.real() ? 1 : (a.real() == b.real() ? a.imag() <= b.imag() : 0);
}

ld cross(point l, point r)
{
    return l.real() * r.imag() - l.imag() * r.real();
}

ld cross(point l, point r, point x)
{
    return cross(r - x, l - x);
}

struct Line
{
    point l, r;
    ld phase;
    Line(point l1, point r1) : l(l1), r(r1)
    {
        if (!cmp(l, r))
            swap(l, r);
        phase = arg(r - l);
    }
    Line(point p, ld phase)
    {
        l = p;
        r = polar((ld)100, phase);
        r = l + r;
        if (!cmp(l, r))
            swap(l, r);
        phase = arg(r - l);
    }
    ld getphase()
    {
        return phase;
    }
    point intersect(Line rhs)
    {
        auto d = cross(rhs.r - rhs.l, r - l);
        if (d <= EPS) // i f p a r a l l e l
        {
            if (cmp(r, rhs.r))
                return r;
            return rhs.r;
        }
        // return {-(s1.cross(e1, s2) == 0), P(0, 0)};
        auto p = cross(r, rhs.r, rhs.l), q = cross(rhs.r, l, rhs.l);
        // auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
        return (l * p + r * q) / d;
    }
};

void solveCase()
{
    int n, H;
    cin >> n >> H;
    vector<point> points(n);
    for (auto &x : points)
    {
        int a, b;
        cin >> a >> b;
        x = point(a, b);
    }
    point eye = points[n - 1] + point(0, H);
    db(n, H);
    db(points);
    db(eye);
    ld res = sqrtl(norm(points[n - 1] - points[n - 2]));
    Line prev(points[n - 2], eye);
    ld phase = prev.getphase();
    for (int i = n - 2; i > 0; i--)
    {
        Line l(points[i - 1], eye);
        Line r(points[i], eye);
        Line lr(points[i], points[i - 1]);
        db(phase, res);
        db(i, l.getphase(), r.getphase(), lr.getphase());
        if (l.getphase()  > phase + EPS)
        {
        }
        else
        {
            Line myline(eye, phase);
            auto mypnt = myline.intersect(lr);
            db(mypnt);
            res += sqrtl(norm(mypnt - points[i - 1]));
            phase = l.getphase();
        }
    }
    cout << res << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    cout << fixed << setprecision(10);
    cerr << fixed << setprecision(10);
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}