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
