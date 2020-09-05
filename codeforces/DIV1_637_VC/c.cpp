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

const int NAX = 2e5 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    int n, m;
    cin >> n >> m;
    vector<int> positions(m + 2);
    for (size_t i = 1; i <= m; i++)
        cin >> positions[i];
    positions[m + 1] = n;
    sort(all(positions));
    ll g, r;
    cin >> g >> r;
    vector<vector<int>> dist(m + 2, vector<int>(g + 1));
    vector<vector<int>> vis(m + 2, vector<int>(g + 1));
    deque<pair<int, int>> bfs;
    ll ans = LLONG_MAX;
    vis[0][0] = 1;
    bfs.pb({0, 0});
    while (bfs.size())
    {
        int node = bfs.front().f;
        int t = bfs.front().s;
        db(bfs.front(), bfs.size());
        bfs.pop_front();
        if (t == 0)
        {
            int timeToEnd = n - positions[node];
            if (timeToEnd <= g)
                ans = min(ans, (r + g) * dist[node][t] + timeToEnd);
        }
        if (t == g)
            if (!vis[node][0])
            {
                vis[node][0] = 1;
                dist[node][0] = 1 + dist[node][g];
                bfs.pb({node, 0});
            }
        if (node > 0)
        {
            int timeToEnd = t + positions[node] - positions[node - 1];
            if (timeToEnd <= g && !vis[node - 1][timeToEnd])
            {
                vis[node - 1][timeToEnd] = 1;
                dist[node - 1][timeToEnd] = dist[node][t];
                bfs.push_front({node - 1, timeToEnd});
            }
        }
        if (node + 1 <= m)
        {
            int timeToEnd = t + positions[node + 1] - positions[node];
            if (timeToEnd <= g && !vis[node + 1][timeToEnd])
            {
                vis[node + 1][timeToEnd] = 1;
                dist[node + 1][timeToEnd] = dist[node][t];
                bfs.push_front({node + 1, timeToEnd});
            }
        }
    }
    if (ans == LLONG_MAX)
        cout << -1 << '\n';
    else
        cout << ans << '\n';
}

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
