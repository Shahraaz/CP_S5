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

// ll sum(ll idx)
// {
//     if (idx < 0)
//         return 0;
//     return (idx) * (idx + 1LL) / 2;
// }

// ll sum(ll l, ll r)
// {
//     return sum(r) - sum(l - 1);
// }

struct Node
{
    long long val;
    Node(long long one = 0) : val(one) {}
    Node lazylazyMerge(const Node &rhs)
    {
        Node a = *this;
        a.val = rhs.val;
        return a;
    }
    Node seglazyMerge(const Node &rhs, const int &l, const int &r)
    {
        Node a = *this;
        a.val = (r - l + 1) * (rhs.val);
        return a;
    }
    Node segSegMerge(const Node &rhs)
    {
        Node a = *this;
        a.val = (a.val + rhs.val);
        return a;
    }
};

template <typename segNode>
struct Segtree
{
    vector<segNode> Seg, Lazy;
    vector<segNode> Base;
    vector<bool> isLazy;
    int n;
    Segtree(int _n = 1e5)
    {
        this->n = _n;
        Seg.resize(4 * _n + 10);
        Lazy.resize(4 * _n + 10);
        isLazy.resize(4 * _n + 10);
    }
    void merge(segNode &curr, segNode &l, segNode &r)
    {
        curr = l + r;
    }
    void propagate(int node, int L, int R)
    {
        if (isLazy[node])
        {
            isLazy[node] = false;
            Seg[node] = Seg[node].seglazyMerge(Lazy[node], L, R);
            if (L != R)
            {
                Lazy[2 * node] = Lazy[2 * node].lazylazyMerge(Lazy[node]);
                Lazy[2 * node + 1] = Lazy[2 * node + 1].lazylazyMerge(Lazy[node]);
                isLazy[2 * node] = true;
                isLazy[2 * node + 1] = true;
            }
            Lazy[node] = segNode();
        }
    }
    void build(int node, int start, int end)
    {
        if (start == end)
        {
            Seg[node] = Base[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
    }
    void build(vector<segNode> &Arr)
    {
        Base = Arr;
        n = Arr.size();
        Seg.resize(4 * n + 10);
        Lazy.resize(4 * n + 10);
        isLazy.resize(4 * n + 10);
        build(1, 0, n - 1);
    }
    segNode Query(int node, int start, int end, int qstart, int qend)
    {
        propagate(node, start, end);
        if (qend < start || qstart > end || start > end)
            return segNode();
        if (qstart <= start && end <= qend)
            return Seg[node];
        int mid = (start + end) / 2;
        segNode l = Query(2 * node, start, mid, qstart, qend);
        segNode r = Query(2 * node + 1, mid + 1, end, qstart, qend);
        return l.segSegMerge(r);
    }
    segNode qQuery(int node, int start, int end, int pos)
    {
        propagate(node, start, end);
        if (start == end)
            return Seg[node];
        int mid = (start + end) / 2;
        if (pos <= mid)
            return qQuery(2 * node, start, mid, pos);
        return qQuery(2 * node + 1, mid + 1, end, pos);
    }
    void Update(int node, int start, int end, int qstart, int qend, segNode val)
    {
        propagate(node, start, end);
        if (qend < start || qstart > end || start > end)
            return;
        if (qstart <= start && end <= qend)
        {
            isLazy[node] = true;
            Lazy[node] = val;
            propagate(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        Update(2 * node, start, mid, qstart, qend, val);
        Update(2 * node + 1, mid + 1, end, qstart, qend, val);
        Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
    }
    void pUpdate(int node, int start, int end, int pos, segNode val)
    {
        propagate(node, start, end);
        if (start == end)
        {
            isLazy[node] = true;
            Lazy[node] = val;
            propagate(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        if (pos <= mid)
            pUpdate(2 * node, start, mid, pos, val);
        else
            pUpdate(2 * node + 1, mid + 1, end, pos, val);
        Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
    }
    segNode query(int pos)
    {
        return qQuery(1, 0, n - 1, pos);
    }
    segNode query(int left, int right)
    {
        return Query(1, 0, n - 1, left, right);
    }
    void update(int pos, segNode val)
    {
        pUpdate(1, 0, n - 1, pos, val);
    }
    void update(int start, int end, segNode val)
    {
        Update(1, 0, n - 1, start, end, val);
    }
};

void solveCase()
{
    int n = 1e5;
    cin >> n;
    assert(n <= (100000));
    vector<int> a(n + 5);
    vector<vector<int>> poses(n + 5);
    Segtree<Node> stree(n + 5);
    int mx = 0;
    for (size_t i = 1; i <= n; i++)
    {
        a[i] = rand() % n;
        cin >> a[i];
        poses[a[i]].pb(i);
        while (poses[mx].size())
            ++mx;
        stree.update(i, Node(mx));
    }
    for (size_t i = 0; i <= n; i++)
        reverse(all(poses[i]));
    ll res = 0;
    for (size_t i = 1; i <= n; i++)
    {
        res += stree.query(i, n).val;
        int v = a[i];

        poses[v].pop_back();
        int rptr = poses[v].size() ? poses[v].back() : n + 1;
        int low = i, high = rptr - 1, f = n + 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (stree.query(mid).val > v)
                f = mid, high = mid - 1;
            else
                low = mid + 1;
        }
        stree.update(f, rptr - 1, v);
    }
    cout << res << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 100;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}