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

const int NAX = 2e5 + 10, MOD = 1000000007;
vector<int> adj[NAX];
int marked[NAX], maxDistanceUp[NAX], maxDistanceDown[NAX];

int dfs1(int node, int par)
{
    maxDistanceDown[node] = marked[node] ? 0 : -1;
    for (auto child : adj[node])
        if (child != par)
        {
            int d = dfs1(child, node);
            if (d > -1)
                maxDistanceDown[node] = max(maxDistanceDown[node], d + 1);
        }
    db(node, maxDistanceDown[node]);
    return maxDistanceDown[node];
}

void dfs2(int node, int par)
{
    int mx1, mx2;
    mx1 = mx2 = -1;
    for (auto child : adj[node])
        if (child != par)
        {
            if (maxDistanceDown[child] > mx1)
            {
                mx2 = mx1;
                mx1 = maxDistanceDown[child];
            }
            else if (maxDistanceDown[child] > mx2)
                mx2 = maxDistanceDown[child];
        }
    for (auto child : adj[node])
        if (child != par)
        {
            int siblingDistance = maxDistanceDown[child] == mx1 ? mx2 : mx1;
            if (siblingDistance != -1)
                siblingDistance += 2;
            maxDistanceUp[child] = siblingDistance;
            if (maxDistanceUp[node] != -1)
                maxDistanceUp[child] = max(maxDistanceUp[child], maxDistanceUp[node] + 1);
            if (marked[child])
                maxDistanceUp[child] = max(maxDistanceUp[child], 0);
            dfs2(child, node);
        }
    db(node, maxDistanceUp[node]);
}

void solveCase(int caseNo)
{
    int n, m, d, u, v;
    cin >> n >> m >> d;
    db("Start");
    while (m--)
    {
        cin >> u;
        marked[u - 1] = true;
    }
    db("Mark");
    for (int i = 1; i < n; ++i)
    {
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    db("Graph");
    dfs1(0, -1);
    db("Dfs1");
    maxDistanceUp[0] = marked[0] ? 0 : -1;
    dfs2(0, -1);
    db("Dfs2");
    int ans = 0;
    for (int i = 0; i < n; ++i)
        ans += (maxDistanceUp[i] <= d && maxDistanceDown[i] <= d);
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