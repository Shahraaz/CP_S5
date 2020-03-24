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

int p[64][NAX];
int clr[NAX];

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
        vector<vector<int>> adj(n);
        for (size_t i = 0; i < n; i++)
        {
            cin >> p[1][i];
            p[0][i] = i;
            p[1][i]--;
            adj[i].push_back(p[1][i]);
        }
        for (size_t i = 0; i < n; i++)
        {
            cin >> clr[i];
        }
        for (size_t i = 2; i < 64; i++)
            for (size_t j = 0; j < n; j++)
                p[i][j] = p[i - 1][p[i - 1][j]];
#ifdef LOCAL
                // cout << "---------------------------\n";
                // for (size_t i = 0; i <= 63; i++)
                // {
                //     db(i);
                //     for (size_t j = 0; j < n; j++)
                //         cout << p[i][j] << ' ';
                //     cout << '\n';
                // }
#else

#endif
        vector<bool> vis(n);
        vector<int> len(n);
        int ans = MOD;
        for (size_t i = 0; i < n; i++)
        {
            if (vis[i])
                continue;
            vis[i] = true;
            queue<int> Q;
            Q.push(i);
            int Len = 0;
            vector<int> cycle;
            map<int, vector<int>> dist;
            while (Q.size())
            {
                auto top = Q.front();
                Q.pop();
                cycle.pb(top);
                dist[clr[top]].pb(Len);
                Len++;
                for (auto &child : adj[top])
                {
                    if (vis[child])
                        continue;
                    Q.push(child);
                    vis[child] = true;
                }
            }
            pc(cycle);
            db(Len);
            for (auto &e : cycle)
                len[e] = Len;
            if (dist.size() == 1)
                ans = 1;
            for (auto &e : dist)
            {
                if (e.s.size() != 1)
                    for (size_t i = 0; (i) < e.s.size(); i++)
                    {
                        ans = min(ans, abs(e.s[i] - e.s[(i + 1) % e.s.size()]));
                    }
            }
            ans = min(ans, Len);
        }
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