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
// std::mt19937 rng(seed);
// template <typename T>
// using Random = std::uniform_int_distribution<T>;

const int NAX = 2e3 + 5, MOD = 1000000007;

int b[NAX][NAX];
string s[NAX];

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++)
            cin >> s[i];
        for (int i = 0; i < n; i++)
        {
            int l = 0;
            while (l < n && s[i][l] == 'W')
                ++l;
            if (l >= n)
            {
                ++b[0][0];
                continue;
            }
            int r = n - 1;
            while (r >= 0 && s[i][r] == 'W')
            {
                --r;
            }
            if (r - l + 1 > k)
                continue;
            ++b[max(i - k + 1, 0)][max(r - k + 1, 0)];
            --b[max(i - k + 1, 0)][l + 1];
            --b[i + 1][max(r - k + 1, 0)];
            ++b[i + 1][l + 1];
        }
        for (int j = 0; j < n; j++)
        {
            int l = 0;
            while (l < n && s[l][j] == 'W')
                ++l;
            if (l >= n)
            {
                ++b[0][0];
                continue;
            }
            int r = n - 1;
            while (r >= 0 && s[r][j] == 'W')
                --r;
            if (r - l + 1 > k)
                continue;
            ++b[max(r - k + 1, 0)][max(j - k + 1, 0)];

            --b[max(r - k + 1, 0)][j + 1];

            --b[l + 1][max(j - k + 1, 0)];

            ++b[l + 1][j + 1];
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; ++j)
                b[i][j + 1] += b[i][j];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; ++j)
                b[i + 1][j] += b[i][j];
        int ans = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; ++j)
                ans = max(ans, b[i][j]);
        cout << ans;
    }
};

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
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
