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

struct Solution
{
    Solution() {}
    void solveCase();
};

struct Node
{
    long long val;
    Node(long long one = 0) : val(one) {}
    Node operator+(const Node &rhs)
    {
        Node a = *this;
        a.val = (a.val + rhs.val);
        return a;
    }
    Node lazylazyMerge(const Node &rhs)
    {
        Node a = *this;
        a.val = (a.val + rhs.val);
        return a;
    }
    Node seglazyMerge(const Node &rhs)
    {
        Node a = *this;
        a.val = (a.val + rhs.val);
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
            Seg[node] = Seg[node].seglazyMerge(Lazy[node]);
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

void Solution::solveCase()
{
    const int LEFT_LIM = 0;
    const int RIGHT_LIM = 1e6;
    int h, v;
    cin >> h >> v;
    ll res = 1;
    db(h, v);
    vector<vector<int>> vecc;
    for (size_t i = 0; i < h; i++)
    {
        int y, l, r;
        cin >> y >> l >> r;
        if (l == LEFT_LIM && r == RIGHT_LIM)
            res++;
        vecc.pb({y, 0, l, r});
    }
    db(vecc);
    // sort(all(vecc));
    vector<vector<int>> goUp, goDown;
    for (size_t i = 0; i < v; i++)
    {
        int x, up, down;
        cin >> x >> down >> up;
        if (down == LEFT_LIM)
        {
            if (up == RIGHT_LIM)
                res++;
            goUp.pb({up, 1, x, down});
        }
        else
        {
            goDown.pb({-down, 1, x, up});
        }
    }
    db(goUp, goDown);
    for (auto &x : vecc)
        goUp.pb(x);
    sort(all(goUp));
    db(goUp);
    Segtree<Node> b1(RIGHT_LIM + 1);
    for (auto &x : goUp)
    {
        if (x[1] == 0)
            b1.update(x[2], x[3], 1);
        else
        {
            auto temp = b1.query(x[2]).val;
            db(x[2], temp);
            res += temp;
        }
    }
    for (auto x : vecc)
    {
        x[0] = -x[0];
        goDown.pb(x);
    }
    sort(all(goDown));
    db(goDown);
    Segtree<Node> b2(RIGHT_LIM + 1);
    for (auto &x : goDown)
    {
        if (x[1] == 0)
            b2.update(x[2], x[3], 1);
        else
        {
            auto temp = b2.query(x[2]).val;
            db(x[2], temp);
            res += temp;
        }
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
