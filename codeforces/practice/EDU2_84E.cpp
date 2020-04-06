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

const int NAX = 5e5 + 5, MOD = 998244353;

const int _n = 5e5 + 10;
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

int ones[NAX], mx[NAX], sum[NAX];
pair<pair<int, int>, int> q[NAX];

class Solution
{
private:
    int n, k, m;
    int solve(int pos)
    {
        memset(ones, 0, sizeof ones);
        memset(mx, -1, sizeof mx);
        for (size_t i = 0; i < m; i++)
            if (q[i].s & (1 << pos))
            {
                ones[q[i].f.f]++;
                ones[q[i].f.s + 1]--;
            }
            else
                mx[q[i].f.s] = max(mx[q[i].f.s], q[i].f.f);
        int j = -1;
        for (size_t i = 1; i <= n; i++)
        {
            int cur = 0;
            if (ones[i] == 0)
            {
                cur = sum[i];
                if (j == -1)
                    cur = add(cur, 1);
                else
                    cur = sub(cur, sum[j]);
            }
            // cout << ones[i] << ' ' << sum[i] << '\n';
            // cout << i - 1 << ' ' << cur << '\n';
            // cout << "---------\n";
            sum[i + 1] = add(sum[i], cur);
            ones[i + 1] += ones[i];
            j = max(j, mx[i]);
        }
        return add(sum[n + 1], j == -1 ? 1 : sub(0, sum[j])) % MOD;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n >> k >> m;
        for (size_t i = 0; i < m; i++)
        {
            cin >> q[i].f.f >> q[i].f.s >> q[i].s;
        }
        int ans = 1;
        for (size_t i = 0; i < k; i++)
            ans = mul(ans, solve(i));
        cout << ans << '\n';
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