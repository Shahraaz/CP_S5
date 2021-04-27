#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> a(n);
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        --x;
        if (x == -2)
            x = i + 1;
        a[i] = x;
        adj[x].pb(i);
    }
    db(a);
    int timer = n;
    vector<int> p(n + 1);
    function<void(int)> dfs = [&](int node) -> void {
        db(node, timer, adj[node]);
        p[node] = timer--;
        for (auto &x : adj[node])
            dfs(x);
    };
    dfs(n);
    deque<int> q;
    for (int i = n - 1; i >= 0; i--)
    {
        db(i, p[i], q);
        while (q.size() && p[q.front()] < p[i])
            q.pop_front();
        if ((q.empty() && a[i] != n) || (q.size() && a[i] != q.front()))
        {
            cout << -1 << '\n';
            return;
        }
        q.push_front(i);
    }
    for (size_t i = 0; i < n; i++)
        cout << p[i] + 1 << ' ';
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}