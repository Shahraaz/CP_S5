#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

const int kmod = 1000000007;

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
    return power(x, mod - 2, mod);
}

// const int _n = 2e5 + 10;
// vector<int> Fact(_n), Inv(_n);

// void pre()
// {
//     Fact[0] = 1;
//     for (int i = 1; i < _n; ++i)
//         Fact[i] = mul(Fact[i - 1], i);
//     Inv[_n - 1] = mod_inv(Fact[_n - 1]);
//     for (int i = _n - 2; i >= 0; --i)
//         Inv[i] = mul(Inv[i + 1], (1 + i));
// }

// int ncr(int n, int r)
// {
//     if (n < 0 || r < 0 || n - r < 0)
//         return 0;
//     return mul(Fact[n], mul(Inv[r], Inv[n - r]));
// }

// int npr(int n, int r)
// {
//     if (n < 0 || r < 0 || n - r < 0)
//         return 0;
//     return mul(Fact[n], Inv[n - r]);
// }

void solveCase()
{
    int n;
    cin >> n;
    vector<int> val(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> val[i];
        if (val[i] < 0)
            val[i] += MOD;
    }
    db(n, val);
    vector<vector<int>> adj(n);
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<int> total(n), level(2);
    vector<vector<int>> sz(n, vector<int>(2));
    function<void(int, int, int)> dfs = [&](int node, int par, int d) -> void {
        int next = d ^ 1;
        level[d]++;
        total[node] = 1;
        sz[node][d] = 1;
        for (auto &x : adj[node])
        {
            if (x != par)
            {
                dfs(x, node, next);
                sz[node][0] += sz[x][0];
                sz[node][1] += sz[x][1];
                total[node] += total[x];
            }
        }
        db(node, par, d, level[d], total[node], sz[node]);
    };
    dfs(0, 0, 0);
    db(level);
    int ans = 0;
    function<void(int, int, int)> dfs2 = [&](int node, int par, int d) -> void {
        int next = d ^ 1;
        ans = add(ans, mul(val[node], n));
        for (auto &x : adj[node])
        {
            if (x != par)
            {
                dfs2(x, node, next);
                ans = add(ans, mul(val[node], mul(sz[x][d], n - total[x])));
                ans = sub(ans, mul(val[node], mul(sz[x][next], n - total[x])));
            }
            else
            {
                ans = add(ans, mul(val[node], mul(level[d] - sz[node][d], total[node])));
                ans = sub(ans, mul(val[node], mul(level[next] - sz[node][next], total[node])));
            }
        }
        db(node, par, d, ans);
    };
    dfs2(0, 0, 0);
    cout << ans << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}