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
const int NAX = 1e5 + 5, MOD = 1000000007;

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

int query(node *a, node *b, int l, int r, int k)
{
    if (l == r)
        return l;

    int count = a->left->count - b->left->count;
    int m = (l + r) / 2;

    db(l, r, k, count);

    if (count >= k)
        return query(a->left, b->left, l, m, k);
    return query(a->right, b->right, m + 1, r, k - count);
}

node *root[NAX];

void solveCase()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;

    auto b = a;
    sort(all(b));
    b.erase(unique(all(b)), b.end());

    db(a);
    db(b);
    for (auto &x : a)
        x = lower_bound(all(b), x) - b.begin();
    db(a);

    null->left = null->right = null;
    for (size_t i = 0; i < n; i++)
        root[i] = (i > 0 ? root[i - 1] : null)->insert(0, b.size() - 1, a[i]);

    for (size_t i = 0; i < q; i++)
    {
        int l, r, k;
        cin >> l >> r >> k;
        --l, --r;
        auto Q = query(root[r], (l == 0 ? null : root[l - 1]), 0, b.size() - 1, k);
        db(l, r, k, Q, b[Q]);
        cout << b[Q] << '\n';
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