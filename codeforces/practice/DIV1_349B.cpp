// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 3e3 + 5, MOD = 1000000007;

set<int> adj[NAX];
set<int> rev_adj[NAX];
vector<int> farthest[NAX], farthest_rev[NAX];
int forw_dist[NAX][NAX];
int back_dist[NAX][NAX];

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
        for (size_t i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].insert(v);
            rev_adj[v].insert(u);
        }
        vector<int> dist(n + 1);
        for (size_t i = 1; i <= n; i++)
        {
            queue<int> Q;
            Q.push(i);
            fill(all(dist), INT_MAX);
            dist[i] = 0;
            stack<int> st;
            while (Q.size())
            {
                auto top = Q.front();
                forw_dist[i][top] = dist[top];
                // db(i, top, dist[top]);
                st.push(top);
                Q.pop();
                for (auto &x : adj[top])
                    if (dist[x] == INT_MAX)
                    {
                        dist[x] = dist[top] + 1;
                        Q.push(x);
                    }
            }
            int cnt = 4;
            while (st.size())
            {
                if (cnt > 0)
                    farthest[i].pb(st.top()), cnt--;
                st.pop();
            }
            // db(i, dist);

            Q.push(i);
            fill(all(dist), INT_MAX);
            dist[i] = 0;
            while (Q.size())
            {
                auto top = Q.front();
                back_dist[i][top] = dist[top];
                // db(-i, top, dist[top]);
                st.push(top);
                Q.pop();
                for (auto &x : rev_adj[top])
                    if (dist[x] == INT_MAX)
                    {
                        dist[x] = dist[top] + 1;
                        Q.push(x);
                    }
            }
            cnt = 4;
            while (st.size())
            {
                if (cnt > 0)
                    farthest_rev[i].pb(st.top()), cnt--;
                st.pop();
            }
            // db(i, farthest_rev[i], farthest[i], adj[i], rev_adj[i]);
            // db(i, dist);
        }
        int max_dist = 0;
        vector<int> res;
        for (size_t b = 1; b <= n; b++)
        {
            for (size_t c = 1; c <= n; c++)
            {
                if (b == c)
                    continue;
                if (forw_dist[b][c] == 0)
                    continue;
                set<int> s = {b, c};
                for (auto &d : farthest[c])
                {
                    if (s.count(d))
                        continue;
                    s.insert(d);
                    for (auto &a : farthest_rev[b])
                    {
                        if (s.count(a))
                            continue;
                        int curr = forw_dist[a][b] + forw_dist[b][c] + forw_dist[c][d];
                        if (curr > max_dist)
                        {
                            res = {a, b, c, d};
                            max_dist = curr;
                        }
                    }
                    s.erase(d);
                }
            }
        }
        db(max_dist);
        for (auto &x : res)
            cout << x << ' ';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
