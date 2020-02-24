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

const int NAX = 2e5 + 5, MOD = 998244353;

const int _n = 3e5 + 10;
vector<int> Fact(_n), Inv(_n);
const int kmod = 998244353;

int mul(int a, int b, int mod = kmod)
{
    return (long long)a * b % mod;
}

int add(int a, int b, int mod = kmod)
{
    a += b;
    if (a >= mod)
        a -= mod;
    return a;
}

int sub(int a, int b, int mod = kmod)
{
    a -= b;
    if (a < 0)
        a += mod;
    return a;
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

class Solution
{
private:
public:
    Solution()
    {
        pre();
    }
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        vector<pair<int, int>> c(n);
        map<int, map<int, int>> byFirst;
        map<int, map<int, int>> bySecond;
        map<pair<int, int>, int> meow;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            cin >> b[i];
            c[i] = {a[i], b[i]};
            byFirst[a[i]][b[i]]++;
            bySecond[b[i]][a[i]]++;
            meow[{a[i], b[i]}]++;
        }
        sort(all(c));
        ll bad = 1;
        for (auto &element : byFirst)
        {
            int denominator = 1;
            ll totalCnt = 0;
            for (auto &elem : element.s)
                totalCnt += elem.s;
            bad = mul(bad, Fact[totalCnt]);
        }
        db(bad);
        int temp = bad;
        bad = 1;
        db(bad, "---------");
        for (auto &element : bySecond)
        {
            int denominator = 1;
            ll totalCnt = 0;
            for (auto &elem : element.s)
                totalCnt += elem.s;
            bad = mul(bad, Fact[totalCnt]);
        }
        db(bad);
        bad = add(bad, temp);
        ll total = Fact[n];
        temp = 1;
        vector<int> kk;
        for (int i = 0; i < n; i++)
        {
            kk.pb(c[i].s);
            /* code */
        }
        for (auto &elem : meow)
            temp = mul(temp, Fact[elem.s]);
        if (is_sorted(all(kk)) == 0)
            temp = 0;
        db(total, bad);
        db(temp);

        // db(MOD + MOD);
        // db(MOD + (ll)MOD);
        cout << sub(total, sub(bad, temp)) << '\n';
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
