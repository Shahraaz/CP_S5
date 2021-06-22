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

int n, k;

struct info
{
    ll cnt[7], sum[7];
    info()
    {
        memset(cnt, 0, sizeof cnt);
        memset(sum, 0, sizeof sum);
    }
};

info operator+(info l, info r)
{
    info ret;
    for (size_t i = 0; i < 7; i++)
    {
        ret.cnt[i] = l.cnt[i] + r.cnt[i];
        ret.sum[i] = l.sum[i] + r.sum[i];
    }
    return ret;
}

info promote(info l)
{
    info ret = l;
    rotate(ret.cnt, ret.cnt + k - 1, ret.cnt + k);
    rotate(ret.sum, ret.sum + k - 1, ret.sum + k);
    for (size_t i = 0; i < 7; i++)
        ret.sum[i] = ret.sum[i] + ret.cnt[i];
    return ret;
}

ll res = 0;

info merge(info a, info b)
{
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
        {
            int ca = a.cnt[i];
            ll sa = a.sum[i];

            int cb = b.cnt[j];
            ll sb = b.sum[j];

            int rem = (k - (i + j) % k) % k;

            ll res_now = sa * cb + sb * ca + rem * 1LL * ca * cb;
            assert(res_now % k == 0);
            res += res_now / k;
        }
    return a + b;
}

vector<int> adj[NAX];

info dfs(int node, int par)
{
    info ret;
    ret.cnt[0] = 1;
    ret.sum[0] = 0;
    for (auto &x : adj[node])
    {
        if (x == par)
            continue;
        ret = merge(ret, dfs(x, node));
    }
    return promote(ret);
}

void solveCase()
{
    cin >> n >> k;
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(0, 0);
    cout << res << '\n';
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