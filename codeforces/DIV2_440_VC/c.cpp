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

using u64 = uint64_t;
using u128 = uint64_t;

u64 binaryPower(u64 base, u64 e, u64 mod)
{
    u64 result = 1;
    base %= mod;
    while (e)
    {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool checkComposite(u64 n, u64 a, u64 d, int s)
{
    u64 x = binaryPower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    auto xCopy = x;
    for (int r = 1; r < s; ++r)
    {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

// bool MillerRabin1(u64 n)
// {
//     const int iter = 16;
//     if (n < 4)
//         return n == 2 || n == 3;
//     int s = 0;
//     u64 d = n - 1;
//     while ((d & 1) == 0)
//     {
//         d >>= 1;
//         s++;
//     }
//     for (int i = 0; i < iter; ++i)
//     {
//         int a = 2 + rand() % (n - 3);
//         if (checkComposite(n, a, d, s))
//             return false;
//     }
//     for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
//     {
//         if (n == a)
//             return true;
//         if (checkComposite(n, a, d, s))
//             return false;
//     }
//     return true;
// }

bool MillerRabin(u64 n)
{
    const int iter = 16;
    if (n < 4)
        return n == 2 || n == 3;
    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0)
    {
        d >>= 1;
        s++;
    }
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if (n == a)
            return true;
        if (checkComposite(n, a, d, s))
            return false;
    }
    return true;
}

class Solution
{
    int cache[17];

private:
    int solve(int x)
    {
        if (x < 17)
            return cache[x];
        int ret = -1;
        switch (x % 4)
        {
        case 0:
            ret = x / 4;
            break;
        case 1:
            ret = 1 + (x - 9) / 4;
            break;
        case 2:
            ret = 1 + (x - 6) / 4;
            break;
        case 3:
            ret = 2 + (x - 15) / 4;
            break;
        default:
            break;
        }
        return ret;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cache[0] = 0;
        cache[1] = -1;
        cache[2] = -1;
        cache[3] = -1;
        cache[4] = 1;
        cache[5] = -1;
        cache[6] = 1;
        cache[7] = -1;
        cache[8] = 2;
        cache[9] = 1;
        cache[10] = 2;
        cache[11] = -1;
        cache[12] = 3;
        cache[13] = 2;
        cache[14] = 3;
        cache[15] = 2;
        cache[16] = 4;
        int q;
        cin >> q;
        while (q--)
        {
            int x;
            cin >> x;
            db(x);
            cout << solve(x) << ' ';
#ifdef LOCAL
            // cout << x << '\n';
            cout << '\n';
#else
            cout << '\n';
#endif
        }
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
