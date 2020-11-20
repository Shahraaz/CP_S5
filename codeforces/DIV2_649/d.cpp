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
int n, m, k;
vector<int> adj[NAX];
vector<int> depth(NAX, -1);
vector<int> st, cycle;
vector<int> stores[2];

void answer()
{
    if (cycle.size() <= k)
    {
        cout << 2 << '\n';
        cout << cycle.size() << '\n';
        for (auto &&x : cycle)
        {
            cout << x << ' ';
        }
        cout << '\n';
    }
    else
    {
        cout << 1 << '\n';
        for (size_t i = 0; i < k; i += 2)
            cout << cycle[i] << ' ';
        cout << '\n';
    }
    exit(0);
}

void dfs(int node, int par)
{
    int maxdepth = -1;
    db(node, par, depth[node]);
    for (auto &child : adj[node])
        if (child != par)
            if (depth[child] != -1)
                maxdepth = max(maxdepth, depth[child]);
    st.push_back(node);
    stores[depth[node] % 2].pb(node);
    db(maxdepth);
    if (maxdepth >= 0)
    {
        while (maxdepth <= depth[node])
        {
            cycle.pb(st[maxdepth]);
            ++maxdepth;
        }
        answer();
    }
    for (auto &child : adj[node])
        if (child != par)
        {
            depth[child] = depth[node] + 1;
            dfs(child, node);
        }
    st.pop_back();
}

void solveCase()
{
    cin >> n >> m >> k;
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    depth[1] = 0;
    dfs(1, 1);
    if (stores[0].size() < stores[1].size())
        swap(stores[0], stores[1]);
    db(stores[0]);
    db(stores[1]);
    cout << 1 << '\n';
    for (size_t i = 0; 2 * i < k; i += 1)
        cout << stores[0][i] << ' ';
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef TIMER
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}