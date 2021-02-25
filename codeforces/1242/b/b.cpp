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
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    set<int> unvisited;
    for (size_t i = 0; i < n; i++)
        unvisited.insert(i);
    UnionFind U(n);
    vector<int> vis(n);
    for (size_t i = 0; i < n; i++)
    {
        if (vis[i])
            continue;
        queue<int> Q;
        Q.push(i);
        vis[i] = 1;
        while (Q.size())
        {
            auto top = Q.front();
            Q.pop();
            unvisited.erase(top);
            int fptr = 0;
            adj[top].pb(-1);
            sort(all(adj[top]));
            db(top, adj[top]);
            while (fptr < adj[top].size())
            {
                auto it = unvisited.upper_bound(adj[top][fptr]);
                if (it == unvisited.end())
                    break;
                db(i, *it, adj[top][fptr]);
                if (fptr + 1 == adj[top].size() || (*it < adj[top][fptr + 1]))
                {
                    db(i, *it);
                    Q.push(*it);
                    vis[*it] = 1;
                    U.unionSet(i, *it);
                    unvisited.erase(it);
                }
                else
                    ++fptr;
            }
        }
    }
    cout << U.numDisjointSets() - 1 << '\n';
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