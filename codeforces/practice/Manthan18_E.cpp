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
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m, k;
        cin >> n >> m >> k;
        vector<pair<int, int>> edges(m);
        vector<int> ans(m);
        vector<int> degree(n);
        vector<pair<int, int>> adj[n];
        set<pair<int, int>> goodSet;
        vector<bool> inGoodSet(n, true);
        for (size_t i = 0; i < m; i++)
        {
            cin >> edges[i].f >> edges[i].s;
            edges[i].f--;
            edges[i].s--;
            adj[edges[i].f].pb({edges[i].s, i});
            adj[edges[i].s].pb({edges[i].f, i});
            degree[edges[i].f]++;
            degree[edges[i].s]++;
        }
        for (size_t i = 0; i < n; i++)
            goodSet.insert({degree[i], i});
        auto refactor = [&k, &goodSet, &adj, &degree, &inGoodSet](int idx = MOD) {
            while (!goodSet.empty() && goodSet.begin()->f < k)
            {
                int node = goodSet.begin()->s;
                for (auto &child : adj[node])
                {
                    int x = child.f;
                    if (child.s >= idx)
                        continue;
                    if (inGoodSet[x])
                    {
                        goodSet.erase({degree[x], x});
                        degree[x]--;
                        goodSet.insert({degree[x], x});
                    }
                }
                goodSet.erase({degree[node], node});
                inGoodSet[node] = false;
            }
        };
        refactor();
        for (int i = m - 1; i >= 0; i--)
        {
            ans[i] = goodSet.size();
            int u = edges[i].f, v = edges[i].s;
            if (inGoodSet[u] && inGoodSet[v])
            {
                goodSet.erase({degree[u], u});
                goodSet.erase({degree[v], v});
                degree[u]--;
                degree[v]--;
                goodSet.insert({degree[u], u});
                goodSet.insert({degree[v], v});
                refactor(i);
            }
        }
        for (size_t i = 0; i < m; i++)
            cout << ans[i] << '\n';
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