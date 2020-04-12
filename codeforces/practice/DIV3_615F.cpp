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

int p[NAX];
vector<int> adj[NAX];

class Solution
{
private:
    pair<int, int> dfs(int node, int par = -1, int dist = 0)
    {
        p[node] = par;
        pair<int, int> res = {dist, node};
        for (auto &child : adj[node])
            if (child != par)
                res = max(res, dfs(child, node, dist + 1));
        return res;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        for (size_t i = 1; i < n; i++)
        {
            int x, y;
            cin >> x >> y;
            --x, --y;
            adj[x].pb(y);
            adj[y].pb(x);
        }
        pair<int, int> da = dfs(0);
        pair<int, int> db = dfs(da.s);
        vector<int> diam;
        int v = db.s;
        while (v != da.s)
        {
            diam.pb(v);
            v = p[v];
        }
        diam.pb(da.s);
        if (diam.size() == n)
        {
            cout << n - 1 << '\n';
            cout << diam.front() + 1 << ' ' << diam.back() + 1 << ' ' << diam[1] + 1 << '\n';
        }
        else
        {
            queue<int> q;
            vector<int> d(n, -1);
            for (auto &x : diam)
            {
                q.push(x);
                d[x] = 0;
            }
            while (q.size())
            {
                int v = q.front();
                q.pop();
                for (auto &child : adj[v])
                    if (d[child] == -1)
                    {
                        d[child] = d[v] + 1;
                        q.push(child);
                    }
            }
            pair<int, int> mx = {d[0], 0};
            for (size_t v = 0; v < n; v++)
                mx = max(mx, {d[v], v});
            cout << diam.size() - 1 + mx.f << '\n';
            cout << diam.front() + 1 << ' ' << mx.s + 1 << ' ' << diam.back() + 1 << '\n';
        }
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
