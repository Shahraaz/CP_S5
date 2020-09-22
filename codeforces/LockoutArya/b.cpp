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
    long long passes;
    int idx;
    int idx2;
    Node(long long one = MOD, int i = -1, int j = -1) : passes(one), idx(i), idx2(j) {}
    Node lazylazyMerge(const Node &rhs)
    {
        Node a = *this;
        // a.val = (a.val + rhs.val);
        return a;
    }
    Node seglazyMerge(const Node &rhs)
    {
        Node a = *this;
        // a.val = (a.val + rhs.val);
        return a;
    }
    Node segSegMerge(const Node &rhs)
    {
        Node a = *this;
        if (a.passes > rhs.passes)
            a = rhs;
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
            // isLazy[node] = true;
            // Lazy[node] = val;
            // propagate(node, start, end);
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
};

void solveCase()
{
    int n, m, s;
    cin >> n >> m >> s;
    vector<pair<int, int>> a(m);
    vector<pair<int, int>> ranges;
    for (size_t i = 0; i < m; i++)
    {
        auto &x = a[i];
        cin >> x.f;
        x.s = i;
        ranges.pb({x.f, 0});
    }
    vector<pair<int, int>> bc(n);
    for (auto &x : bc)
        cin >> x.f;
    for (size_t i = 0; i < n; i++)
    {
        auto &x = bc[i];
        cin >> x.s;
        ranges.pb({x.f, i});
    }
    sort(all(ranges));
    db(ranges);
    for (auto &x : a)
        x.f = lower_bound(all(ranges), make_pair(x.f, 0)) - ranges.begin();
    for (int i = 0; i < n; i++)
    {
        auto &x = bc[i];
        x.f = lower_bound(all(ranges), make_pair(x.f, i)) - ranges.begin();
    }
    sort(all(a));
    db(a);
    db(bc);
    int low = 0, high = m, ans = MOD;
    vector<int> res(m);
    Segtree<Node> stree(ranges.size() + 1);
    for (size_t i = 0; i < n; i++)
        stree.update(bc[i].f, Node(bc[i].s, i, bc[i].f));
    auto check = [&](int days) -> int {
        if (days == 0)
            return false;
        auto copytree = stree;
        ll passses = 0;
        int backUp = 0;
        int idx = 0;
        for (int i = m - 1; i >= 0; i--)
        {
            if (backUp)
            {
                backUp--;
                res[a[i].s] = idx;
            }
            else
            {
                auto temp = copytree.query(a[i].f, ranges.size() - 1);
                db(a[i], temp.passes, temp.idx);
#ifdef LOCAL
                for (size_t i = 0; i < ranges.size(); i++)
                {
                    auto temp = copytree.query(i);
                    cout << i << ' ' << temp.passes << ' ' << temp.idx << ' ' << temp.idx2 << '\n';
                }
                cout << '\n';
#endif
                if (temp.idx == -1)
                    return false;
                passses += temp.passes;
                backUp = days - 1;
                idx = res[a[i].s] = temp.idx;
                copytree.update(temp.idx2, Node());
            }
        }
        db(days, passses, s);
        db(res);
        return passses <= s;
    };
    while (low <= high)
    {
        int mid = (low + high) / 2;
        auto now = check(mid);
        if (now)
        {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    if (ans == MOD)
    {
        cout << "NO\n";
    }
    else
    {
        check(ans);
        cout << "YES\n";
        for (auto &x : res)
        {
            cout << x + 1 << ' ';
        }
        cout << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
