//Optimise
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
auto TimeStart = chrono::steady_clock::now();

const int NAX = 1e5 + 10, MOD = 1000000007;

ll Sum[4 * NAX];
pair<int, int> MaxIdx[4 * NAX];
int a[NAX];
pair<int, int> build(int node, int start, int end)
{
    if (start > end)
        return {-1, 0};
    if (start == end)
    {
        Sum[node] = a[start];
        return MaxIdx[node] = {a[start], start};
    }
    int mid = ((ll)start + end) / 2;
    auto ret1 = build(2 * node, start, mid);
    auto ret2 = build(2 * node + 1, mid + 1, end);
    Sum[node] = Sum[2 * node] + Sum[2 * node + 1];
    if (ret1 > ret2)
        return MaxIdx[node] = ret1;
    return MaxIdx[node] = ret2;
}

ll querySum(int node, int start, int end, int qstart, int qend)
{
    if (start > end || start > qend || end < qstart)
        return 0;
    if (qstart <= start && end <= qend)
        return Sum[node];
    int mid = ((ll)start + end) / 2;
    return querySum(2 * node, start, mid, qstart, qend) +
           querySum(2 * node + 1, mid + 1, end, qstart, qend);
}

pair<int, int> queryMaxIdx(int node, int start, int end, int qstart, int qend)
{
    if (start > end || start > qend || end < qstart)
        return {-1, 0};
    if (qstart <= start && end <= qend)
        return MaxIdx[node];
    int mid = ((ll)start + end) / 2;
    auto ret1 = queryMaxIdx(2 * node, start, mid, qstart, qend);
    auto ret2 = queryMaxIdx(2 * node + 1, mid + 1, end, qstart, qend);
    if (ret1 < ret2)
        return ret2;
    return ret1;
}

pair<int, int> update(int node, int start, int end, int pos, int val)
{
    if (start > end)
        return {-1, 0};
    if (start == end)
    {
        a[pos] = val;
        MaxIdx[node] = {val, pos};
        Sum[node] = val;
        db(pos, val, Sum[node], MaxIdx[node]);
        return MaxIdx[node];
    }
    int mid = ((ll)start + end) / 2;
    if (pos <= mid)
        update(2 * node, start, mid, pos, val);
    else
        update(2 * node + 1, mid + 1, end, pos, val);
    Sum[node] = Sum[2 * node] + Sum[2 * node + 1];
    auto ret1 = MaxIdx[node * 2];
    auto ret2 = MaxIdx[2 * node + 1];
    if (ret1 > ret2)
        MaxIdx[node] = ret1;
    else
        MaxIdx[node] = ret2;
    db(node, start, end, pos, val, MaxIdx[node]);
    return MaxIdx[node];
}

void solveCase(int caseNo)
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    db("buildStart");
    build(1, 0, n - 1);
    db("buildEnd");
    while (m--)
    {
        int type, l, r, x, k;
        cin >> type;
        db(type);
        if (type == 1)
        {
            cin >> l >> r;
            --l, --r;
            db(l, r);
            cout << querySum(1, 0, n - 1, l, r) << '\n';
        }
        else if (type == 2)
        {
            cin >> l >> r >> x;
            --l, --r;
            int cnt = 5;
            while (cnt)
            {
                auto Q = queryMaxIdx(1, 0, n - 1, l, r);
                db(Q, l, r);
                if (Q.f < x)
                    break;
                if (Q.s < l || Q.s > r)
                    break;
                update(1, 0, n - 1, Q.s, a[Q.s] % x);
            }
        }
        else
        {
            cin >> k >> x;
            --k;
            db(x, k);
            update(1, 0, n - 1, k, x);
        }
    }
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