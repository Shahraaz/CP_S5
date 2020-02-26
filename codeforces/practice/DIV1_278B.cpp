// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
#define pc(...) PC(#__VA_ARGS__, __VA_ARGS__);
template <typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> &p)
{
    out << '[' << p.first << ", " << p.second << ']';
    return out;
}
template <typename Arg>
void PC(const char *name, Arg &&arg)
{
    while (*name == ',' || *name == ' ')
        name++;
    std::cerr << name << " { ";
    for (const auto &v : arg)
        cerr << v << ' ';
    cerr << " }\n";
}
template <typename Arg1, typename... Args>
void PC(const char *names, Arg1 &&arg1, Args &&... args)
{
    while (*names == ',' || *names == ' ')
        names++;
    const char *comma = strchr(names, ',');
    std::cerr.write(names, comma - names) << " { ";
    for (const auto &v : arg1)
        cerr << v << ' ';
    cerr << " }\n";
    PC(comma, args...);
}
template <typename Arg1>
void ZZ(const char *name, Arg1 &&arg1)
{
    std::cerr << name << " = " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void ZZ(const char *names, Arg1 &&arg1, Args &&... args)
{
    const char *comma = strchr(names + 1, ',');
    std::cerr.write(names, comma - names) << " = " << arg1;
    ZZ(comma, args...);
}
#else
#define db(...)
#define pc(...)
#endif

using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 1e5 + 5, MOD = 1000000007;

template <typename inpType, int (*func)(int, int)>
struct sparseTree
{
    int n, logLim, def;
    vector<vector<int>> lookup;

    void buildSparseTable(inpType arr, int n, int def)
    {
        this->n = n;
        this->def = def;
        logLim = log2(n) + 1;
        lookup.resize(n, vector<int>(logLim, def));
        // pc(arr);
        for (int i = 0; i < n; i++)
        {
            lookup[i][0] = arr[i];
            // db(i, 0, lookup[i][0]);
        }
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 0; (i + (1 << j) - 1) < n; i++)
            {
                // db(lookup[i][j - 1], lookup[i + (1 << (j - 1))][j - 1]);
                lookup[i][j] = func(lookup[i][j - 1], lookup[i + (1 << (j - 1))][j - 1]);
                // db(i, j, lookup[i][j]);
            }
    }

    int query(int L, int R)
    {
        if (L < 0 || L > n - 1 || R < 0 || R > n - 1 || L > R)
            return def;
        int j = (int)log2(R - L + 1);
        return func(lookup[L][j], lookup[R - (1 << j) + 1][j]);
    }
};

int min(int a, int b)
{
    return std::min(a, b);
}
int max(int a, int b)
{
    return std::max(a, b);
}

struct Node
{
    long long val;
    Node(int one = MOD) : val(one) {}
    Node operator+(const Node &rhs)
    {
        Node a = *this;
        a.val = min(a.val, rhs.val);
        return a;
    }
};
ostream &operator<<(ostream &out, const Node &p)
{
    out << p.val;
    return out;
}
istream &operator>>(istream &in, Node &p)
{
    in >> p.val;
    return in;
}

