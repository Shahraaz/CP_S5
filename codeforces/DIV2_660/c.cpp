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

const int NAX = 1e5 + 5, MOD = 1000000007;

vector<int> adj[NAX];
int p[NAX];
int pop[NAX];
int HappySubtree[NAX];
int h[NAX];
// int degree[NAX];
// int sad[NAX], happy[NAX];

int dfs(int node, int par)
{
    bool isLeaf = true;
    pop[node] = p[node];
    int childOnlyHappt = 0;
    for (auto &x : adj[node])
        if (x != par)
        {
            auto temp = dfs(x, node);
            db(temp, x, node);
            if (!temp)
                return false;
            isLeaf = false;
            pop[node] += pop[x];
            HappySubtree[node] += HappySubtree[x];
            childOnlyHappt += HappySubtree[x];
        }
    if (isLeaf)
    {
        int temp = h[node] + p[node];
        if (temp < 0 || (temp % 2))
            return false;
        HappySubtree[node] = temp / 2;
    }
    else
    {
        int temp = h[node] + pop[node] - 2 * childOnlyHappt;
        if (temp < 0 || (temp % 2))
            return false;
        HappySubtree[node] = temp / 2 + childOnlyHappt;
    }
    return HappySubtree[node] >= 0 && HappySubtree[node] <= pop[node];
}

struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        for (size_t i = 0; i < n; i++)
        {
            cin >> p[i];
        }
        for (size_t i = 0; i < n; i++)
        {
            cin >> h[i];
            adj[i].clear();
            // degree[i] = 0;
        }
        for (size_t i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        if (dfs(0, 0))
            cout << "YES\n";
        else
            cout << "NO\n";
        // dfs(0, 0);
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
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
