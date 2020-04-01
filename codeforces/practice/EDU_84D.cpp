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
        vector<int> p(n);
        vector<int> clr(n);
        vector<int> vis(n);
        vector<int> adj[n];
        for (size_t i = 0; i < n; i++)
        {
            cin >> p[i];
            p[i]--;
            adj[i].pb(p[i]);
            // adj[p[i]].pb(i);
        }
        for (size_t i = 0; i < n; i++)
            cin >> clr[i];
        int res = MOD;
        for (size_t i = 0; i < n; i++)
        {
            if (vis[i])
                continue;
            vector<int> cycle;
            queue<int> Q;
            Q.push(i);
            vis[i] = true;
            while (!Q.empty())
            {
                auto node = Q.front();
                Q.pop();
                cycle.pb(node);
                for (auto &child : adj[node])
                {
                    if (!vis[child])
                    {
                        vis[child] = 1;
                        Q.push(child);
                    }
                }
            }
            pc(cycle);
            int len = cycle.size();
            vector<int> trials;
            for (ll i = 1; i * i <= len; i++)
                if (len % i == 0)
                    trials.pb(i), trials.pb(len / i);
            sort(all(trials));
            trials.erase(unique(all(trials)), trials.end());
            pc(trials);
            for (auto &l : trials)
            {
                for (size_t i = 0; i < l; i++)
                {
                    bool ok = true;
                    for (size_t j = i; j < cycle.size(); j += l)
                        ok = ok && (clr[cycle[i]] == clr[cycle[j]]);
                    if (ok)
                        res = min(res, l);
                    db(i, l, ok);
                }
            }
        }
        cout << res << '\n';
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