struct Segtree
{
    vector<Node> Seg, Lazy;
    vector<Node> Base;
    vector<bool> isLazy;
    int n;
    Segtree(int n = 2e5)
    {
        this->n = n;
        Seg.resize(4 * n + 10);
        Lazy.resize(4 * n + 10);
        isLazy.resize(4 * n + 10);
    }
    void merge(Node &curr, Node &l, Node &r)
    {
        curr = l + r;
    }
    void propagate(int node, int L, int R)
    {
        if (isLazy[node])
        {
            isLazy[node] = false;
            Seg[node] = Seg[node] + Lazy[node];
            if (L != R)
            {
                Lazy[2 * node] = Lazy[2 * node] + Lazy[node];
                Lazy[2 * node + 1] = Lazy[2 * node + 1] + Lazy[node];
                isLazy[2 * node] = true;
                isLazy[2 * node + 1] = true;
            }
            Lazy[node] = Node();
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
        merge(Seg[node], Seg[2 * node], Seg[2 * node + 1]);
    }
    void build(vector<Node> Arr)
    {
        Base = Arr;
        n = Arr.size();
        Seg.resize(4 * n + 10);
        Lazy.resize(4 * n + 10);
        isLazy.resize(4 * n + 10);
        build(1, 0, n - 1);
    }
    Node Query(int node, int start, int end, int qstart, int qend)
    {
        propagate(node, start, end);
        if (qend < start || qstart > end || start > end)
            return Node();
        if (qstart <= start && end <= qend)
            return Seg[node];
        int mid = (start + end) / 2;
        Node l = Query(2 * node, start, mid, qstart, qend);
        Node r = Query(2 * node + 1, mid + 1, end, qstart, qend);
        Node ret;
        merge(ret, l, r);
        return ret;
    }
    Node qQuery(int node, int start, int end, int pos)
    {
        propagate(node, start, end);
        if (start == end)
            return Seg[node];
        int mid = (start + end) / 2;
        if (pos <= mid)
            return qQuery(2 * node, start, mid, pos);
        return qQuery(2 * node + 1, mid + 1, end, pos);
    }
    void Update(int node, int start, int end, int qstart, int qend, Node val)
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
        merge(Seg[node], Seg[2 * node], Seg[2 * node + 1]);
    }
    void pUpdate(int node, int start, int end, int pos, Node val)
    {
        propagate(node, start, end);
        if (start == end)
        {
            isLazy[node] = true;
            Seg[node] = Node();
            Lazy[node] = val;
            propagate(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        if (pos <= mid)
            pUpdate(2 * node, start, mid, pos, val);
        else
            pUpdate(2 * node + 1, mid + 1, end, pos, val);
        merge(Seg[node], Seg[2 * node], Seg[2 * node + 1]);
    }
    Node query(int pos)
    {
        return qQuery(1, 0, n - 1, pos);
    }
    Node query(int left, int right)
    {
        return Query(1, 0, n - 1, left, right);
    }
    void update(int pos, Node val)
    {
        pUpdate(1, 0, n - 1, pos, val);
    }
    void update(int start, int end, Node val)
    {
        Update(1, 0, n - 1, start, end, val);
    }
};

class Solution
{

private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, s, l;
        cin >> n >> s >> l;
        vector<int> dp(n, MOD), a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];

        sparseTree<vector<int>, min> minTree;
        sparseTree<vector<int>, max> maxTree;

        minTree.buildSparseTable(a, n, MOD);
        maxTree.buildSparseTable(a, n, -MOD);

        int rptr, lptr;
        rptr = lptr = n - 1;
        if (l > n)
        {
            cout << -1 << '\n';
            return;
        }
        lptr -= l - 1;
        auto checkDiff = [&minTree, &maxTree, &s](int left, int right) -> bool {
            auto maxi = maxTree.query(left, right);
            auto mini = minTree.query(left, right);
            db(left, right, maxi, mini);
            return (maxi - mini) <= s;
        };
        while (lptr >= 0 && checkDiff(lptr, rptr) == 0)
            lptr--;
        if (lptr < 0)
        {
            cout << -1 << '\n';
            return;
        }

        Segtree Dp(n);

        db(lptr);
        Dp.build(vector<Node>(n));
        Dp.update(lptr, Node(1));
        --lptr;

        int ret = MOD;
        while (lptr >= 0)
        {
            while (rptr >= 0 && checkDiff(lptr, rptr) == 0)
                rptr--;
            db(lptr, rptr);
            if ((rptr - lptr + 1) >= l)
            {
                if (rptr == n - 1)
                    Dp.update(lptr, Node(1));
                else
                {
                    Node q = Dp.query(lptr + l, rptr + (rptr != (n - 1)));
                    q.val++;
                    db(lptr, q);
                    Dp.update(lptr, q);
                }
            }
            db("\n");
            --lptr;
        }
        auto ans = Dp.query(0);
        if (ans.val > n)
            cout << -1 << '\n';
        else
            cout << ans << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
