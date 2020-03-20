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
        for (size_t i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vector<int> path;
        vector<int> idx;
        vector<bool> vis(n + 1);
        idx.resize(n + 1);
        for (size_t i = 1; i <= n; i++)
        {
            int u;
            cin >> u;
            path.pb(u);
            idx[u] = i;
        }
        if (path.front() != 1)
        {
            cout << "No\n";
            return;
        }
        queue<int> Q;
        Q.push(path.front());
        vis[path.front()] = true;
        int ctr = 2;
        while (!Q.empty())
        {
            auto node = Q.front();
            Q.pop();
            db(node, ctr);
            vector<pair<int, int>> order;
            for (auto &child : adj[node])
            {
                if (vis[child])
                    continue;
                order.pb({idx[child], child});
            }
            sort(all(order));
            pc(order);
            for (auto &child : order)
            {
                if (child.f == ctr)
                {
                    vis[child.s] = true;
                    Q.push(child.s);
                    ctr++;
                }
                else
                {
                    cout << "No\n";
                    return;
                }
            }
        }
        cout << "Yes\n";
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