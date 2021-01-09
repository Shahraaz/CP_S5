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

vector<int> adj[NAX];
int start_ptr[NAX], end_ptr[NAX], CLOCK = 0, par[NAX];

void dfs(int node, int par)
{
    ::par[node] = par;
    start_ptr[node] = CLOCK;
    CLOCK++;
    for (auto &x : adj[node])
        if (x != par)
            dfs(x, node);
    end_ptr[node] = CLOCK - 1;
    db(node, start_ptr[node], end_ptr[node]);
}

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    {
        auto b = a;
        sort(all(b));
        for (auto &x : a)
            x = lower_bound(all(b), x) - b.begin();
    }
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(0, 0);
    vector<vector<int>> tour_locations(n);
    for (size_t i = 0; i < n; i++)
        tour_locations[a[i]].pb(start_ptr[i]);
    for (size_t i = 0; i < n; i++)
    {
        sort(all(tour_locations[i]));
        db(i, tour_locations[i]);
    }
    auto get_subtree = [&](int node, int color) -> int {
        int ret = upper_bound(all(tour_locations[color]), end_ptr[node]) - lower_bound(all(tour_locations[color]), start_ptr[node]);
        db(node, color, ret);
        return ret;
    };
    vector<int> delta(n + 1);
    for (size_t i = 0; i < n; i++)
    {
        int color = a[i];
        int overall = tour_locations[color].size();
        db(i, color, overall);
        for (auto &c : adj[i])
            if (c != par[i])
            {
                int below = get_subtree(c, color);
                if (below > 0)
                {
                    delta[0]++;
                    delta[n]--;

                    delta[start_ptr[c]]--;
                    delta[end_ptr[c] + 1]++;
                }
            }
        if (i != 0)
        {
            int me = overall - get_subtree(i, color);
            if (me > 0)
            {
                delta[start_ptr[i]]++;
                delta[end_ptr[i] + 1]--;
            }
        }
        db(delta);
    }
    int sum = 0, ans = 0;
    for (size_t i = 0; i < n; i++)
    {
        sum += delta[i];
        db(i, sum);
        ans += sum == 0;
    }
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
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}