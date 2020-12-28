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

struct Node
{
    long long val;
    Node(long long one = 0) : val(one) {}
    Node lazylazyMerge(const Node &rhs)
    {
        Node a = *this;
        a.val = (a.val + rhs.val);
        return a;
    }
    Node seglazyMerge(const Node &rhs, const int &l, const int &r)
    {
        Node a = *this;
        a.val += (r - l + 1) * (rhs.val);
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
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> p(m);
    vector<int> vecc(m, MOD);
    for (auto &x : p)
    {
        cin >> x.first >> x.second;
        --x.first;
        --x.second;
    }
    sort(all(p));
    db(p);
    auto compute_time = [&](int idxPerson, int startTime) {
        int start = max(p[idxPerson].first, startTime);
        int endd = min(p[idxPerson].second, startTime + k - 1);
        int tt = endd - start + 1;
        if (tt < 0)
            tt = 0;
        return tt;
    };
    ll res = 0;
    // db(p);

    for (size_t i = 0; i < n; i++)
    {
        ll one = 0;
        Segtree<Node> stree(n);
        for (size_t j = 0; j < m; j++)
        {
            int t = compute_time(j, i);
            db(i, j, t);
            if (t == 0)
            {
                vecc[j] = MOD;
                stree.update(p[j].first, p[j].second, 1);
            }
            else if (t == (p[j].second - p[j].first + 1))
            {
                vecc[j] = MOD;
                one += t;
            }
            else
            {
                if (t >= compute_time(j, i + 1))
                {
                    vecc[j] = MOD;
                    one += t;
                }
                else
                {
                    int lptr = i, rptr = p[j].second, ans = rptr + 1;
                    while (lptr <= rptr)
                    {
                        int mid = (lptr + rptr) / 2;
                        int two = compute_time(j, mid);
                        if (two >= t)
                            lptr = mid + 1;
                        else
                        {
                            ans = min(ans, mid);
                            rptr = mid - 1;
                        }
                    }
                    db(i, j, one, ans, compute_time(j, ans));
                    // if (ans >= n)
                    stree.update(p[j].first, p[j].second, 1);
                    vecc[j] = ans;
                }
            }
        }
        db(i, one, vecc);
        vector<vector<int>> events(n);
        for (size_t j = 0; j < m; j++)
            if (vecc[j] < n)
                events[vecc[j]].pb(j);
        res = max(res, one);
        for (int j = i; j < n; j++)
        {
            for (auto &x : events[j])
            {
                one += compute_time(x, i);
                stree.update(p[x].first, p[x].second, -1);
            }
            res = max(res, one + stree.query(j, min(n - 1, j + k - 1)).val);
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
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}