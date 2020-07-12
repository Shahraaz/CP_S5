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

class UnionFind
{ // OOP style
private:
    vector<int> p, rank, setSize; // remember: vi is vector<int>
    int numSets;

public:
    UnionFind(int N)
    {
        setSize.assign(N, 1);
        numSets = N;
        rank.assign(N, 0);
        p.assign(N, 0);
        for (int i = 0; i < N; i++)
            p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    bool unionSet(int i, int j)
    {
        if (!isSameSet(i, j))
        {
            numSets--;
            int x = findSet(i), y = findSet(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y])
            {
                p[y] = x;
                setSize[x] += setSize[y];
            }
            else
            {
                p[x] = y;
                setSize[y] += setSize[x];
                if (rank[x] == rank[y])
                    rank[y]++;
            }
            return true;
        }
        return false;
    }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

vector<pair<int, int>> adj[NAX];
pair<pair<int, int>, pair<int, int>> edges[NAX];
bool isGood[NAX];

const int MAXB = 20;
int level[NAX];
int par[NAX][MAXB];
int maxWt[NAX][MAXB];
int w[NAX];

void dfs(int node, int par, int prevWt)
{
    ::par[node][0] = par == -1 ? node : par;
    level[node] = par == -1 ? 0 : level[par] + 1;
    maxWt[node][0] = prevWt;
    for (size_t i = 1; i < MAXB; i++)
    {
        ::par[node][i] = ::par[::par[node][i - 1]][i - 1];
        maxWt[node][i] = max(maxWt[node][i - 1], maxWt[::par[node][i - 1]][i - 1]);
    }
    for (auto &x : adj[node])
        if (isGood[x.s] && x.f != par)
            dfs(x.f, node, w[x.s]);
}

int get(int a, int b)
{
    if (level[a] < level[b])
        swap(a, b);
    int ret = 0;
    for (int bit = MAXB - 1; bit >= 0; bit--)
        if (level[par[a][bit]] >= level[b])
        {
            ret = max(ret, maxWt[a][bit]);
            a = par[a][bit];
        }
    if (a == b)
        return ret;
    for (int bit = MAXB - 1; bit >= 0; bit--)
        if (par[a][bit] != par[b][bit])
        {
            ret = max({ret, maxWt[a][bit], maxWt[b][bit]});
            a = par[a][bit];
            b = par[b][bit];
        }
    return max({ret, maxWt[a][0], maxWt[b][0]});
}

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        for (size_t i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            --u, --v;
            ::w[i] = w;
            adj[u].pb({v, i});
            adj[v].pb({u, i});
            edges[i] = {{w, i}, {u, v}};
        }
        sort(edges, edges + m);
        UnionFind U(n);
        ll res = 0;
        for (size_t i = 0; i < m; i++)
            if (U.unionSet(edges[i].s.f, edges[i].s.s))
            {
                res += edges[i].f.f;
                isGood[edges[i].f.s] = true;
            }
        dfs(0, -1, 0);
        vector<ll> ret(m);
        for (size_t i = 0; i < m; i++)
            if (isGood[edges[i].f.s])
                ret[edges[i].f.s] = res;
            else
                ret[edges[i].f.s] = res - get(edges[i].s.f, edges[i].s.s) + edges[i].f.f;
        for (size_t i = 0; i < m; i++)
            cout << ret[i] << '\n';
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
