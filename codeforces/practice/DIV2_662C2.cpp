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

const int NAX = 5e5 + 5, MOD = 1000000007;

int a[NAX];
ll ans1[NAX], ans2[NAX];

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        stack<pair<ll, ll>> lol;
        ll con1 = 0;
        for (int i = 1; i <= n; i++)
        {
            ll cur = 1;
            while (!lol.empty() && lol.top().f > a[i])
            {
                cur += lol.top().s;
                con1 -= lol.top().f * lol.top().s;
                lol.pop();
            }
            lol.push({a[i], cur});
            con1 += a[i] * (cur);
            ans1[i] = con1;
        }
        while (lol.size())
        {
            lol.pop();
        }
        con1 = 0;
        for (int i = n; i >= 1; i--)
        {
            ll cur = 1;
            while (!lol.empty() && lol.top().f > a[i])
            {
                cur += lol.top().s;
                con1 -= lol.top().f * lol.top().s;
                lol.pop();
            }
            lol.push({a[i], cur});
            con1 += a[i] * (cur);
            ans2[i] = con1 - a[i];
        }
        ll maxa = 0;
        for (int i = 1; i <= n; i++)
        {
            if (ans1[i] + ans2[i] > ans1[maxa] + ans2[maxa])
                maxa = i;
        }
        int mol = a[maxa];
        for (int i = maxa - 1; i > 0; i--)
        {
            mol = min(mol, a[i]);
            a[i] = mol;
        }
        mol = a[maxa];
        for (int i = maxa + 1; i <= n; i++)
        {
            mol = min(mol, a[i]);
            a[i] = mol;
        }
        for (int i = 1; i <= n; i++)
        {
            // cin >> a[i];
            cout << a[i] << ' ';
        }
        cout << '\n';
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
