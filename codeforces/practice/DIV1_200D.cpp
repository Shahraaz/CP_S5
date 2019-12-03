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

const int NAX = 5e5 + 10, MOD = 1000000007;
vector<int> adj[NAX];
int startSegment[NAX], endSegment[NAX], idx[NAX], timer;

void dfs(int node, int par)
{
    startSegment[node] = ++timer;
    for (auto child : adj[node])
        if (child != par)
            dfs(child, node);
    endSegment[node] = timer;
    // db(node, startSegment[node], endSegment[node]);
}

int Tree[NAX * 4];
bool isLazy[4 * NAX], ToSet[4 * NAX];
int NodeSet[NAX];

void propagate(int node, int start, int end)
{
    if (isLazy[node])
    {
        if (ToSet[node])
        {
            NodeSet[start] = true;
            Tree[node] = end - start + 1;
        }
        else
            Tree[node] = 0;
        if (start != end)
        {
            ToSet[2 * node + 1] = ToSet[2 * node] = ToSet[node];
            isLazy[2 * node + 1] = isLazy[2 * node] = isLazy[node];
        }
        isLazy[node] = false;
        ToSet[node] = false;
    }
}

void update(int node, int start, int end, int qstart, int qend, bool set)
{
    if (qend < start || qstart > end || start > end)
        return;
    propagate(node, start, end);
    if (qstart <= start && end <= qend)
    {
        isLazy[node] = true;
        ToSet[node] = set;
        propagate(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    update(2 * node, start, mid, qstart, qend, set);
    update(2 * node + 1, mid + 1, end, qstart, qend, set);
    Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
}

void update2(int node, int start, int end, int pos)
{
    if (start > end)
        return;
    propagate(node, start, end);
    if (start == end)
    {
        if (NodeSet[start])
            Tree[node]--;
        NodeSet[start] = false;
        return;
    }
    int mid = (start + end) / 2;
    if (pos <= mid)
        update2(2 * node, start, mid, pos);
    else
        update2(2 * node + 1, mid + 1, end, pos);
    Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
}

int query(int node, int start, int end, int qstart, int qend)
{
    if (qend < start || qstart > end || start > end)
        return 0;
    propagate(node, start, end);
    if (qstart <= start && end <= qend)
        return Tree[node];
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, qstart, qend) + query(2 * node + 1, mid + 1, end, qstart, qend);
}

void solveCase(int caseNo)
{
    int n, u, v;
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1, 0);
    int q, type, node;
    cin >> q;
    while (q--)
    {
        cin >> type >> node;
        switch (type)
        {
        case 1:
            db("Fill", node);
            update(1, startSegment[1], endSegment[1], startSegment[node], endSegment[node], 1);
            break;
        case 2:
            db("UNFill", node);
            update2(1, startSegment[1], endSegment[1], startSegment[node]);
            break;
        case 3:
            int Q = query(1, startSegment[1], endSegment[1], startSegment[node], endSegment[node]);
            db(Q, node);
            cout << (Q == (endSegment[node] - startSegment[node] + 1)) << '\n';
            break;
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