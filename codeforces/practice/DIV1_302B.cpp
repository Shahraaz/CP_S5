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

const int NAX = 5005 + 5, MOD = 1000000007;

int dist[NAX][NAX];
vector<int> adj[NAX];

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
        memset(dist, -1, sizeof dist);
        for (size_t i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        for (size_t i = 0; i < n; i++)
        {
            queue<int> q;
            dist[i][i] = 0;
            q.push(i);
            while (!q.empty())
            {
                auto s = q.front();
                q.pop();
                for (auto &child : adj[s])
                    if (dist[i][child] == -1)
                    {
                        dist[i][child] = dist[i][s] + 1;
                        q.push(child);
                    }
            }
            // #ifdef LOCAL
            //             db(i);
            //             for (size_t j = 0; j < n; j++)
            //                 cout << dist[i][j] << ' ';
            //             cout << '\n';
            // #else

            // #endif
        }
        int s[2], t[2], l[2];
        cin >> s[0] >> t[0] >> l[0];
        cin >> s[1] >> t[1] >> l[1];
        s[0]--, t[0]--;
        s[1]--, t[1]--;
        int ans = m + 1;

        for (size_t iter = 0; iter < 2; iter++)
        {
            swap(s[0], t[0]);
            for (size_t i = 0; i < n; i++)
                for (size_t j = 0; j < n; j++)
                {
                    int v[] = {dist[s[0]][i] + dist[i][j] + dist[j][t[0]], dist[s[1]][i] + dist[i][j] + dist[j][t[1]]};
                    if (v[0] <= l[0] && v[1] <= l[1])
                        ans = min(ans, v[0] + v[1] - dist[i][j]);
                    db(iter, i, j, ans);
                }
        }
        if (dist[s[0]][t[0]] <= l[0] && dist[s[1]][t[1]] <= l[1])
            ans = min(ans, dist[s[0]][t[0]] + dist[s[1]][t[1]]);
        if (ans > m)
            cout << -1 << '\n';
        else
            cout << m - ans << '\n';
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