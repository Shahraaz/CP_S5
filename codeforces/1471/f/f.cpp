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

void solveCase()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> degree(n);
    UnionFind U(n);
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
        degree[u]++;
        degree[v]++;
        U.unionSet(u, v);
    }
    if (U.sizeOfSet(0) != n)
    {
        cout << "NO\n";
        return;
    }
    vector<int> issel(n), res;
    queue<int> Q;
    vector<int> isinres(n);
    Q.push(0);
    isinres[0] = 1;
    issel[0] = 1;
    res.pb(0);
    while (Q.size())
    {
        auto top = Q.front();
        Q.pop();
        for (auto &x : adj[top])
            if (!issel[x])
            {
                bool ok = true;
                for (auto &y : adj[x])
                    ok = ok && !isinres[y];
                if (ok)
                {
                    isinres[x] = 1;
                    res.pb(x);
                }
                issel[x] = 1;
                Q.push(x);
            }
    }
    cout << "YES\n";
    cout << res.size() << '\n';
    for (auto &x : res)
    {
        cout << x + 1 << ' ';
    }
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}