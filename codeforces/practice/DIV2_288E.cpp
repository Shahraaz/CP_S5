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

const int NAX = 600 + 5, MOD = 1000000007;

int f[NAX][NAX], l[NAX], r[NAX], tr[NAX][NAX];
char ans[2 * NAX];

int dp(int x, int y)
{
    if (x == y)
        return !l[x];
    int &res = f[x][y];
    if (res >= 0)
        return res;
    if (l[x] <= y - x && y - x <= r[x] && dp(x + 1, y))
        return res = 1;
    for (size_t i = x; i < y; i++)
        if (dp(x, i) && dp(i + 1, y))
        {
            tr[x][y] = i;
            return res = 1;
        }
    return res = 0;
}

void trace(int x, int y, int l, int r)
{
    if (!tr[x][y])
    {
        ans[l] = '(';
        ans[r] = ')';
        if (x == y)
            return;
        trace(x + 1, y, l + 1, r - 1);
    }
    else
    {
        int i = tr[x][y];
        trace(x, i, l, l + (i - x + 1) * 2 - 1);
        trace(i + 1, y, l + (i - x + 1) * 2, r);
    }
}

void solveCase()
{
    int n;
    cin >> n;
    for (size_t i = 1; i <= n; i++)
    {
        cin >> l[i] >> r[i];
        if (l[i] == r[i] && l[i] % 2 == 0)
        {
            cout << "IMPOSSIBLE\n";
            return;
        }
        l[i] /= 2;
        r[i] = (r[i] - 1) / 2;
    }
    memset(f, -1, sizeof f);
    if (!dp(1, n))
        cout << "IMPOSSIBLE\n";
    else
    {
        trace(1, n, 1, 2 * n);
        for (size_t i = 1; i <= 2 * n; i++)
            cout << ans[i];
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
