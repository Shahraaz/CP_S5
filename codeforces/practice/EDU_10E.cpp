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
    return out;
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

class Solution
{
private:
    vector<vector<pair<int, int>>> adj;
    vector<pair<pair<int, int>, int>> edges;
    vector<int> vis, disc, low, P;
    set<pair<int, int>> bridges;
    int _tm;
    void dfs(int c)
    {
        vis[c] = true;
        disc[c] = low[c] = ++_tm;
        for (auto &child : adj[c])
        {
            if (vis[child.f])
            {
                if (P[c] != child.f)
                    low[c] = min(low[c], low[child.f]);
                continue;
            }
            P[child.f] = c;
            dfs(child.f);
            low[c] = min(low[c], low[child.f]);
            if (low[child.f] > disc[c])
            {
                bridges.insert({c, child.f});
                bridges.insert({child.f, c});
            }
        }
    }

    bool dfs1(int node)
    {
        if (vis[node])
            return false;
        vis[node] = true;
        bool res = false;
        for (auto &child : adj[node])
        {
            res |= child.s;
            res |= dfs1(child.f);
        }
        return res;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        adj.assign(n + 1, vector<pair<int, int>>());
        vis.assign(n + 1, false);
        disc.assign(n + 1, 0);
        low.assign(n + 1, 0);
        P.assign(n + 1, 0);
        _tm = 0;
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].pb({v, w});
            adj[v].pb({u, w});
            edges.pb(make_pair(make_pair(u, v), w));
        }
        int a, b;
        cin >> a >> b;
        queue<int> Q;
        Q.push(a);
        vector<int> from(n + 1, -1), D(n + 1, n + 1);
        from[a] = -1;
        D[a] = 0;
        while (!Q.empty())
        {
            auto u = Q.front();
            Q.pop();
            for (auto &child : adj[u])
            {
                if (D[child.f] > D[u] + 1)
                {
                    D[child.f] = D[u] + 1;
                    from[child.f] = u;
                    Q.push(child.f);
                }
            }
        }
        int tmp = b;
        set<pair<int, int>> shortest;
        while (from[tmp] != -1)
        {
            shortest.insert({tmp, from[tmp]});
            shortest.insert({from[tmp], tmp});
            tmp = from[tmp];
        }
        dfs(a);
        adj.assign(n + 1, vector<pair<int, int>>());
        for (int i = 0; i < m; i++)
        {
            int x = edges[i].f.f;
            int y = edges[i].f.s;
            int z = edges[i].s;
            if (bridges.find({x, y}) != bridges.end() && shortest.find({x, y}) == shortest.end())
                continue;
            adj[x].pb({y, z});
            adj[y].pb({x, z});
        }
        fill(all(vis), false);
        if (dfs1(a))
            cout << "YES\n";
        else
            cout << "NO\n";
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
