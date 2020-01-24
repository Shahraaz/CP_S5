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

const int NAX = 1e5 + 5, MOD = 1000000007;

using point = complex<long long>;

typedef long long typeone;
typedef long double typetwo;
enum
{
    LEFT,
    RIGHT,
    BEYOND,
    BEHIND,
    BETWEEN,
    ORIGIN,
    DESTINATION
};

const long double EPS = 1e-9;
class point
{
public:
    typeone x, y;
    point(typeone _x = 0, typeone _y = 0) : x(_x), y(_y) {}
    bool operator<(const point &p) const
    {
        return (x < p.x) || (x == p.x && y < p.y);
    }
    bool operator>(point &p)
    {
        return (x > p.x) || (x == p.x && y > p.y);
    }
    bool operator==(point &p)
    {
        return x == p.x && y == p.y;
    }
    bool operator!=(point &p)
    {
        return !(*this == p);
    }
    point operator=(const point &p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }
    point operator*(typetwo s)
    {
        return point(s * x, s * y);
    }
    point operator+(point &p)
    {
        return point(x + p.x, y + p.y);
    }
    point operator-(point &p)
    {
        return point(x - p.x, y - p.y);
    }
    typeone operator[](const int i)
    {
        return i == 0 ? x : y;
    }
    typeone orientation(point p0, point p1, point p2)
    {
        p1 = p1 - p0;
        p2 = p2 - p0;
        typeone sa = p1.x * p2.y - p2.x * p1.y;
        if (sa > 0)
            return 1;
        if (sa < 0)
            return -1;
        return 0;
    }
    typeone len2()
    {
        return x * x + y * y;
    }
    typetwo len()
    {
        return sqrtl((long double)len2());
    }

    typetwo PolarAngle()
    {
        if (x == 0 && y == 0)
            return 0;
        if (x == 0)
            return (y > 0) ? 90 : 270;
        typetwo theta = atanf((long double)y / x);
        theta *= 180 / (long double)3.141592653;
        if (x > 0)
            return y >= 0 ? theta : 360 + theta;
        else
            return 180 + theta;
    }
    int classify(point &p0, point &p1)
    {
        point p2 = *this;
        point a = p1 - p0;
        point b = p2 - p0;
        typeone sa = a.x * b.y - b.x * a.y;
        if (sa > 0)
            return LEFT;
        if (sa < 0)
            return RIGHT;
        if ((a.x * b.x < 0) || (a.y * b.y < 0))
            return BEHIND;
        if (a.len2() < b.len2())
            return BEYOND;
        if (p0 == p2)
            return ORIGIN;
        if (p0 == p1)
            return DESTINATION;
        return BETWEEN;
    }
};

point a[NAX], b[NAX];

void solveCase(int caseNo)
{
    int n;
    cin >> n;
}

int main()
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
        solveCase(i);
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
