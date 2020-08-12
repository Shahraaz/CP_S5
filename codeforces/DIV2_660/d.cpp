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
vector<int> adj_rev[NAX];
set<int> adj_2[NAX];
int a[NAX];
int b[NAX];
int degree[NAX];
int val[NAX];
ll dp[NAX];
int vis[NAX];

void dfs(int node, int par)
{
    vis[node] = true;
    for (auto &x : adj_rev[node])
    {
        if (!vis[x] && dp[x] > 0)
            dfs(x, node);
    }
    cout << node + 1 << ' ';
    for (auto &x : adj_rev[node])
    {
        if (!vis[x])
            dfs(x, node);
    }
}

struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        for (size_t i = 0; i < n; i++)
        {
            cin >> b[i];
            if (b[i] >= 0)
            {
                b[i]--;
                adj[i].pb(b[i]);
                adj_rev[b[i]].pb(i);
                degree[b[i]]++;
            }
        }
        queue<int> Q;
        memset(val, -1, sizeof val);
        for (size_t i = 0; i < n; i++)
            if (degree[i] == 0)
                Q.push(i);
        ll res = 0;
        vector<int> order;
        while (Q.size())
        {
            auto top = Q.front();
            order.pb(top);
            Q.pop();
            dp[top] += a[top];
            // ll add = dp[top];
            for (auto &x : adj[top])
            {
                if (dp[top] > 0)
                {
                    dp[x] += dp[top];
                    // adj_2[x].insert(top);
                }
                degree[x]--;
                if (degree[x] == 0)
                    Q.push(x);
            }
            // dp[top] = add;
            db(top, dp[top], adj[top]);
            res += dp[top];
        }
        cout << res << '\n';
        vector<int> todo;
        vector<int> first;
        for (auto &x : order)
        {
            if (dp[x] < 0)
                todo.pb(x);
            else
            {
                // first.pb(x);
                cout << x + 1 << ' ';
            }
        }
        // reverse(all(todo));
        for (auto &x : todo)
        {
            cout << x + 1 << ' ';
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
