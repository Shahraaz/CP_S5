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

int _n = 1e5 + 10;
vector<int> Fact(_n), Inv(_n);
const int kmod = 1000000007;

int mul(int a, int b, int mod = kmod)
{
    return (long long)a * b % mod;
}

int power(int base, int index, int mod = kmod)
{
    if (index == 0)
        return 1;
    int temp = power(base, index / 2, mod);
    temp = mul(temp, temp, mod);
    if (index & 1)
        temp = mul(temp, base, mod);
    return temp;
}

void pre()
{
    Fact[0] = 1;
    for (int i = 1; i < _n; ++i)
        Fact[i] = mul(Fact[i - 1], i);
    Inv[_n - 1] = power(Fact[_n - 1], kmod - 2);
    for (int i = _n - 2; i >= 0; --i)
        Inv[i] = mul(Inv[i + 1], (1 + i));
}

int ncr(int n, int r)
{
    if (n < 0 || r < 0 || n - r < 0)
        return 0;
    return mul(Fact[n], mul(Inv[r], Inv[n - r]));
}

int add(int a, int b)
{
    a += b;
    if (a >= MOD)
        a -= MOD;
    return a;
}

int n, k;
int a[51], f[51];
bool vis[51][51][2];
int cache[51][51][2][201];

int greedy()
{
    int ans = 0;
    int l1 = f[1], l2 = f[2];
    while ((l1 > 0 || l2 > 0) && ans <= 200)
    {
        int curk = k;
        int r1 = f[1] - l1;
        int r2 = f[2] - l2;
        db(l1, l2, r1, r2, ans, k);
        if (r1 == 0 && l1 != 0 || (r1 + r2 == 0))
        {
            while (l1 > 0 && curk > 0)
                l1--, curk--;
            while (l2 > 0 && curk > 1)
                l2--, curk -= 2;
        }
        else
        {
            while (l2 > 0 && curk > 1)
                l2--, curk -= 2;
            while (l1 > 0 && curk > 0)
                l1--, curk--;
        }
        ans++;
        db(l1, l2, curk);
        if (l1 + l2 == 0)
            break;
        r1 = f[1] - l1;
        r2 = f[2] - l2;
        if (r1)
            l1++;
        else
            l2++;
        ans++;
    }
    return ans;
}

int dp2(int l1, int l2, int side, int turns)
{
    if (turns == 0)
        return l1 == 0 && l2 == 0;
    int &ans = cache[l1][l2][side][turns];
    if (ans >= 0)
        return ans;
    ans = 0;
    if (!side)
    {
        for (int one = 0; one <= l1; one++)
            for (int two = 0; two <= l2; two++)
            {
                if (one + 2 * two > k)
                    break;
                if (one + two == 0)
                    continue;
                ans = add(ans, mul(ncr(l1, one), mul(ncr(l2, two), dp2(l1 - one, l2 - two, side ^ 1, turns - 1))));
            }
    }
    else
    {
        int r1 = f[1] - l1;
        int r2 = f[2] - l2;
        for (int one = 0; one <= r1; one++)
            for (int two = 0; two <= r2; two++)
            {
                if (one + 2 * two > k)
                    break;
                if (one + two == 0)
                    continue;
                ans = add(ans, mul(ncr(r1, one), mul(ncr(r2, two), dp2(l1 + one, l2 + two, side ^ 1, turns - 1))));
            }
    }
    return ans;
}

void solveCase(int caseNo)
{
    pre();
    memset(cache, -1, sizeof cache);
    cin >> n >> k;
    k /= 50;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i] /= 50;
        f[a[i]]++;
    }
    int ans1 = greedy();
    if (ans1 > 200)
    {
        cout << "-1\n0";
        return;
    }
    cout << ans1 << '\n'
         << dp2(f[1], f[2], 0, ans1) << '\n';
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
