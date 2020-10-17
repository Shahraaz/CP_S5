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

const int N = 18;
const int MAX_MASK = 1 << (N);
const ll INF = 1e18;

int n, m;
vector<int> adj[N];
ll sum[N];
int need_mask[N];
ll dp[N + 1][N + 1][MAX_MASK];
bool p[N + 1][N + 1][MAX_MASK];

int used[NAX];
vector<int> order;

void dfs(int node, int construct)
{
    // db(node, construct);
    if (used[node])
        return;
    used[node] = 1;
    for (auto &x : adj[node])
        dfs(x, construct);
    if (construct)
        order.pb(node);
}

void solveCase()
{
    cin >> n >> m;
    for (size_t i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        --x, --y;
        sum[x] += w;
        sum[y] -= w;
        adj[x].pb(y);
    }
    for (size_t i = 0; i < n; i++)
        dfs(i, 1);
    for (size_t i = 0; i < n; i++)
    {
        fill(used, used + N, false);
        dfs(i, false);
        for (size_t j = 0; j < n; j++)
            if (i != j && used[j])
                need_mask[i] |= (1 << j);
        // db(adj[i]);
        // db(i, bitset<N>(need_mask[i]));
    }
    for (size_t i = 0; i <= n; i++)
        for (size_t j = 0; j <= n; j++)
            for (size_t k = 0; k < (1 << n); k++)
                dp[i][j][k] = INF;
    dp[0][0][0] = 0;
    reverse(all(order));
    db(order);
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j <= n; j++)
            for (size_t k = 0; k < (1 << n); k++)
            {
                if (dp[i][j][k] >= INF / 2)
                    continue;
                db(i, j, bitset<N>(k), p[i][j][k], dp[i][j][k]);
                if (j == n)
                {
                    if (dp[i + 1][0][k] > dp[i][j][k])
                    {
                        dp[i + 1][0][k] = dp[i][j][k];
                        p[i + 1][0][k] = false;
                    }
                }
                else
                {
                    int v = order[j];
                    ll add = sum[v] * i;
                    if (dp[i][j + 1][k] > dp[i][j][k])
                    {
                        dp[i][j + 1][k] = dp[i][j][k];
                        p[i][j + 1][k] = false;
                    }
                    if ((k & (1 << v)) == 0)
                        if ((need_mask[v] & k) == need_mask[v])
                        {
                            int nk = k | (1 << v);
                            if (dp[i][j + 1][nk] > dp[i][j][k] + add)
                            {
                                dp[i][j + 1][nk] = dp[i][j][k] + add;
                                p[i][j + 1][nk] = true;
                            }
                        }
                }
            }
    vector<int> ans(n);
    int i = n;
    int j = 0;
    int k = (1 << n) - 1;
    while (i > 0 || j > 0 || k > 0)
    {
        assert(i >= 0);
        assert(j >= 0);
        assert(k >= 0);
        if (j == 0)
        {
            j = n;
            --i;
        }
        else
        {
            if (p[i][j][k])
            {
                int v = order[j - 1];
                ans[v] = i;
                k ^= 1 << v;
            }
            --j;
        }
    }
    for (size_t i = 0; i < n; i++)
    {
        cout << ans[i] << ' ';
    }
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
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
