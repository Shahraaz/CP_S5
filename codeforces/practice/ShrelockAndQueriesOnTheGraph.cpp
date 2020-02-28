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

const int NAX = 1e5 + 5, MOD = 1000000007;

vector<int> E[NAX];     // Bridge tree
vector<int> graph[NAX]; //Original graph
int U[NAX], V[NAX];
bool isBridge[NAX];
bool visited[NAX];
int arr[NAX];
int cmpno;
queue<int> Q[NAX];
int L[NAX], P[19][NAX];
int vis = 0;
int C[NAX], S[NAX];
int start[NAX], finish[NAX], now;
int compo[NAX], T;

void dfsLcaBridgeTree(int u, int p)
{
    L[u] = p != -1 ? L[p] + 1 : 1;
    P[0][u] = p;
    start[u] = ++now;
    for (int j = 1; j < 19; j++)
    {
        int x = P[j - 1][u];
        if (x < 0)
            break;
        P[j][u] = P[j - 1][x];
    }
    ++vis;
    for (size_t i = 0; i < E[u].size(); i++)
    {
        int v = E[u][i];
        if (v == p)
            continue;
        dfsLcaBridgeTree(v, u);
    }
    finish[u] = ++now;
}

bool isAncestor(int u, int a)
{
    if (u == a)
        return true;
    return start[u] < start[a] && finish[u] > finish[a];
}

int lca(int p, int q)
{
    int log, i;
    if (L[p] < L[q])
        swap(p, q);
    for (log = 1; (1 << log) <= L[p]; log++)
        ;
    for (int i = log - 1; i >= 0; i--)
        if (L[p] - (1 << i) >= L[q])
            p = P[i][p];
    if (p == q)
        return p;
    for (int i = log - 1; i >= 0; i--)
        if (P[i][p] != -1 && P[i][p] != P[i][q])
            p = P[i][p], q = P[i][q];
    return P[0][p];
}

int adj(int u, int e)
{
    return U[e] == u ? V[e] : U[e];
}

int getDist(int a, int b, int lca)
{
    return L[a] + L[b] - 2 * L[lca];
}

int dfs0BridgeTree(int u, int edge)
{
    visited[u] = 1;
    int dbe = arr[u] = T++;
    for (size_t i = 0; i < graph[u].size(); i++)
    {
        int e = graph[u][i];
        int w = adj(u, e);
        // db(u, i, w);
        if (!visited[w])
            dbe = min(dbe, dfs0BridgeTree(w, e));
        else if (e != edge)
            dbe = min(dbe, arr[w]);
    }
    // cout << u << ' ' << edge << ' ' << dbe << ' ' << arr[u] << '\n';
    if (dbe == arr[u] && edge != -1)
    {
        isBridge[edge] = true;
        // cout << "Bridge " << edge << '\n';
    }
    return dbe;
}

void dfsBridgeTreeContruction(int v)
{
    int currcmp = cmpno;
    Q[currcmp].push(v);
    visited[v] = 1;
    while (!Q[currcmp].empty())
    {
        int u = Q[currcmp].front();
        Q[currcmp].pop();
        compo[u] = currcmp;
        for (size_t i = 0; i < graph[u].size(); i++)
        {
            int e = graph[u][i];
            int w = adj(u, e);
            if (visited[w])
                continue;
            if (isBridge[e])
            {
                cmpno++;
                E[cmpno].pb(currcmp);
                E[currcmp].pb(cmpno);
                dfsBridgeTreeContruction(w);
            }
            else
            {
                Q[currcmp].push(w);
                visited[w] = 1;
            }
        }
    }
}

pair<int, int> getCommanPath(int u, int a, int v, int b)
{
    if (!isAncestor(v, a))
        return {0, 0};
    int x = lca(a, b);
    if (L[v] < L[u])
    {
        if (isAncestor(u, x))
            return {u, x};
    }
    else if (isAncestor(v, x))
        return {v, x};
    return {0, 0};
}

int getAnswer(int a, int b, int c, int d)
{
    int u = lca(a, b), v = lca(c, d);
    int ret = getDist(a, b, u);
    pair<int, int> X;
    X = getCommanPath(u, a, v, c);
    ret -= getDist(X.f, X.s, lca(X.f, X.s));

    X = getCommanPath(u, a, v, d);
    ret -= getDist(X.f, X.s, lca(X.f, X.s));

    X = getCommanPath(u, b, v, c);
    ret -= getDist(X.f, X.s, lca(X.f, X.s));

    X = getCommanPath(u, b, v, d);
    ret -= getDist(X.f, X.s, lca(X.f, X.s));

    return ret;
}

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m, q;
        cin >> n >> m >> q;
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            U[i] = v;
            V[i] = u;
            graph[u].pb(i);
            graph[v].pb(i);
            // cout << u << ' ' << v << ' ' << i << '\n';
        }
        // cout << '\n';
        dfs0BridgeTree(0, -1);
        memset(visited, 0, sizeof visited);
        dfsBridgeTreeContruction(0);
        dfsLcaBridgeTree(0, -1);
        while (q--)
        {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            --a, --b, --c, --d;
            cout << getAnswer(compo[c], compo[d], compo[a], compo[b]) << '\n';
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
