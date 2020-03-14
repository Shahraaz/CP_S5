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

vector<int> adj[NAX];
map<pair<int, int>, int> edgeIdx;
int clr[NAX], indegree[NAX];

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        if (n == 2)
        {
            cout << 0 << '\n';
            return;
        }
        if (n == 3)
        {
            cout << 0 << '\n';
            cout << 1 << '\n';
            return;
        }
        for (size_t i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
            edgeIdx[{u, v}] = i;
            edgeIdx[{v, u}] = i;
            indegree[u]++;
            indegree[v]++;
        }
        vector<int> leaves;
        for (size_t i = 1; i <= n; i++)
            if (indegree[i] == 1)
                leaves.pb(i);
        if (leaves.size() == 2)
        {
            for (size_t i = 0; i < (n - 1); i++)
                cout << i << '\n';
            return;
        }

        pc(leaves);

        memset(clr, -1, sizeof clr);
        int u, u1;
        u = leaves[0];
        u1 = adj[u][0];
        db(u, u1);
        clr[edgeIdx[{u1, u}]] = 0;

        u = leaves[1];
        u1 = adj[u][0];
        db(u, u1);
        clr[edgeIdx[{u1, u}]] = 1;

        u = leaves[2];
        u1 = adj[u][0];
        db(u, u1);
        clr[edgeIdx[{u1, u}]] = 2;

        int ctr = 3;
        for (size_t i = 1; i < n; i++)
        {
            db(i, clr[i]);
            if (clr[i] >= 0)
            {

                cout << clr[i] << '\n';
            }
            else
            {
                cout << (ctr) << '\n';
                ++ctr;
            }
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