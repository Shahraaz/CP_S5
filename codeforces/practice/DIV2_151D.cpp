//Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define multitest 1
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
using T = pair<int, int>;
using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e5 + 10, mod = 1000000007;
vector<int> adj[nax], hasClr[nax];
int clr[nax];
bool vis[nax];

void solve(int caseNo)
{
    int n, m, u, v;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> clr[i];
        hasClr[clr[i]].pb(i);
    }
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    int optClr, optCardinality;
    optCardinality = optClr = -1;
    for (int i = 1; i <= n; ++i)
    {
        if (vis[clr[i]])
            continue;
        vis[clr[i]] = true;
        set<int> neightbourClr;
        for (auto node : hasClr[clr[i]])
            for (auto neighbour : adj[node])
                if (clr[neighbour] != clr[i])
                    neightbourClr.insert(clr[neighbour]);
        db(i, clr[i]);
        pc(neightbourClr);
        db(neightbourClr.size(), optCardinality, neightbourClr.size() > optCardinality);
        if ((signed)neightbourClr.size() > optCardinality || (neightbourClr.size() == optCardinality && optClr > clr[i]))
        {
            optCardinality = neightbourClr.size();
            optClr = clr[i];
        }
    }
    cout << optClr << '\n';
}

int main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef multitest
    cin >> t;
#endif
    for (int i = 0; i < t; ++i)
        solve(i);
#ifdef TIME
    cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
    return 0;
}