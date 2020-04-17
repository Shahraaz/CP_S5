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

vector<int> adj[NAX];
bool isClr[NAX];
int depth[NAX];
priority_queue<pair<int, int>> pq;

class Solution
{
private:
    int dfs(int node, int par)
    {
        depth[node] = depth[par] + 1;
        int sz = 1;
        for (auto &child : adj[node])
        {
            if (child == par)
                continue;
            sz += dfs(child, node);
        }
        int temp = depth[node] - sz;
        pq.push({temp, node});
        return sz;
    }
    ll calc(int node, int par, int dx)
    {
        ll temp = 0;
        if (isClr[node])
            temp += dx;
        dx += !isClr[node];
        for (auto &child : adj[node])
        {
            if (child == par)
                continue;
            temp += calc(child, node, dx);
        }
        db(node, par, dx, temp, isClr[node]);
        return temp;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, k;
        cin >> n >> k;
        for (size_t i = 1; i < n; i++)
        {
            int u, c;
            cin >> u >> c;
            adj[u].pb(c);
            adj[c].pb(u);
        }
        depth[1] = 1;
        dfs(1, 0);
        while (pq.size() && k--)
        {
            // cout << pq.top() << '\n';
            db(pq.top());
            isClr[pq.top().s] = true;
            pq.pop();
        }
        cout << calc(1, 0, 0) << '\n';
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
