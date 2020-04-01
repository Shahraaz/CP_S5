// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#define pc(...)
#endif

#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 998244353;

const int _n = 1e5 + 10;
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

int mod_inv(int x, int mod = kmod)
{
    return power(x, kmod - 2);
}

void pre()
{
    Fact[0] = 1;
    for (int i = 1; i < _n; ++i)
        Fact[i] = mul(Fact[i - 1], i);
    Inv[_n - 1] = mod_inv(Fact[_n - 1]);
    for (int i = _n - 2; i >= 0; --i)
        Inv[i] = mul(Inv[i + 1], (1 + i));
}

int ncr(int n, int r)
{
    if (n < 0 || r < 0 || n - r < 0)
        return 0;
    return mul(Fact[n], mul(Inv[r], Inv[n - r]));
}

int pw[NAX];
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
        pw[0] = 1;
        for (size_t i = 0; i < n; i++)
            pw[i + 1] = mul(pw[i], 10);
        for (int i = 1; i <= n; i++)
        {
            if (i == n)
            {
                cout << 10 << '\n';
                break;
            }
            int res = 0;
            if (i <= n - 2)
                res = mul(810, mul(n - i - 1, pw[n - i - 2]));
            res = add(res, mul(180, pw[n - i - 1]));
            cout << res << ' ';
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