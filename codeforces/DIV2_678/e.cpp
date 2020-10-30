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

struct Node
{
    long long val;
    Node(long long one = MOD) : val(one) {}
    Node lazylazyMerge(const Node &rhs)
    {
        Node a = *this;
        a.val = min(a.val, rhs.val);
        return a;
    }
    Node seglazyMerge(const Node &rhs, const int &l, const int &r)
    {
        Node a = *this;
        a.val = min(a.val, rhs.val);
        return a;
    }
    Node segSegMerge(const Node &rhs)
    {
        Node a = *this;
        a.val = max(a.val, rhs.val);
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
    Segtree(int _n = 2e5)
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
            return segNode(-1);
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
            // isLazy[node] = true;
            // Lazy[node] = val;
            // propagate(node, start, end);
            // db(node, start, end, val.val);
            Seg[node] = val;
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
    void print()
    {
#ifdef LOCAL
        for (size_t i = 0; i < n; i++)
            cout << query(i, i).val << ' ';
        cout << '\n';
#endif
    }
};

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> poses[n + 2];
    for (size_t i = 1; i <= n + 1; i++)
        poses[i].pb(0);
    for (size_t i = 1; i <= n; i++)
    {
        cin >> a[i];
        poses[a[i]].pb(i);
    }
    for (size_t i = 1; i <= n + 1; i++)
        poses[i].pb(n + 1);
    Segtree<Node> stree(n + 2);
    db(poses[1]);
    if (poses[1].size() == 2)
    {
        cout << 2 << '\n';
        return;
    }
    if (poses[1].size() == (n + 2))
    {
        cout << 1 << '\n';
        return;
    }
    vector<bool> possible(n + 5);
    possible[1] = 1;
    possible[2] = 1;
    stree.update(0, 0);
    // stree.print();
    for (int i = n; i >= 1; i--)
    {
        auto it = upper_bound(all(poses[a[i]]), i);
        // db(i, a[i]);
        auto next_i = *it;
        db(next_i);
        // stree.print();
        auto pref = stree.query(0, a[i] - 1).val;
        // db(pref);
        if (pref != -1 && pref < next_i)
        {
            possible[a[i]] = 1;
            db(i, a[i]);
        }
        if (pref != -1 && pref <= *upper_bound(all(poses[a[i] + 1]), i))
        {
            possible[a[i] + 1] = 1;
            db(i, a[i] + 1);
        }
        stree.update(a[i], i);
    }

    db(possible);
    for (size_t i = 1; i < n + 2; i++)
    {
        auto it = upper_bound(all(poses[i]), 0);
        if (*it <= n)
        {
            if (stree.query(0, i - 1).val <= *it)
                possible[i] = 1;
            if (stree.query(0, i).val <= *upper_bound(all(poses[i + 1]), 0))
                possible[i + 1] = 1;
        }
        if (!possible[i])
        {
            cout << i << '\n';
            return;
        }
    }
    cout << n + 2 << '\n';
    // assert(false);
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
