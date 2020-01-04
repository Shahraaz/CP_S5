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

using point = complex<long double>;

bool cmp(point a, point b)
{
    return arg(a) < arg(b);
}

void solveCase(int caseNo)
{
    vector<point> points;
    int n, x, y;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        cin >> x >> y;
        points.pb(point(x, y));
        // db(arg(points.back()));
    }
    db("here");
    ll res = 0;
    const auto pi = acosl(-1);
    for (size_t i = 0; i < n; i++)
    {
        // db(i);
        vector<long double> v2;
        for (size_t j = 0; j < n; j++)
        {
            // db(j);
            if (i != j)
            {
                v2.pb(arg(points[j]) < 0 ? (arg(points[j]) + 2 * pi) : arg(points[j]));
            }
        }
        db(i);
        pc(v2);
        for (int j = 0; j < n - 1; ++j)
        {
            v2.pb(v2[j] + 2 * pi);
        }
        sort(all(v2));
        pc(v2);
        for (int j = 0; j < n - 1; ++j)
        {
            auto it = upper_bound(v2.begin() + j, v2.begin() + j + n - 1, pi + v2[j]) - v2.begin() - j;
            if (it != 0)
                --it;
            int left = it, right = n - 1 - it;
            if (left > 0 && right > 0)
            {
                if (left > 1)
                    res += right * (left) * (left - 1) / 2;
                swap(left, right);
                if (left > 1)
                    res += right * (left) * (left - 1) / 2;
            }
        }
    }
    cout << res << '\n';
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
