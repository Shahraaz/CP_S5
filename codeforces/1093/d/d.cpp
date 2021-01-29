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
const int NAX = 3e5 + 5, MOD = 998244353;

int pow2[NAX];

int mul(int a, int b)
{
    return (a * 1LL * b) % MOD;
}

int add(int a, int b)
{
    a += b;
    if (a >= MOD)
        a -= MOD;
    return a;
}

int sub(int a, int b)
{
    a -= b;
    if (a < 0)
        a += MOD;
    return a;
}

int pre()
{
    pow2[0] = 1;
    for (size_t i = 1; i < NAX; i++)
        pow2[i] = mul(pow2[i - 1], 2);
}

void solveCase()
{
    int n, m;
    cin >> n >> m;
    ll res = 1;
    vector<vector<int>> adj(n);
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    queue<int> Q;
    vector<int> vis(n), isE(n);
    for (size_t i = 0; i < n; i++)
    {
        if (vis[i])
            continue;
        vis[i] = 1;
        Q.push(i);
        int e = 1, o = 0;
        isE[i] = 1;
        while (Q.size())
        {
            auto top = Q.front();
            Q.pop();
            for (auto &x : adj[top])
                if (!vis[x])
                {
                    vis[x] = 1;
                    Q.push(x);
                    isE[x] = !isE[top];
                    e += isE[x];
                    o += !isE[x];
                }
                else if (isE[x] == isE[top])
                {
                    cout << 0 << '\n';
                    return;
                }
        }
        res = mul(res, add(pow2[o], pow2[e]));
    }
    cout << res << '\n';
}

int32_t main()
{
    pre();
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}