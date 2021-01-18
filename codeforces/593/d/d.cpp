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
const int NAX = 2e5 + 5, MOD = 1000000007;

vector<vector<int>> adj;
vector<pair<pair<int, int>, ll>> edges;
int n;
int par[NAX], mapper[NAX];
ll wt[NAX];

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

void solveCase()
{
    int m;
    cin >> n >> m;
    adj.resize(n);
    fill(wt, wt + n, 1);
    for (size_t i = 0; i + 1 < n; i++)
    {
        int u, v;
        ll p;
        cin >> u >> v >> p;
        --u, --v;
        edges.pb({{u, v}, p});
        adj[u].pb(v);
        adj[v].pb(u);
    }
    db("input done");
    LeastCommonAncestor l(adj);
    db("built");
    for (size_t i = 0; i + 1 < n; i++)
    {
        if (l.dp[0][edges[i].first.first] == edges[i].first.second)
        {
            mapper[i] = edges[i].first.first;
            wt[edges[i].first.first] = edges[i].second;
        }
        else
        {
            mapper[i] = edges[i].first.second;
            wt[edges[i].first.second] = edges[i].second;
        }
        db(i, mapper[i], wt[mapper[i]]);
    }
    db("wt assigned");
    auto par = l.dp[0];
    for (size_t i = 0; i < n; i++)
        par[i] = i;
    {
        vector<int> vis(n);
        queue<int> Q;
        Q.push(0);
        vis[0] = 1;
        while (Q.size())
        {
            auto top = Q.front();
            Q.pop();
            for (auto &x : adj[top])
                if (!vis[x])
                {
                    vis[x] = 1;
                    if (wt[x] == 1)
                        par[x] = par[top];
                    Q.push(x);
                }
        }
    }
    function<int(int)> find_par = [&](int a) -> int {
        if (par[a] == a)
            return a;
        return par[a] = find_par(par[a]);
    };
    auto brute_force = [&](int a, int b, ll p) -> ll {
        auto lca = l.lca(a, b);
        db(a, b, lca, p);
        while (l.Level[a] > l.Level[lca])
        {
            db(a, par[a], wt[a], p);
            db(lca, l.Level[a], l.Level[lca]);
            if (wt[a] == 1)
            {
                if (par[a] == a)
                {
                    par[a] = l.dp[0][a];
                    a = find_par(a);
                }
                else
                    a = find_par(a);
            }
            else
            {
                p /= wt[a];
                a = l.dp[0][a];
            }
            if (p == 0)
                break;
        }
        db(a, b, lca, p);
        __int128_t p1 = 1;
        vector<ll> temp;
        while (l.Level[b] > l.Level[lca])
        {
            db(b, par[b], wt[b], b);
            db(lca, l.Level[b], l.Level[lca]);
            if (wt[b] == 1)
            {
                if (par[b] == b)
                {
                    par[b] = l.dp[0][b];
                    b = find_par(b);
                }
                else
                    b = find_par(b);
            }
            else
            {
                p1 *= wt[b];
                temp.pb(wt[b]);
                b = l.dp[0][b];
            }
            if (p1 > p)
                return 0;
        }
        reverse(all(temp));
        for (auto &x : temp)
            p /= x;
        return p;
    };
    for (size_t i = 0; i < m; i++)
    {
        int ch;
        cin >> ch;
        if (ch == 1)
        {
            ll a, b, p;
            cin >> a >> b >> p;
            --a, --b;
            cout << brute_force(a, b, p) << '\n';
        }
        else
        {
            ll p, c;
            cin >> p >> c;
            --p;
            auto v = mapper[p];
            if (wt[v] != 1 && c == 1)
                par[v] = l.dp[0][v];
            wt[v] = c;
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
        solveCase();
    return 0;
}