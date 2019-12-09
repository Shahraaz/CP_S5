//Optimise
// Fake it until u make it
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

const int NAX = 2e5 + 10, MOD = 1000000007;

struct BIT
{
    int N;
    vector<long long> bit;

    void init(int n)
    {
        N = n;
        bit.assign(n + 1, 0);
    }

    void update(int idx, long long val)
    {
        while (idx <= N)
        {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    void updateMax(int idx, long long val)
    {
        while (idx <= N)
        {
            bit[idx] = max(bit[idx], val);
            idx += idx & -idx;
        }
    }

    long long pref(int idx)
    {
        long long ans = 0;
        while (idx > 0)
        {
            ans += bit[idx];
            idx -= idx & -idx;
        }
        return ans;
    }

    long long rsum(int l, int r)
    {
        return pref(r) - pref(l - 1);
    }

    long long prefMax(int idx)
    {
        long long ans = -2e9;
        while (idx > 0)
        {
            ans = max(ans, bit[idx]);
            idx -= idx & -idx;
        }
        return ans;
    }
};

int n, q;
long long root = 0;
int level[NAX], chain[NAX], idx[NAX], depth[NAX];
BIT bit[NAX], global;
vector<int> adj[NAX];

void dfs(int node, int par, int lvl, int ch)
{
    level[node] = lvl;
    chain[node] = ch;
    depth[ch] = max(depth[ch], lvl);
    db(node, level[node], lvl, ch, chain[node], depth[node]);
    for (auto &child : adj[node])
        if (child != par)
            dfs(child, node, lvl + 1, ch++);
}

void solveCase(int caseNo)
{
    cin >> n >> q;
    global.init(n + 1);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1, 1, 0, 1);
    db("begin");
    for (int i = 1; i <= n; ++i)
        if (depth[i])
        {
            db(i, depth[i]);
            bit[i].init(depth[i]);
        }
    db("end");
    while (q--)
    {
        int type;
        cin >> type;
        db(type);
        if (type == 0)
        {
            int v, d, x;
            cin >> v >> x >> d;
            db(v, d, x);
            if (v == 1)
            {
                root += x;
                global.update(1, x);
                global.update(d + 1, -x);
                continue;
            }
            int cNo = chain[v];
            int lvl = level[v];
            int lo = lvl - d;
            int hi = lvl + d;
            db(lo, hi, cNo, lvl);
            if (lo <= 0)
            {
                root += x;
                lvl = abs(lo);
                if (lvl > 0)
                {
                    global.update(1, x);
                    global.update(lvl + 1, -x);
                    bit[cNo].update(1, -x);
                    if (lvl + 1 <= depth[cNo])
                        bit[cNo].update(lvl + 1, x);
                }
            }
            bit[cNo].update(max(1, lo), x);
            if (hi < depth[cNo])
                bit[cNo].update(hi + 1, -x);
        }
        else
        {
            int v;
            cin >> v;
            db(v);
            if (v == 1)
                cout << root << '\n';
            else
            {
                int cNo = chain[v];
                int lvl = level[v];
                db(cNo, lvl);
                long long ans = global.pref(lvl) + bit[cNo].pref(lvl);
                cout << ans << '\n';
            }
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