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

struct node
{
    int count;
    node *left, *right;

    node(int _count, node *_left, node *_right) : count(_count), left(_left), right(_right) {}
    node *insert(int l, int r, int w, int nval);
};

node *null = new node(MOD, NULL, NULL);

node *node::insert(int l, int r, int w, int nval)
{
    if (l <= w && w <= r)
    {
        if (l == r)
            return new node(min(this->count, nval), null, null);

        int mid = (l + r) / 2;

        node *ret = new node(this->count, this->left, this->right);
        if (w <= mid)
            ret->left = ret->left->insert(l, mid, w, nval);
        else
            ret->right = ret->right->insert(mid + 1, r, w, nval);

        ret->count = min({ret->count, ret->left->count, ret->right->count});

        return ret;
    }
    return this;
}

int query(node *a, int l, int r, int ql, int qr)
{
    if (qr < l || r < ql || l > r)
        return MOD;

    if (ql <= l && r <= qr)
        return a->count;

    int mid = (l + r) / 2;

    return min(query(a->left, l, mid, ql, qr), query(a->right, mid + 1, r, ql, qr));
}

const int LIM = 1e5 + 5;
node *root[LIM];
// null->left = null->right = null;

void solveCase()
{
    null->left = null->right = null;
    int n, r;
    cin >> n >> r;
    --r;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<vector<int>> adj(n);
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<int> intime(n), outtime(n), h(n);
    vector<vector<int>> same_ht(n + 1);
    int timer = 0;
    function<void(int, int)> dfs = [&](int node, int par) -> void {
        same_ht[h[node]].pb(node);
        intime[node] = timer++;
        for (auto &x : adj[node])
        {
            if (x == par)
                continue;
            h[x] = h[node] + 1;
            dfs(x, node);
        }
        outtime[node] = timer - 1;
        db(node, par, intime[node], outtime[node]);
    };
    dfs(r, r);
    auto curr_root = null;
    for (size_t i = 0; i < same_ht.size(); i++)
    {
        for (auto &node : same_ht[i])
            curr_root = curr_root->insert(0, n - 1, intime[node], a[node]);
        root[i] = curr_root;
    }
    int ans = 0;
    int q;
    cin >> q;
    while (q--)
    {
        int p, q;
        cin >> p >> q;
        p = (p + ans) % n;
        q = (q + ans) % n;
        int ht = min(n, h[p] + q);
        ans = query(root[ht], 0, n - 1, intime[p], outtime[p]);
        cout << ans << '\n';
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