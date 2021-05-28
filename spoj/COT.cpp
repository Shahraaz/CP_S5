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
const int NAX = 1e5 + 5, MOD = 1000000007, LOG = 19;

int v[NAX], pa[NAX][LOG], RM[NAX], depth[NAX], maxi = 0;
vector<int> adj[NAX];
map<int, int> M;

struct node
{
    int count;
    node *left, *right;

    node(int _count, node *_left, node *_right) : count(_count), left(_left), right(_right) {}
    node *insert(int l, int r, int w);
};

node *null = new node(0, NULL, NULL);
// null->left = null->right = null;

node *node::insert(int l, int r, int w)
{
    if (l <= w && w <= r)
    {
        if (l == r)
            return new node(this->count + 1, null, null);

        int mid = (l + r) / 2;

        return new node(this->count + 1, this->left->insert(l, mid, w), this->right->insert(mid + 1, r, w));
    }
    return this;
}

int query(node *a, node *b, node *c, node *d, int l, int r, int k)
{
    if (l == r)
        return l;

    int count = a->left->count + b->left->count - c->left->count - d->left->count;
    int m = (l + r) / 2;

    if (count >= k)
        return query(a->left, b->left, c->left, d->left, l, m, k);
    return query(a->right, b->right, c->right, d->right, m + 1, r, k - count);
}

node *root[NAX];

void dfs(int cur, int prev)
{
    pa[cur][0] = prev;
    depth[cur] = (prev == -1 ? 0 : depth[prev] + 1);

    root[cur] = (prev == -1 ? null : root[prev])->insert(0, maxi, M[v[cur]]);
    for (auto &x : adj[cur])
        if (x != prev)
            dfs(x, cur);
}

int LCA(int u, int v)
{

    if (depth[u] < depth[v])
        return LCA(v, u);

    int diff = depth[u] - depth[v];

    for (size_t i = 0; i < LOG; i++)
        if ((diff >> i) & 1)
            u = pa[u][i];

    if (u != v)
    {
        for (int i = LOG - 1; i >= 0; i--)
            if (pa[u][i] != pa[v][i])
            {
                u = pa[u][i];
                v = pa[v][i];
            }
        u = pa[u][0];
    }

    return u;
}

void solveCase()
{
    int n, m;
    cin >> n >> m;
    null->left = null->right = null;

    for (size_t i = 0; i < n; i++)
    {
        cin >> v[i];
        M[v[i]];
    }

    maxi = 0;
    for (auto &x : M)
    {
        x.second = maxi;
        RM[maxi] = x.first;
        maxi++;
    }

    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;

        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs(0, -1);

    for (size_t i = 0; i + 1 < LOG; i++)
        for (size_t j = 0; j < n; j++)
            if (pa[j][i] != -1)
                pa[j][i + 1] = pa[pa[j][i]][i];

    for (size_t i = 0; i < m; i++)
    {
        int u, v, k;
        cin >> u >> v >> k;
        --u, --v;

        auto lca = LCA(u, v);

        int ans = query(root[u], root[v], root[lca], (pa[lca][0] == -1) ? null : root[pa[lca][0]], 0, maxi, k);

        cout << RM[ans] << '\n';
    }
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