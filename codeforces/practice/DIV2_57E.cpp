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

const int NAX = 1e6 + 5, MOD = 1000000007;
int a[NAX], b[NAX];

struct segmentTree
{
    vector<ll> Tree;
    int n;
    segmentTree(int n) : n(n)
    {
        Tree.resize(4 * n);
    }
    void update(int node, int start, int end, int pos, int val)
    {
        if (start > end)
            return;
        if (start == end)
        {
            Tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (pos <= mid)
            update(2 * node, start, mid, pos, val);
        else
            update(2 * node + 1, mid + 1, end, pos, val);
        Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
    }
    ll query(int node, int start, int end, int qstart, int qend)
    {
        if (start > end || qend < start || end < qstart)
            return 0;
        if (qstart <= start && end <= qend)
            return Tree[node];
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, qstart, qend) + query(2 * node + 1, mid + 1, end, qstart, qend);
    }
};

void solveCase(int caseNo)
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b, b + n);
    segmentTree currentElements(n), dp(n);
    ll res = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        a[i] = lower_bound(b, b + n, a[i]) - b;
        int less = currentElements.query(1, 0, n - 1, 0, a[i]);
        ll tempDp = dp.query(1, 0, n - 1, 0, a[i]);
        res += tempDp;
        dp.update(1, 0, n - 1, a[i], less);
        currentElements.update(1, 0, n - 1, a[i], 1);
        db(less, tempDp, i, a[i], res);
    }
    cout << res << '\n';
}

int main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    for (int i = 1; i <= t; ++i)
    {
        solveCase(i);
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
