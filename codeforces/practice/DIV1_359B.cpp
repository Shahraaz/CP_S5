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

const int NAX = 3e5 + 5, MOD = 1000000007;

int centroid[NAX];
vector<int> adj[NAX];
int sizeOfSubTree[NAX];
int biggestChildidx[NAX];
int parentOfNode[NAX];

class Solution
{
private:
    bool is_centorid_of_subtree(int node, int child)
    {
        return (sizeOfSubTree[node] - sizeOfSubTree[child]) * 2 <= sizeOfSubTree[node] &&
               sizeOfSubTree[biggestChildidx[child]] * 2 <= sizeOfSubTree[node];
    }
    int dfs_init(int node, int par)
    {
        // db(node, par, "b");
        parentOfNode[node] = par;
        for (auto &child : adj[node])
            if (child != par)
            {
                sizeOfSubTree[node] += dfs_init(child, node);
                if (sizeOfSubTree[child] > sizeOfSubTree[biggestChildidx[node]])
                    biggestChildidx[node] = child;
            }
        return ++sizeOfSubTree[node];
    }
    void dfs_calc(int node, int par)
    {
        if (sizeOfSubTree[node] == 1)
            centroid[node] = node;
        else
        {
            for (auto &child : adj[node])
                if (child != par)
                    dfs_calc(child, node);
            db(node, par, biggestChildidx[node], sizeOfSubTree[node]);
            int c = centroid[biggestChildidx[node]];
            db(c);
            while (!is_centorid_of_subtree(node, c))
            {
                c = parentOfNode[c];
                db(c);
                if (c == parentOfNode[c])
                    break;
            }
            centroid[node] = c;
            db(node, centroid[node]);
        }
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, q;
        cin >> n >> q;
        for (size_t i = 2; i <= n; i++)
        {
            int v;
            cin >> v;
            adj[v].pb(i);
            adj[i].pb(v);
        }
        dfs_init(1, 1);
        dfs_calc(1, 1);
        for (size_t i = 0; i < q; i++)
        {
            int v;
            cin >> v;
            cout << centroid[v] << '\n';
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