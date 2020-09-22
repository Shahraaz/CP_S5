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

//Here it is an unweighted tree
//If you want to solve for thath then
//You have to go for Dist(a,b) = Dist(a) + Dist(b) - 2*Dist(lca(a,b))
// where Dist(a) is distance from Root to a;
struct LeastCommonAncestor
{
    vector<int> Level, sizes;
    vector<vector<int>> dp;
    vector<vector<int>> Adj;
    int Log;
    LeastCommonAncestor() {}
    LeastCommonAncestor(vector<vector<int>> &Tree) : Adj(Tree)
    {
        int n = Tree.size();
        Log = ceil(log2(n)) + 1;
        dp.assign(Log, vector<int>(n));
        Level.assign(n, 0);
        sizes.assign(n, 0);
        dfs(0, 0, 0);
        for (int i = 1; i < Log; ++i)
            for (int j = 0; j < n; ++j)
                dp[i][j] = dp[i - 1][dp[i - 1][j]];
    }
    void dfs(int node, int parent, int level)
    {
        dp[0][node] = parent;
        Level[node] = level;
        sizes[node] = 1;
        for (auto child : Adj[node])
            if (child != parent)
            {
                dfs(child, node, level + 1);
                sizes[node] += sizes[child];
            }
    }
    int lca(int a, int b)
    {
        if (Level[a] > Level[b])
            swap(a, b);
        int d = Level[b] - Level[a];
        for (int i = 0; i < Log; ++i)
            if (d & (1 << i))
                b = dp[i][b];
        if (a == b)
            return a;
        for (int i = Log - 1; i >= 0; --i)
            if (dp[i][a] != dp[i][b])
            {
                a = dp[i][a];
                b = dp[i][b];
            }
        return dp[0][a];
    }
    int dist(int a, int b)
    {
        return Level[a] + Level[b] - 2 * Level[lca(a, b)];
    }
};

void solveCase()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    LeastCommonAncestor lca(adj);
    int m;
    cin >> m;
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        if (u == v)
        {
            cout << n << '\n';
            continue;
        }
        int d = lca.dist(u, v);
        if (d & 1)
            cout << 0 << '\n';
        else
        {
            int lca_u_v = lca.lca(u, v);
            int dist_u_lca = lca.dist(u, lca_u_v);
            int dist_v_lca = lca.dist(v, lca_u_v);
            auto find_kth_from_u = [&](int k) -> int {
                if (dist_u_lca == k)
                    return lca_u_v;
                if (dist_u_lca > k)
                {
                    int b = u;
                    for (int i = 0; i < lca.Log; ++i)
                        if (k & (1 << i))
                            b = lca.dp[i][b];
                    return b;
                }
                // if (dist_u_lca == k)
                k = d - k;
                int b = v;
                for (int i = 0; i < lca.Log; ++i)
                    if (k & (1 << i))
                        b = lca.dp[i][b];
                return b;
            };
            db("kth", d / 2);
            int prevNode = find_kth_from_u(d / 2 - 1);
            int targetNode = find_kth_from_u(d / 2);
            int NextNode = find_kth_from_u(d / 2 + 1);
            db(prevNode, targetNode, NextNode);
            // cout << prevNode << ' ' << targetNode << NextNode << '\n';
            ll res = 0;
            if (lca.dp[0][targetNode] == prevNode)
            {
                res = lca.sizes[targetNode] - lca.sizes[NextNode];
            }
            else if (lca.dp[0][targetNode] == NextNode)
            {
                res = lca.sizes[targetNode] - lca.sizes[prevNode];
            }
            else
            {
                res = n;
                res -= lca.sizes[NextNode] + lca.sizes[prevNode];
            }
            cout << res << '\n';
        }
    }
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
