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

vector<pair<ll, ll>> points;
ll xs, ys, t;

ll Abs(ll x)
{
    return x < 0 ? -x : x;
}

int Try(int idx)
{
    int down = idx;
    int up = points.size() - idx;
    int res = 0;
    for (int start = 0; start < points.size(); start++)
    {
        for (int end = start; end < points.size(); end++)
        {
            ll xCum = points[end].f - points[start].f;
            ll yCum = points[end].s - points[start].s;
            ll upCostx = Abs(points[end].f - xs);
            ll upCosty = Abs(points[end].s - ys);
            ll downCostx = Abs(points[start].f - xs);
            ll downCosty = Abs(points[start].s - ys);
            ll totalup = upCostx + upCosty;
            ll totaldown = downCostx + downCosty;
            if (totalup < totaldown)
            {
                ll T = totalup + xCum + yCum;
                if (T <= t)
                    res = max(res, end - start + 1);
            }
            else
            {
                ll T = totaldown + xCum + yCum;
                if (T <= t)
                    res = max(res, end - start + 1);
            }
        }
        db(start, res);
    }

    return res;
}

void solveCase(int caseNo)
{
    ll x0, y0, ax, ay, bx, by;
    cin >> x0 >> y0 >> ax >> ay >> bx >> by;
    cin >> xs >> ys >> t;
    points.pb({x0, y0});
    for (int i = 0; i < 60; i++)
    {
        using ld = long double;
        ld xnext = (ld)x0 * ax + bx;
        ld ynext = (ld)y0 * ay + by;
        db(xnext, ynext);
        db(xnext > 1e17, ynext > 1e17);
        if (xnext > (1e17) || ynext > (1e17))
            break;
        x0 = x0 * ax + bx;
        y0 = y0 * ay + by;
        points.push_back({x0, y0});
        db(points.back());
    }
    int idx = lower_bound(all(points), make_pair(xs, ys)) - points.begin();
    cout << Try(idx) << '\n';
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
