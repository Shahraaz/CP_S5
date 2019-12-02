//Optimise
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
auto TimeStart = chrono::steady_clock::now();

const int NAX = 2e5 + 10, MOD = 1000000007, LG = 30;
vector<int> adj[NAX];
int n, depth[NAX], size[NAX], anc[NAX][LG], tin[NAX], tout[NAX], timer;

void dfs(int node, int par = 1, int d = 0)
{
    depth[node] = d;
    size[node] = 1;
    tin[node] = timer++;
    anc[node][0] = par;
    for (int i = 1; i < LG; ++i)
        anc[node][i] = anc[anc[node][i - 1]][i - 1];
    for (auto child : adj[node])
        if (child != par)
        {
            dfs(child, node);
            size[node] += size[child];
        }
    tout[node] = timer++;
}

bool ancestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int go_up(int a, int b)
{
    for (int i = LG - 1; i >= 0; --i)
        if (!ancestor(anc[a][i], b))
            a = anc[a][i];
    return a;
}

int lca(int a, int b)
{
    int result = -1;
    if (ancestor(a, b))
        return a;
    else if (ancestor(b, a))
        return b;
    return anc[go_up(a, b)][0];
}

int query(int a, int b)
{
    if (a == b)
        return n;
    int l = lca(a, b);
    if (depth[a] == depth[b])
        return n - size[go_up(a, l)] - size[go_up(b, l)];
    if (depth[a] < depth[b])
        swap(a, b);
    int dist = depth[a] + depth[b] - 2 * depth[l];
    if (dist % 2)
        return 0;
    dist /= 2;
    int to = a;
    for (int i = LG - 1; i >= 0; --i)
        if (depth[a] - depth[anc[to][i]] < dist)
            to = anc[to][i];
    int mid = anc[to][0];
    return size[mid] - size[to];
}

void solveCase(int caseNo)
{
    cin >> n;
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1);
    int q;
    cin >> q;
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        cout << query(u, v) << '\n';
    }
}

int main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    for (int i = 1; i <= t; ++i)
    {
        solveCase(i);
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}