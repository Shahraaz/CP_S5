// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#define pc(...)
#endif

#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

//Add Dummy Comment
//https://github.com/Shahraaz/CP/blob/master/SCC.cpp

typedef vector<int> _vi;
typedef vector<_vi> _graph;
// int getConj(int x)
// {
//     return x ^ 1;
// }
// auto add = [&](int a, int b) {
//     adj[a].pb(b);
//     adj[getConj(b)].pb(getConj(a));
// };
// auto addXor = [&](int a, int b) {
//     add(a, getConj(b));
//     add(getConj(a), b);
// };
// auto addOr = [&](int a, int b) {
//     add(getConj(a), b);
// };

// auto addand = [&](int u, int v) {
//     add(getConj(u), u);
//     add(getConj(v), v);
// };

class SCC
{
public:
    int _n, _m, CompC;
    _graph G, RevG, SccG;
    stack<int> St;
    _vi Vis, Comp;
    SCC()
    {
    }
    void fillOrder(int i)
    {
        Vis[i] = true;
        for (int x : G[i])
            if (!Vis[x])
                fillOrder(x);
        St.push(i);
    }
    void Dfs(int u, int c)
    {
        Vis[u] = true;
        Comp[u] = c;
        for (int x : RevG[u])
            if (!Vis[x])
                Dfs(x, c);
    }
    void MakeScc()
    {
        for (int i = 0; i < _n; ++i)
            if (!Vis[i])
                fillOrder(i);
        fill(Vis.begin(), Vis.end(), false);
        CompC = 0;
        while (!St.empty())
        {
            auto v = St.top();
            St.pop();
            if (!Vis[v])
                Dfs(v, CompC++);
        }
        // SccG.resize(CompC);
        // for (int i = 0; i < _n; ++i)
        //     for (auto y : G[i])
        //         if (Comp[i] != Comp[y])
        //             SccG[Comp[i]].pb(Comp[y]);
        // for (int i = 0; i < CompC; ++i)
        // {
        //     sort(SccG[i].begin(), SccG[i].end());
        //     SccG[i].erase(unique(SccG[i].begin(), SccG[i].end()), SccG[i].end());
        // }
    }
    SCC(_graph _G)
    {
        G = _G;
        _n = G.size();
        _m = 0;
        Vis.resize(_n);
        Comp.resize(_n);
        RevG.resize(_n);
        for (int i = 0; i < _n; ++i)
            for (auto y : G[i])
            {
                _m++;
                RevG[y].pb(i);
            }
        MakeScc();
    }
    pair<_graph, _vi> GetScc()
    {
        return {SccG, Comp};
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
        vector<vector<int>> adj(2 * n);
        auto getConj = [](int n) {
            return n ^ 1;
        };
        auto add = [&](int a, int b) {
            adj[a].pb(b);
            adj[getConj(b)].pb(getConj(a));
        };
        auto addXor = [&](int a, int b) {
            add(a, getConj(b));
            add(getConj(a), b);
        };
        auto addOr = [&](int a, int b) {
            add(getConj(a), b);
        };
        auto addand = [&](int u, int v) {
            add(getConj(u), u);
            add(getConj(v), v);
        };
        auto correctU = [&](int u) {
            if (u >= n)
            {
                u -= n;
                u = getConj(2 * u);
            }
            else
                u = 2 * u;
            return u;
        };
        for (size_t i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            --a, --b;
            a = correctU(a);
            b = correctU(b);
            addOr(a, b);
        }
        SCC scc(adj);
        for (size_t i = 0; i < 2 * n; i++)
            if (scc.Comp[i] == scc.Comp[getConj(i)])
            {
                cout << "boring\n";
                return;
            }
        cout << "interesting\n";
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