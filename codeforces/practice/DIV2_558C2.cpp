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

class Solution
{
private:
    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }

public:
    Solution() {}
    ~Solution() {}
    void Solve();
};

void Solution::Solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i].f >> v[i].s;
    vector<pair<int, pair<int, int>>> lines;
    map<pair<int, int>, set<int>> slope_map;
    int totalLineCnt = 0;
    ll res = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            int x1 = v[i].f, y1 = v[i].s;
            int x0 = v[j].f, y0 = v[j].s;
            int a = x1 - x0, b = y1 - y0;
            int g = gcd(a, b);
            a /= g, b /= g;
            if (a < 0 || (a == 0 && b < 0))
                a = -a, b = -b;
            ll c = a * y1 - b * x1;
            db(a, b, c);
            if (slope_map[{a, b}].find(c) == slope_map[{a, b}].end())
            {
                //It was not present
                totalLineCnt++;
                slope_map[{a, b}].insert(c);
                res += totalLineCnt - slope_map[{a, b}].size();
                db(totalLineCnt, res, slope_map[{a, b}].size());
                // pc(slope_map[{a, b}]);
#ifdef LOCAL
                for (auto slopes : slope_map)
                {
                    db(slopes.f);
                    pc(slopes.s);
                }
#else
                // for(auto slopes:slope_map)
                //     pc(slopes.s);
#endif
                db("\n");
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
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.Solve();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
