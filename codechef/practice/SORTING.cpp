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
    node *insert(int l, int r, int w);
};

node *null = new node(0, NULL, NULL);

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

const int LIM = 5e5 + 5;
node *root[LIM];
// null->left = null->right = null;

void solveCase()
{
    null->left = null->right = null;
    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> pos(n);
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        --x;

        a[i] = x;
        pos[x] = i;
    }

    for (size_t i = 0; i < n; i++)
    {
        db(i, pos[i]);
        root[i] = (i > 0 ? root[i - 1] : null)->insert(0, n - 1, pos[i]);
    }
    queue<pair<int, int>> Q;
    Q.push({0, n - 1});
    ll res = 0;
    db(a);
    while (Q.size())
    {
        auto top = Q.front();
        Q.pop();

        int l = top.first;
        int r = top.second;

        int len = r - l + 1;
        if (len <= 1)
            continue;
        int idx = (len + 1) / 2;

        int pivot = query(root[r], (l > 0 ? root[l - 1] : null), 0, n - 1, idx);
        pivot = a[pivot];
        db(l, r, len, idx, pivot);
        assert(l <= pivot && pivot <= r);
        res += len;
        Q.push({l, pivot - 1});
        Q.push({pivot + 1, r});
    }
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