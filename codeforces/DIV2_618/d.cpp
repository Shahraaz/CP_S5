// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
#define pc(...) PC(#__VA_ARGS__, __VA_ARGS__);
template <typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> &p)
{
    out << '[' << p.first << ", " << p.second << ']';
    return out;
}
template <typename Arg>
void PC(const char *name, Arg &&arg)
{
    while (*name == ',' || *name == ' ')
        name++;
    std::cerr << name << " { ";
    for (const auto &v : arg)
        cerr << v << ' ';
    cerr << " }\n";
}
template <typename Arg1, typename... Args>
void PC(const char *names, Arg1 &&arg1, Args &&... args)
{
    while (*names == ',' || *names == ' ')
        names++;
    const char *comma = strchr(names, ',');
    std::cerr.write(names, comma - names) << " { ";
    for (const auto &v : arg1)
        cerr << v << ' ';
    cerr << " }\n";
    PC(comma, args...);
}
template <typename Arg1>
void ZZ(const char *name, Arg1 &&arg1)
{
    std::cerr << name << " = " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void ZZ(const char *names, Arg1 &&arg1, Args &&... args)
{
    const char *comma = strchr(names + 1, ',');
    std::cerr.write(names, comma - names) << " = " << arg1;
    ZZ(comma, args...);
}
#else
#define db(...)
#define pc(...)
#endif

using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

struct point //Replace double with int if not required
{
    ll x, y;

    point() {}

    point(ll x, ll y) : x(x), y(y) {}

    void operator=(const point &p)
    {
        x = p.x, y = p.y;
    }

    bool operator<(const point &p)
    {
        if (x == p.x)
            return y < p.y;
        return x < p.x;
    }

    point operator+(const point &p) const
    {
        point pt(x + p.x, y + p.y);
        return pt;
    }

    point operator-(const point &p) const
    {
        point pt(x - p.x, y - p.y);
        return pt;
    }

    double crossProduct(const point &p) const
    {
        return x * p.y - y * p.x;
    }

    int dotProduct(const point &p) const
    {
        return x * p.x + y * p.y;
    }

    double dist()
    {
        return x * x + y * y;
    }
};

bool comp(point &p1, point &p2)
{
    if (p1.x != p2.x)
        return p1.x < p2.x;
    return p1.y < p2.y;
}

bool cw(point &a, point &b, point &c)
{
    int area = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    return area < 0;
}

bool ccw(point &a, point &b, point &c)
{
    int area = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    return area > 0;
}

vector<point> convex_hull(vector<point> &v)
{
    if (v.size() == 1)
        return v;

    sort(v.begin(), v.end(), comp);

    point p1 = v[0], p2 = v.back();

    vector<point> up, down;
    up.push_back(p1);
    down.push_back(p1);

    for (int i = 1; i < v.size(); i++)
    {
        if (i == v.size() - 1 || cw(p1, v[i], p2))
        {
            while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], v[i]))
                up.pop_back();
            up.push_back(v[i]);
        }
        if (i == v.size() - 1 || ccw(p1, v[i], p2))
        {
            while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], v[i]))
                down.pop_back();
            down.push_back(v[i]);
        }
    }

    for (int i = down.size() - 2; i > 0; i--)
        up.push_back(down[i]);

    return up;
}

void solveCase()
{
    int n;
    cin >> n;
    vector<point> poly(n);
    for (int i = 0; i < n; i++)
        cin >> poly[i].x >> poly[i].y;
    vector<ll> dist;
    for (int i = 0; i < n; i++)
    {
        dist.pb((poly[i].x - poly[(i + 1) % n].x) * (poly[i].x - poly[(i + 1) % n].x) + (poly[i].y - poly[(i + 1) % n].y) * (poly[i].y - poly[(i + 1) % n].y));
    }
    ll a = dist[0];
    if (count(all(dist), a) == n)
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
#ifdef MULTI_TEST
    cin >> t;
#endif
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
