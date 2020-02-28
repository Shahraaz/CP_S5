// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
#define pc(...) PC(#__VA_ARGS__, __VA_ARGS__);
template <typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> &p)
{
    out << '[' << p.first << ", " << p.second << ']';
}
template <typename Arg>
void PC(const char *name, Arg &&arg)
{
    while (*name == ',' || *name == ' ')
        name++;
    std::cerr << name << " { ";
    for (const auto &v : arg)
        cerr << v << ' ';
    cerr << " }\n";
}
template <typename Arg1, typename... Args>
void PC(const char *names, Arg1 &&arg1, Args &&... args)
{
    while (*names == ',' || *names == ' ')
        names++;
    const char *comma = strchr(names, ',');
    std::cerr.write(names, comma - names) << " { ";
    for (const auto &v : arg1)
        cerr << v << ' ';
    cerr << " }\n";
    PC(comma, args...);
}
template <typename Arg1>
void ZZ(const char *name, Arg1 &&arg1)
{
    std::cerr << name << " = " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void ZZ(const char *names, Arg1 &&arg1, Args &&... args)
{
    const char *comma = strchr(names + 1, ',');
    std::cerr.write(names, comma - names) << " = " << arg1;
    ZZ(comma, args...);
}
#else
#define db(...)
#define pc(...)
#endif

using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

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

struct BiConnectedComponents
{
    int n, m, T, cmpCnt;
    vector<int> U, V, arr, compId;
    vector<bool> isBridge, vis;
    vector<vector<int>> adj_mytype, Tree;
    vector<queue<int>> Q;

    int getNode(int e, int node)
    {
        return U[e] == node ? V[e] : U[e];
    }

    int dfsBridge(int u, int edge)
    {
        vis[u] = 1;
        arr[u] = T++;
        int dbe = arr[u];
        for (auto &e : adj_mytype[u])
        {
            int v = getNode(e, u);
            if (!vis[v])
                dbe = min(dbe, dfsBridge(v, e));
            else if (e != edge)
                dbe = min(dbe, arr[v]);
        }
        if (dbe == arr[u] && edge != -1)
            isBridge[edge] = true;
        return dbe;
    }

    void dfsBridgeTree(int node)
    {
        int currCmp = cmpCnt;
        Q[currCmp].push(node);
        vis[node] = true;
        while (!Q[currCmp].empty())
        {
            int u = Q[currCmp].front();
            Q[currCmp].pop();
            compId[u] = currCmp;
            for (auto &edge : adj_mytype[u])
            {
                int v = getNode(edge, u);
                if (vis[v])
                    continue;
                if (isBridge[edge])
                {
                    cmpCnt++;
                    Tree[cmpCnt].pb(currCmp);
                    Tree[currCmp].pb(cmpCnt);
                    dfsBridgeTree(v);
                }
                else
                {
                    Q[currCmp].push(v);
                    vis[v] = true;
                }
            }
        }
    }

    void build_tree(vector<vector<int>> &adj)
    {
        n = adj.size();
        m = 0;
        adj_mytype.assign(n, vector<int>());
        U.clear();
        V.clear();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < adj[i].size(); j++)
            {
                if (i < adj[i][j])
                {
                    U.pb(i);
                    V.pb(adj[i][j]);
                    adj_mytype[i].pb(m);
                    adj_mytype[adj[i][j]].pb(m);
                    m++;
                }
            }
        }
        // db(m);
        isBridge.assign(m, false);
        vis.assign(n, false);
        arr.assign(n, 0);
        T = 0;
        dfsBridge(0, -1);
        fill(vis.begin(), vis.end(), false);
        Tree.assign(n, vector<int>());
        cmpCnt = 0;
        compId.assign(n, 0);
        Q.assign(n, queue<int>());
        dfsBridgeTree(0);
        Tree.resize(cmpCnt + 1);
        db(cmpCnt);
        pc(compId);
    }
};

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        BiConnectedComponents B;
        B.build_tree(adj);
        db("LCA Start");
        LeastCommonAncestor L(B.Tree);
        db("LCA End");
        int k;
        cin >> k;
        for (int i = 0; i < k; i++)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            cout << L.dist(B.compId[u], B.compId[v]) << '\n';
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
