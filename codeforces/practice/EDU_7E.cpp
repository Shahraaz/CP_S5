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

vector<int> adj[NAX];
ll leaves_on_level[NAX];

struct Solution
{
    int max_depth = 0;
    void dfs(int node, int par, int level)
    {
        bool isLeaf = true;
        for (auto &x : adj[node])
            if (x != par)
            {
                dfs(x, node, level + 1);
                isLeaf = false;
            }
        if (isLeaf)
        {
            max_depth = max(max_depth, level);
            leaves_on_level[level]++;
        }
    }
    Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        for (size_t i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        ll res = 0;
        for (auto &x : adj[1])
        {
            max_depth = 0;
            dfs(x, 1, 0);
            for (size_t i = 0; i < max_depth; i++)
                if (leaves_on_level[i] > 0)
                {
                    leaves_on_level[i + 1] += leaves_on_level[i] - 1;
                    leaves_on_level[i] = 0;
                }
            db(x, max_depth, leaves_on_level[max_depth]);
            res = max(res, max_depth + leaves_on_level[max_depth]);
            leaves_on_level[max_depth] = 0;
            max_depth = 0;
        }
        cout << res << '\n';
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
