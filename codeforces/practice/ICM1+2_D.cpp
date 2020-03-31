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

const int NAX = 1e6 + 5, MOD = 1000000007;

vector<int> arr[NAX];
int arr1[NAX];
vector<pair<int, int>> adj[NAX];
int n, m;
int col[NAX], vis[NAX];

class Solution
{
private:
    void makeGraph()
    {
        for (size_t i = 1; i <= n; i++)
        {
            int x = arr[i][0];
            int y = arr[i][1];
            adj[x].pb({y, arr1[i]});
            adj[y].pb({x, arr1[i]});
        }
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n >> m;
        for (size_t i = 0; i < n; i++)
            cin >> arr1[i + 1];
        for (size_t i = 1; i <= m; i++)
        {
            int sz;
            cin >> sz;
            for (size_t j = 0; j < sz; j++)
            {
                int y;
                cin >> y;
                arr[y].pb(i);
            }
        }
        makeGraph();
        memset(col, -1, sizeof col);
        memset(vis, 0, sizeof vis);
        bool p = true;
        for (int i = 1; i <= m; i++)
        {
            if (!vis[i] && adj[i].size())
            {
                col[i] = 0;
                vis[i] = true;
                queue<int> Q;
                Q.push(i);
                while (Q.size())
                {
                    int node = Q.front();
                    Q.pop();
                    for (auto &child : adj[node])
                    {
                        int co = col[node];
                        if (child.s == 0)
                            co = 1 - co;
                        if (vis[child.f] && col[child.f] != co)
                            p = false;
                        if (!vis[child.f])
                        {
                            col[child.f] = co;
                            vis[child.f] = true;
                            Q.push(child.f);
                        }
                    }
                }
            }
        }
        if (p)
            cout << "YES";
        else
            cout << "NO";
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