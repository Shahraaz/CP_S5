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

const int NAX = 5e5 + 5, MOD = 1000000007;

int n, k;
vector<pair<int, ll>> adj[NAX];
ll dp[2][NAX];

ll dfs(int node, int par, int state)
{
    auto &ret = dp[state][node];
    if (ret >= 0)
        return ret;
    ret = 0;
    int rem = k - state;
    priority_queue<ll> Q;
    for (auto &x : adj[node])
    {
        if (x.f == par)
            continue;
        auto a = dfs(x.f, node, 1);
        auto b = dfs(x.f, node, 0);
        ret += b;
        Q.push(x.s + a - b);
    }
    rem = min(rem, (int)Q.size());
    while (rem && Q.top() > 0)
    {
        rem--;
        ret += Q.top();
        Q.pop();
    }
    node++;
    db(node, par, state, ret);
    return ret;
}

void solveCase()
{
    cin >> n >> k;
    for (size_t i = 0; i < n; i++)
        dp[0][i] = dp[1][i] = -1;
    for (size_t i = 1; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    cout << dfs(0, 0, 0) << '\n';
    for (size_t i = 0; i < n; i++)
        adj[i].clear();
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
