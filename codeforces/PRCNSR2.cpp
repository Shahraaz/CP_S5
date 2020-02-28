// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
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

const int NAX = 1e3 + 5, MAX = NAX * NAX;
int MOD = 1000000007, LOGN = 12, INF = MOD;

int f[NAX][NAX];
int ff[NAX][NAX];
int U[MAX], V[MAX];
vector<int> g[NAX];
vector<pair<int, int>> Tree[NAX];
int n, m;
bool isBridge[MAX];
int visited[NAX], arr[NAX], T;
int cmpno, comp[NAX];
queue<int> Q[NAX];

class Solution
{
    int rec(int x, int y)
    {
        if (f[x][y] != -1)
            return f[x][y];
        if (x == y)
            return f[x][y] = 0;
        if (x == 1 || y == 1)
            return f[x][y] = 1 % MOD;
        return f[x][y] = f[y][x] = ((rec(x - 1, y) + rec(x, y - 1)) % MOD + rec(x - 1, y - 1)) % MOD;
    }

    int getNode(int e, int node)
    {
        return U[e] == node ? V[e] : U[e];
    }

    int dfs0(int u, int edge) //Bridges
    {
#ifdef LOCAL
        cout << u << ' ' << edge << '\n';
#else

#endif
        visited[u] = 1;
        arr[u] = T++;
        int dbe = arr[u];
        for (auto &e : g[u])
        {
            int v = getNode(e, u);
            if (!visited[v])
                dbe = min(dbe, dfs0(v, e));
            else if (e != edge)
                dbe = min(dbe, arr[v]);
        }
        if (dbe == arr[u] && edge != -1)
        {
            isBridge[edge] = true;
#ifdef LOCAL
            cout << edge << '\n';
#else

#endif
        }
#ifdef LOCAL
        cout << "RES\n";
        cout << u << ' ' << dbe << '\n';
#else

#endif
        return dbe;
    }

    void dfs1(int v) //Build bridge tree
    {
        int currcmp = cmpno;
        Q[currcmp].push(v);
        visited[v] = true;
        while (!Q[currcmp].empty())
        {
            int u = Q[currcmp].front();
            Q[currcmp].pop();
            comp[u] = currcmp;
            for (auto &edge : g[u])
            {
                int node = getNode(edge, u);
                if (visited[node])
                    continue;
                if (isBridge[edge])
                {
                    cmpno++;
                    Tree[cmpno].pb({currcmp, f[U[edge]][V[edge]]});
                    Tree[currcmp].pb({cmpno, f[U[edge]][V[edge]]});
                    dfs1(node);
                }
                else
                {
                    Q[currcmp].push(node);
                    visited[node] = true;
                }
            }
        }
    }

    void build_tree()
    {
        T = 0;
        cmpno = 0;
        memset(visited, 0, sizeof visited);
        dfs0(1, -1);
        memset(visited, 0, sizeof visited);
        dfs1(1);
#ifdef LOCAL
        for (int i = 1; i <= n; ++i)
            cout << comp[i] << ' ';
        cout << '\n';
#else

#endif
    }

    int root;
    void dfs(int u, int p, int mn)
    {
        ff[root][u] = mn;
        for (auto &child : Tree[u])
        {
            int node = child.f;
            int weight = child.s;
            if (node == p)
                continue;
            dfs(node, u, min(mn, weight));
        }
    }

    void process_tree()
    {
        for (root = 0; root < cmpno; root++)
            dfs(root, root, INF);
    }
    void init()
    {
        memset(f, -1, sizeof f);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                rec(i, j);
        // cout << i << ' ' << j << ' ' << rec(i,j) << '\n';
    }
    void reset()
    {
        for (int i = 0; i <= n; i++)
        {
            g[i].clear();
            Tree[i].clear();
        }
        for (int i = 0; i < m; i++)
        {
            isBridge[i] = false;
        }
    }

private:
public:
    ~Solution() {}
    void solveCase()
    {
        // int n, m;
        cin >> n >> m >> MOD;
        init();
        for (int i = 0; i < m; i++)
        {
            cin >> U[i] >> V[i];
            g[U[i]].pb(i);
            g[V[i]].pb(i);
        }
        build_tree();
        process_tree();
        int answer = 0;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
            {
                if (comp[i] == comp[j])
                    continue;
                answer = max(answer, f[i][j] - ff[comp[i]][comp[j]]);
            }
        reset();
        cout << answer << '\n';
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
