//Optimise
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
auto TimeStart = chrono::steady_clock::now();

const int NAX = 2e5 + 10, MOD = 1000000007;
using u64 = uint64_t;
using u128 = __uint128_t;

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

// bool MillerRabin3(u64 n)
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
//     // for (int i = 0; i < iter; ++i)
//     // {
//     //     int a = 2 + rand() % (n - 3);
//     //     if (checkComposite(n, a, d, s))
//     //         return false;
//     // }
//     for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
//     {
//         if (n == a)
//             return true;
//         if (checkComposite(n, a, d, s))
//             return false;
//     }
//     return true;
// }

void solveCase(int caseNo)
{
    int cnt = 0;
    for (int i = 1; i < 1000000; ++i)
        cnt += MillerRabin(i);
    cout << cnt << '\n';
    cout << 50847534 << '\n';
    while (true)
    {
        ll n;
        cin >> n;
        if (n == 0)
            break;
        cout << MillerRabin(n) << '\n';
    }

    // All three versions pass the test
    // If both deterministic and non deterministic are used time 1997.46s
    // If only deterministic is used time 1333.03 s
    // If only non-deterministic is used time 1509.77 s
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
        cout << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}