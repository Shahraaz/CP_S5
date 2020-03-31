// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
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

const int NAX = 2e5 + 5, MOD = 1000000007;

const int _n = 1e5 + 10;
vector<int> Fact(_n), Inv(_n);
const int kmod = 1000000007;

inline int mul(int a, int b, int mod = kmod)
{
    return (long long)a * b % mod;
}

inline int add(int a, int b, int mod = kmod)
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

vector<int> adj[NAX];
int col[NAX];
bool good[NAX];
int cc[3];
int dp1[NAX], dp2[NAX];
pair<int, int> dfs1(int node, int par)
{
    pair<int, int> p = {0, 0};
    bool red = false, black = false;
    good[node] = false;
    for (auto &child : adj[node])
    {
        if (child == par)
            continue;
        // dfs1(child, node);
        auto v = dfs1(child, node);
        p.f += v.f;
        p.s += v.s;
        if (v.f && black && col[node] == 0)
            good[node] = true;
        if (v.s && red && col[node] == 0)
            good[node] = true;
        black = black || v.s;
        red = red || v.f;
    }
    if (col[node] == 0)
    {
        int remRed = cc[1] - p.f;
        int remBlack = cc[2] - p.s;
        if (remRed && black)
            good[node] = true;
        if (remBlack && red)
            good[node] = true;
    }
    else if (col[node] == 1)
        p.f++;
    else
        p.s++;
    return p;
}
void dfs2(int node, int par)
{
    ll val1, val2;
    val1 = val2 = 1;
    for (auto &child : adj[node])
    {
        if (child == par)
            continue;
        dfs2(child, node);
        val1 = val1 * (dp1[child] + 1LL + dp2[child]) % MOD;
        val2 = val2 * (dp2[child] + 1LL) % MOD;
    }
    if (good[node])
    {
        dp1[node] = val1;
        dp2[node] = 0;
    }
    else if (col[node] == 0)
    {
        dp1[node] = (val1 - val2 + MOD) % MOD;
        dp2[node] = val2;
    }
    else
        dp1[node] = dp2[node] = 0;
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
        for (size_t i = 1; i <= n; i++)
            adj[i].clear();
        for (size_t i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        cc[0] = cc[1] = cc[2] = 0;
        for (size_t i = 1; i <= n; i++)
        {
            cin >> col[i];
            cc[col[i]]++;
            dp1[i] = dp2[i] = 0;
        }
        dfs1(1, 1);
        dfs2(1, 1);
        ll ans = 0;
        for (size_t i = 1; i <= n; i++)
            ans = (ans + dp1[i]) % MOD;
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