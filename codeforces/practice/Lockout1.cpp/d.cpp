// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

using u64 = ll;
using u128 = ll;

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
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        if (MillerRabin(n))
            cout << 1 << '\n'
                 << n << '\n';
        else if (MillerRabin(n - 2))
            cout << 2 << '\n'
                 << 2 << ' ' << n - 2 << '\n';
        else
        {
            cout << 3 << '\n'
                 << 3 << ' ';
            n -= 3;
            for (size_t i = 0; i < n; i++)
            {
                if (MillerRabin(i) && MillerRabin(n - i))
                {
                    cout << i << ' ' << n - i << '\n';
                    break;
                }
            }
            // cout << "Not Found\n";
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
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
