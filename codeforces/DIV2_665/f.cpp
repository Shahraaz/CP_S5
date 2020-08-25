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

const int NAX = (1 << 18) + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

struct Node
{
    ll sum;
    Node *l, *r;
    int swap, reverse;
    Node(ll sum = 0)
    {
        this->sum = sum;
        l = r = nullptr;
        swap = reverse = 0;
    }
};

int n;
int a[NAX];
int levelRev[25], levelswap[25];

Node *build(int left, int right)
{
    // db(left, right);
    if (left > right || left >= (1 << ::n) || right < 0)
        return nullptr;
    Node *n = new Node();
    if (n == nullptr)
        n = new Node();
    if (left == right)
    {
        n->sum = a[left];
        return n;
    }
    int mid = (left + right) / 2;
    n->l = build(left, mid);
    n->r = build(mid + 1, right);
    // db(left, mid, right);
    n->sum = n->l->sum + n->r->sum;
    return n;
}

void rev(Node *node, int left, int right, int idx, int val, int level)
{
    if (left > right || left >= (1 << ::n) || right < 0)
        return;
    if (left == right)
    {
        node->sum = val;
        return;
    }
    if ((node->reverse & 1) != (levelRev[level] & 1))
    {
        node->reverse++;
        swap(node->l, node->r);
    }
    if ((node->swap & 1) != (levelswap[level] & 1))
    {
        node->swap++;
        swap(node->l, node->r);
    }
    int mid = (left + right) / 2;
    if (idx <= mid)
        rev(node->l, left, mid, idx, val, level - 1);
    else
        rev(node->r, mid + 1, right, idx, val, level - 1);
    node->sum = node->l->sum + node->r->sum;
}

ll query(Node *node, int lptr, int rptr, int ql, int qr, int level)
{
    if (lptr > rptr || qr < lptr || rptr < ql)
        return 0;
    if (ql <= lptr && rptr <= qr)
        return node->sum;
    if ((node->reverse & 1) != (levelRev[level] & 1))
    {
        node->reverse++;
        swap(node->l, node->r);
    }
    if ((node->swap & 1) != (levelswap[level] & 1))
    {
        node->swap++;
        swap(node->l, node->r);
    }
    int mid = (lptr + rptr) / 2;
    return query(node->l, lptr, mid, ql, qr, level - 1) + query(node->r, mid + 1, rptr, ql, qr, level - 1);
}

void Solution::solveCase()
{
    int q;
    cin >> n >> q;
    for (size_t i = 0; i < (1 << n); i++)
        cin >> a[i];
    auto root = build(0, (1 << n) - 1);
    for (size_t i = 0; i < q; i++)
    {
        int ch;
        cin >> ch;
        if (ch == 1)
        {
            int x, k;
            cin >> x >> k;
            --x;
            rev(root, 0, (1 << n) - 1, x, k, n);
        }
        else if (ch == 2)
        {
            int k;
            cin >> k;
            for (size_t i = 0; i <= k; i++)
                levelRev[i]++;
        }
        else if (ch == 3)
        {
            int k;
            cin >> k;
            levelswap[k + 1]++;
        }
        else
        {
            int l, r;
            cin >> l >> r;
            --l, --r;
            cout << query(root, 0, (1 << n) - 1, l, r, n) << '\n';
        }
#ifdef LOCAL
        for (size_t i = 0; i < (1 << n); i++)
        {
            cout << query(root, 0, (1 << n) - 1, i, i, n) << ' ';
        }
        cout << '\n';
#endif
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
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
