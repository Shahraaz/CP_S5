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

int dp[201][201][4][4][5];
pair<int, int> nxt[201][201][4][4][5];

int solve(int a, int b, int pa, int pb, int gn)
{
    // db("solve", a, b, pa, pb, gn);
    if (pa == 0 && pb == 0)
        return a == 0 && b == 0;
    int &res = dp[a][b][pa][pb][gn];
    if (res != -1)
        return res;
    int mx = (gn < 4) ? 25 : 15;
    res = 0;
    if ((pb < pa && pb) || !pa)
    {
        for (int i = 0; i < mx - 1; i++)
            if (a >= i && b >= mx)
            {
                res |= solve(a - i, b - mx, pa, pb - 1, gn + 1);
                if (res)
                {
                    nxt[a][b][pa][pb][gn] = {i, mx};
                    return true;
                }
            }
        for (int i = mx + 1; i <= b; i++)
            if (a >= i - 2)
            {
                res |= solve(a - i + 2, b - i, pa, pb - 1, gn + 1);
                if (res)
                {
                    nxt[a][b][pa][pb][gn] = {i - 2, i};
                    return true;
                }
            }
    }
    else
    {
        for (int i = 0; i < mx - 1; i++)
            if (b >= i && a >= mx)
            {
                res |= solve(a - mx, b - i, pa - 1, pb, gn + 1);
                if (res)
                {
                    nxt[a][b][pa][pb][gn] = {mx, i};
                    return true;
                }
            }
        for (int i = mx + 1; i <= a; i++)
            if (b >= i - 2)
            {
                res |= solve(a - i, b - i + 2, pa - 1, pb, gn + 1);
                if (res)
                {
                    nxt[a][b][pa][pb][gn] = {i, i - 2};
                    return true;
                }
            }
    }
    return res;
}

void gen(int a, int b, int pa, int pb, int gn)
{
    db("gen", a, b, pa, pb, gn);
    if (pa == 0 && pb == 0)
        return;
    pair<int, int> p = nxt[a][b][pa][pb][gn];
    cout << p.f << ':' << p.s << ' ';
    gen(a - p.f, b - p.s, pa - (p.f > p.s), pb - (p.s > p.f), gn + 1);
}

void solveCase()
{
    memset(dp, -1, sizeof dp);
    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        int pa, pb;
        bool ok = false;
        if (!ok && solve(a, b, 3, 0, 0))
            ok = true, pa = 3, pb = 0;
        if (!ok && solve(a, b, 3, 1, 0))
            ok = true, pa = 3, pb = 1;
        if (!ok && solve(a, b, 3, 2, 0))
            ok = true, pa = 3, pb = 2;
        if (!ok && solve(a, b, 2, 3, 0))
            ok = true, pa = 2, pb = 3;
        if (!ok && solve(a, b, 1, 3, 0))
            ok = true, pa = 1, pb = 3;
        if (!ok && solve(a, b, 0, 3, 0))
            ok = true, pa = 0, pb = 3;
        if (ok)
        {
            db(t);
            cout << pa << ":" << pb << '\n';
            gen(a, b, pa, pb, 0);
            cout << '\n';
        }
        else
        {
            db(t);
            cout << "Impossible\n";
        }
    }
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
