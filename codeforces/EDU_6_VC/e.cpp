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

const int NAX = 4e5 + 5, MOD = 1000000007;

struct Node
{
    ll val;
    Node(ll one = 0) : val(one) {}
    Node operator+(const Node &rhs)
    {
        Node a = *this;
        a.val = (a.val + rhs.val);
        return a;
    }
    Node lazylazyMerge(const Node &rhs)
    {
        Node a = *this;
        a.val = rhs.val;
        return a;
    }
    Node seglazyMerge(const Node &rhs)
    {
        Node a = *this;
        a.val = (rhs.val);
        return a;
    }
    Node segSegMerge(const Node &rhs)
    {
        Node a = *this;
        a.val = a.val | rhs.val;
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
    Segtree(int _n = 0)
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
            Seg[node] = val;
            // isLazy[node] = true;
            // Lazy[node] = val;
            // propagate(node, start, end);
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

vector<int> adj[NAX];
int lptr[NAX], rptr[NAX];
int timer = 0;
struct Solution
{
    int dfs(int node, int par)
    {
        lptr[node] = rptr[node] = timer++;
        for (auto &x : adj[node])
            if (x != par)
                rptr[node] = dfs(x, node);
        return rptr[node];
    }
    Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        vector<int> clr;
        Segtree<Node> segtree(n);
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            clr.pb(x - 1);
        }
        for (size_t i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs(0, 0);
        for (size_t i = 0; i < n; i++)
            segtree.update(lptr[i], Node(1LL << clr[i]));
        while (m--)
        {
            int t, v, c;
            cin >> t;
            if (t == 1)
            {
                cin >> v >> c;
                --c, --v;
                segtree.update(lptr[v], rptr[v], Node(1LL << c));
            }
            else
            {
                cin >> v;
                --v;
                db(v, lptr[v], rptr[v]);
                db(segtree.query(lptr[v], rptr[v]).val);
                cout << __builtin_popcountll(segtree.query(lptr[v], rptr[v]).val) << '\n';
            }
        }
    }
};

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
