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
using oredered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
auto TimeStart = chrono::steady_clock::now();

const int NAX = 2e5 + 10, MOD = 1000000007;
vector<pair<int, int>> adj[NAX];
pair<int, int> par[NAX];
int ss[NAX], nodesDown[NAX], nodesUp[NAX];
bool vis[NAX];

bool lucky(int w)
{
    while (w)
    {
        if (w % 10 == 7 || w % 10 == 4)
            w /= 10;
        else
            return false;
    }
    return true;
}

void dfs(int node, int parent, int weight)
{
    ss[node] = 1;
    vis[node] = true;
    par[node].f = parent;
    par[node].s = weight;
    for (auto edge : adj[node])
        if (!vis[edge.f])
        {
            dfs(edge.f, node, edge.s);
            ss[node] += ss[edge.f];
            if (edge.s)
                nodesDown[node] += ss[edge.f];
            else
                nodesDown[node] += nodesDown[edge.f];
        }
}

int n, u, v, w;
void dfs2(int node)
{
    if (par[node].second)
        nodesUp[node] = n - ss[node];
    else if (node != 1)
    {
        nodesUp[node] += nodesDown[par[node].first] - nodesDown[node];
        nodesUp[node] += nodesUp[par[node].first];
    }
    vis[node] = true;
    for (auto edge : adj[node])
        if (!vis[edge.f])
            dfs2(edge.first);
}

void solveCase(int caseNo)
{
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        cin >> u >> v >> w;
        w = lucky(w);
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    dfs(1, 0, 0);
    memset(vis, 0, sizeof vis);
    dfs2(1);
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        ll k = nodesUp[i] + nodesDown[i];
        db(i, nodesUp[i], nodesDown[i], k);
        ans += k * (k - 1);
    }
    cout << ans << '\n';
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
    for (int i = 0; i < t; ++i)
        solveCase(i);
#ifdef TIME
    cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
    return 0;
}