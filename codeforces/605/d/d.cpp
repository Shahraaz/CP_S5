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
    // long long val;
    set<pair<int, int>> vals;
    Node() {}
    Node lazylazyMerge(const Node &rhs)
    {
        // Node a = *this;
        // a.val = (a.val + rhs.val);
        // return a;
    }
    Node seglazyMerge(const Node &rhs, const int &l, const int &r)
    {
        // Node a = *this;
        // a.val += (r - l + 1) * (rhs.val);
        // return a;
    }
    Node segSegMerge(const Node &rhs)
    {
        // Node a = *this;
        // for (auto &x : rhs.vals)
        //     a.vals.insert(x);
        // return a;
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
    pair<int, int> Query(int node, int start, int end, int qstart, int qend)
    {
        propagate(node, start, end);
        if (qend < start || qstart > end || start > end)
            return pair<int, int>(MOD, MOD);
        if (qstart <= start && end <= qend)
        {
            if ((Seg[node].vals).empty())
                return pair<int, int>(MOD, MOD);
            return *((Seg[node].vals).begin());
        }
        int mid = (start + end) / 2;
        auto l = Query(2 * node, start, mid, qstart, qend);
        auto r = Query(2 * node + 1, mid + 1, end, qstart, qend);
        return min(l, r);
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
    void pUpdate(int node, int start, int end, int pos, pair<int, int> val)
    {
        Seg[node].vals.insert(val);
        // propagate(node, start, end);
        if (start == end)
        {
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
        // Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
    }
    void pdel(int node, int start, int end, int pos, pair<int, int> val)
    {
        Seg[node].vals.erase(val);
        // propagate(node, start, end);
        if (start == end)
        {
            // isLazy[node] = true;
            // Lazy[node] = val;
            // propagate(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        if (pos <= mid)
            pdel(2 * node, start, mid, pos, val);
        else
            pdel(2 * node + 1, mid + 1, end, pos, val);
        // Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
    }
    segNode query(int pos)
    {
        return qQuery(1, 0, n - 1, pos);
    }
    pair<int, int> query(int left, int right)
    {
        return Query(1, 0, n - 1, left, right);
    }
    void update(int pos, pair<int, int> val)
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
    int n;
    cin >> n;
    db(n);
    vector<pair<pair<int, int>, pair<int, pair<int, int>>>> a(n);
    vector<int> ranges;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i].first.first >> a[i].first.second;
        cin >> a[i].second.first >> a[i].second.second.first;
        a[i].second.second.second = i;
        ranges.pb(a[i].first.first);
        ranges.pb(a[i].second.first);
    }
    sort(all(ranges));
    ranges.erase(unique(all(ranges)), ranges.end());
    for (size_t i = 0; i < n; i++)
    {
        a[i].first.first = lower_bound(all(ranges), a[i].first.first) - ranges.begin();
        a[i].second.first = lower_bound(all(ranges), a[i].second.first) - ranges.begin();
    }
    sort(all(a));
    db(a);
    vector<int> prev(n, -1), dist(n, MOD);
    queue<int> Q;
    Segtree<Node> stree(n);
    for (size_t i = 0; i < n; i++)
    {
        if (a[i].first.first == 0 && a[i].first.second == 0)
        {
            Q.push(i);
            dist[i] = 0;
        }
        else
            stree.update(i, {a[i].first.second, i});
    }
    // db(a);
    while (Q.size())
    {
        auto curr_idx = Q.front();
        db(curr_idx, dist[curr_idx]);
        Q.pop();
        int c = a[curr_idx].second.first;
        int d = a[curr_idx].second.second.first;
        int idx2 = lower_bound(all(a), make_pair(make_pair(c + 1, 0), make_pair(0, make_pair(0, 0)))) - a.begin();
        --idx2;
        db(idx2);
        while (true)
        {
            auto q = stree.query(0, idx2);
            db(curr_idx, q);
            if (q.first > d)
                break;
            int idx = q.second;
            Q.push(idx);
            dist[idx] = dist[curr_idx] + 1;
            // db(idx, dist[idx], curr_idx, dist[curr_idx + 1]);
            prev[idx] = curr_idx;
            stree.pdel(1, 0, n - 1, idx, q);
        }
    }
    db(n);
    for (size_t i = 0; i < n; i++)
    {
        if (a[i].second.second.second == (n - 1))
        {
            if (dist[i] != MOD)
            {
                cout << dist[i] + 1 << '\n';
                vector<int> path;
                int curr = i;
                while (curr >= 0)
                {
                    path.pb(curr);
                    curr = prev[curr];
                }
                for (int i = path.size() - 1; i >= 0; i--)
                {
                    cout << a[path[i]].second.second.second + 1 << ' ';
                }
                cout << '\n';
                return;
            }
        }
    }
    cout << -1 << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    db("start");
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}