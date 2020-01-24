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

const int NAX = 2e6 + 5, MOD = 1000000007;

int f[NAX];

void fenwAdd(int i, int w)
{
    for (; i < NAX; i |= (i + 1))
        f[i] += w;
}

int fenwSum(int i)
{
    int s = 0;
    for (; i >= 0; i &= i + 1, --i)
        s += f[i];
    return s;
}

void solveCase(int caseNo)
{
    int n;
    cin >> n;
    vector<int> p(n), q(n);
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
        --p[i];
        q[p[i]] = i;
    }
    set<int> lh, rh;
    ll inv = 0, ls = 0, rs = 0;
    for (int i = 0; i < n; i++)
    {
        inv += i - fenwSum(q[i]);
        fenwAdd(q[i], 1);
        if (lh.empty() || q[i] <= *lh.rbegin())
            lh.insert(q[i]), ls += q[i];
        else
            rh.insert(q[i]), rs += q[i];
        while (rh.size() > lh.size())
        {
            int x = *rh.begin();
            rs -= x;
            ls += x;
            rh.erase(x);
            lh.insert(x);
        }
        while (lh.size() > rh.size() + 1)
        {
            int x = *lh.rbegin();
            ls -= x;
            rs += x;
            lh.erase(x);
            rh.insert(x);
        }
        ll ans = inv;
        ll x = *lh.rbegin(), L = lh.size(), R = rh.size();
        ans += x * L - L * (L - 1) / 2 - ls;
        ans += rs - x * R - R * (R + 1) / 2;
        cout << ans << ' ';
    }
    cout << '\n';
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
