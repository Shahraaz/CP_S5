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

struct Solution
{
    Solution() {}
    void solveCase();
};

//Here it is an unweighted tree
//If you want to solve for thath then
//You have to go for Dist(a,b) = Dist(a) + Dist(b) - 2*Dist(lca(a,b))
// where Dist(a) is distance from Root to a;
struct LeastCommonAncestor
{
    vector<int> Level;
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
        dfs(0, 0, 0);
        for (int i = 1; i < Log; ++i)
            for (int j = 0; j < n; ++j)
                dp[i][j] = dp[i - 1][dp[i - 1][j]];
    }
    void dfs(int node, int parent, int level)
    {
        dp[0][node] = parent;
        Level[node] = level;
        for (auto child : Adj[node])
            if (child != parent)
                dfs(child, node, level + 1);
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

void Solution::solveCase()
{
    int n, bob;
    cin >> n >> bob;
    bob--;
    int axel = 0;
    vector<vector<int>> adj(n);
    for (size_t i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        --x, --y;
        // x = (x - bob + n) % n;
        // y = (y - bob + n) % n;
        // db(x, y);
        adj[x].pb(y);
        adj[y].pb(x);
    }
    LeastCommonAncestor lca(adj);
    vector<int> level(n);
    function<int(int, int, int)> dfs = [&](int node, int par, int lvl) -> int {
        int maxLevel = lvl;
        for (auto &x : adj[node])
            if (x != par)
                maxLevel = max(maxLevel, dfs(x, node, lvl + 1));
        level[node] = maxLevel;
        db(node, level[node]);
        return maxLevel;
    };
    dfs(0, 0, 0);
    int res = 0;
    queue<pair<int, int>> Q;
    Q.push({bob, bob});
    while (Q.size())
    {
        auto top = Q.front();
        Q.pop();
        int a = lca.dist(bob, top.f);
        int b = lca.dist(axel, top.f);
        db(top, a, b);
        if (b < a)
            continue;
        if (b == a)
            res = max(res, a * 2);
        else
        {
            int temp = 2 * level[top.f];
            db(temp);
            res = max(res, temp);
            for (auto &x : adj[top.f])
                if (x != top.s)
                    Q.push({x, top.f});
        }
    }
    cout << res << '\n';
}

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
