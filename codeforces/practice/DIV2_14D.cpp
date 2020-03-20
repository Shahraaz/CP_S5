// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
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

class Solution
{
private:
    int n;
    vector<vector<int>> adj;
    int answer;
    int farthestNode, maxDist;

    void dfs(int node, int par, int forbid, int dist = 0)
    {
        db(node, par, forbid, dist);
        if (node == forbid)
            return;
        for (auto &child : adj[node])
        {
            if (child == par)
                continue;
            dfs(child, node, forbid, dist + 1);
        }
        if (dist > maxDist)
        {
            maxDist = dist;
            farthestNode = node;
        }
    }

    int diam(int node, int par)
    {
        db(node, par);
        farthestNode = -1, maxDist = -1;
        dfs(node, par, par);
        int node2 = farthestNode;
        dfs(farthestNode, farthestNode, par);
        return maxDist;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n;
        adj.resize(n);
        vector<pair<int, int>> edges;
        for (size_t i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            edges.pb({u, v});
            adj[u].pb(v);
            adj[v].pb(u);
        }
        answer = 0;
        for (auto &edge : edges)
        {
            answer = max(answer, diam(edge.f, edge.s) * diam(edge.s, edge.f));
        }
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