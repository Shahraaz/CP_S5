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
    int n, d, k;
    cin >> n >> d >> k;
    if (d >= n)
    {
        cout << "NO\n";
        return;
    }
    if (d == 1)
    {
        if (n == 1)
        {
            cout << "YES\n";
            return;
        }
        else if (n == 2)
        {
            cout << "YES\n";
            cout << "1 2\n";
            return;
        }
        cout << "NO\n";
        return;
    }
    if (d == 2)
    {
        if (k >= (n - 1))
        {
            cout << "YES\n";
            for (size_t i = 1; i < n; i++)
                cout << 1 << ' ' << i + 1 << '\n';
            return;
        }
        cout << "NO\n";
        return;
    }
    set<int> unused;
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> Q;
    const int DIST = 0;
    const int DEGREE = 1;
    const int NODE = 2;
    vector<vector<int>> adj(n);
    for (size_t i = 1; i <= d; i++)
    {
        adj[i].pb(i - 1);
        adj[i - 1].pb(i);
    }
    for (size_t i = 0; i < n; i++)
    {
        if (adj[i].size())
        {
            vector<int> temp(3);
            temp[DIST] = max(i, d - i);
            temp[DEGREE] = adj[i].size();
            temp[NODE] = i;
            Q.push(temp);
        }
        else
        {
            unused.insert(i);
        }
    }
    while (unused.size())
    {
        auto node = *unused.begin();
        unused.erase(node);
        while (true)
        {
            if (Q.size() == 0)
            {
                cout << "NO\n";
                return;
            }
            auto top = Q.top();
            Q.pop();
            if (top[DEGREE] >= k)
                continue;
            if (top[DIST] >= d)
                continue;
            adj[top[NODE]].pb(node);
            adj[node].pb(top[NODE]);
            top[DEGREE]++;
            Q.push(top);
            vector<int> temp(3);
            temp[DIST] = top[DIST] + 1;
            temp[DEGREE] = adj[node].size();
            temp[NODE] = node;
            Q.push(temp);
            break;
        }
    }
    LeastCommonAncestor lca(adj);
    for (size_t i = 0; i < n; i++)
    {
        db(i, adj[i]);
        if (adj[i].size() > k)
        {
            cout << "NO\n";
            return;
        }
    }
    int node1 = 0;
    for (size_t i = 0; i < n; i++)
        if (lca.dist(0, i) > lca.dist(0, node1))
            node1 = i;
    int node2 = 0;
    for (size_t i = 0; i < n; i++)
        if (lca.dist(node1, i) > lca.dist(node1, node2))
            node2 = i;
    if (lca.dist(node1, node2) == d)
    {
        cout << "YES\n";
        for (size_t i = 0; i < n; i++)
        {
            for (auto &x : adj[i])
                if (i < x)
                    cout << i + 1 << ' ' << x + 1 << '\n';
        }
    }
    else
    {
        cout << "NO\b";
        return;
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
