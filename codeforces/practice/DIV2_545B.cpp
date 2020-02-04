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

void solveCase()
{
    vector<vector<int>> indicesOfTypes(4);
    int n;
    cin >> n;
    string s, b;
    cin >> s >> b;
    for (size_t i = 0; i < n; i++)
        indicesOfTypes[((s[i] - '0') << 1) + (b[i] - '0')].pb(i + 1);
    int na = indicesOfTypes[0].size();
    int nb = indicesOfTypes[1].size();
    int nc = indicesOfTypes[2].size();
    int nd = indicesOfTypes[3].size();
    for (int b = 0; b <= nb; b++)
    {
        for (int c = 0; c <= nc; c++)
        {
            int temp = nb + nd - c - b;
            if (temp >= 0)
                if (temp % 2 == 0)
                {
                    int d = temp / 2;
                    int a = n / 2 - b - c - d;
                    auto isValid = [](int a, int lim) -> bool {
                        return 0 <= a && a <= lim;
                    };
                    if (isValid(a, na) && isValid(b, nb) && isValid(c, nc) && isValid(d, nd))
                    {
                        for (size_t i = 0; i < a; i++)
                            cout << indicesOfTypes[0][i] << ' ';
                        for (size_t i = 0; i < b; i++)
                            cout << indicesOfTypes[1][i] << ' ';
                        for (size_t i = 0; i < c; i++)
                            cout << indicesOfTypes[2][i] << ' ';
                        for (size_t i = 0; i < d; i++)
                            cout << indicesOfTypes[3][i] << ' ';
                        return;
                    }
                }
        }
    }
    cout << -1 << '\n';
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
