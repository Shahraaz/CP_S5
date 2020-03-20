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
vector<int> similar[NAX];
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
        for (size_t i = 0; i < n; i++)
        {
            ll x;
            cin >> x;
            for (size_t j = 0; j < 62; j++)
            {
                if (x & (1LL << j))
                {
                    for (auto &emel : similar[j])
                    {
                        adj[emel].pb(i);
                        adj[i].pb(emel);
                    }
                    similar[j].pb(i);
                    if (similar[j].size() == 3)
                    {
                        cout << 3 << '\n';
                        return;
                    }
                }
            }
        }
        vector<pair<int, int>> edges;
        for (size_t i = 0; i < n; i++)
        {
            sort(all(adj[i]));
            adj[i].erase(unique(all(adj[i])), adj[i].end());
            db(i);
            pc(adj[i]);
            for (auto &child : adj[i])
                edges.pb({i, child});
        }
        int ans = INT_MAX;
        for (auto &edge : edges)
        {
            auto u = edge.f;
            auto v = edge.s;
            vector<int> dist(n + 1, MOD);
            dist[u] = 0;
            queue<int> Q;
            Q.push(u);
            while (!Q.empty())
            {
                auto node = Q.front();
                Q.pop();
                for (auto &child : adj[node])
                {
                    if (node == u && child == v)
                        continue;
                    if (node == v && child == u)
                        continue;
                    if (dist[child] == MOD)
                    {
                        dist[child] = dist[node] + 1;
                        Q.push(child);
                    }
                }
            }
            if (dist[v] != MOD)
            {
                ans = min(ans, dist[v] + 1);
            }
        }

        if (ans == INT_MAX)
            cout << -1 << '\n';
        else
            cout << ans << '\n';
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