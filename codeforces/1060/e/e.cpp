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

ll res = 0;

vector<int> adj[NAX];
int n;
ll sum_odd[NAX], sum_even[NAX];
ll cnt_odd[NAX], cnt_even[NAX];

void dfs(int node, int par)
{
    sum_even[node] = 0;
    cnt_even[node] = 1;
    for (auto &c : adj[node])
        if (c != par)
        {
            dfs(c, node);
            cnt_even[node] += cnt_odd[c];
            cnt_odd[node] += cnt_even[c];

            sum_even[node] += cnt_odd[c] + sum_odd[c];
            sum_odd[node] += cnt_even[c] + sum_even[c];
        }
    db(node, par);
    db(sum_even[node], cnt_even[node]);
    db(sum_odd[node], cnt_odd[node]);
}

void dfs_reroot(int node, int par)
{
    ll res_node = (sum_even[node]) / 2;
    res_node += (sum_odd[node] + cnt_odd[node]) / 2;
    res += res_node;
    db(node, par, res);

    for (auto &c : adj[node])
        if (c != par)
        {
            ll back_cnt_even_node = cnt_even[node];
            ll back_cnt_odd_node = cnt_odd[node];
            ll back_sum_even_node = sum_even[node];
            ll back_sum_odd_node = sum_odd[node];

            cnt_even[node] -= cnt_odd[c];
            cnt_odd[node] -= cnt_even[c];

            sum_even[node] -= cnt_odd[c] + sum_odd[c];
            sum_odd[node] -= cnt_even[c] + sum_even[c];

            cnt_even[c] += cnt_odd[node];
            cnt_odd[c] += cnt_even[node];

            sum_even[c] += cnt_odd[node] + sum_odd[node];
            sum_odd[c] += cnt_even[node] + sum_even[node];

            dfs_reroot(c, node);

            cnt_even[node] = back_cnt_even_node;
            cnt_odd[node] = back_cnt_odd_node;
            sum_even[node] = back_sum_even_node;
            sum_odd[node] = back_sum_odd_node;
        }
}

void solveCase()
{
    cin >> n;
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    res = 0;
    dfs(0, -1);
    dfs_reroot(0, 0);
    cout << res / 2 << '\n';
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
        solveCase();
    return 0;
}