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

const int NAX = 2e5 + 5, MOD = 1000000007;

vector<vector<int>> adj;
int depth[NAX], par[NAX];

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

bool cmp(int u, int v)
{
    return depth[u] > depth[v];
}

class Solution
{
private:
    void dfs(int node, int par, int depth = 0)
    {
        db(node, par, depth);
        ::par[node] = par;
        ::depth[node] = depth;
        for (auto &child : adj[node])
            if (child != par)
                dfs(child, node, depth + 1);
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        adj.resize(n);
        for (size_t i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs(0, -1);
        LeastCommonAncestor lca(adj);
        for (size_t i = 0; i < m; i++)
        {
            int k;
            cin >> k;
            vector<int> v(k);
            for (auto &x : v)
            {
                cin >> x;
                --x;
            }
            sort(all(v), cmp);
            pc(v);
            int curr = v[0];
            bool ok = true;
            for (size_t i = 1; i < k; i++)
            {
                db(curr, v[i], depth[curr], depth[v[i]]);
                if (depth[curr] == depth[v[i]])
                {
                    if (par[curr] == par[v[i]])
                    {
                        ;
                    }
                    else
                    {
                        ok = false;
                        break;
                    }
                }
                else if (depth[curr] > depth[v[i]])
                {
                    int pparNode = lca.lca(curr, v[i]);
                    if (v[i] == pparNode || par[v[i]] == pparNode)
                    {
                    }
                    else
                    {
                        ok = false;
                        break;
                    }
                    curr = pparNode;
                }
                else
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
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