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
    int n;
    cin >> n;
    vector<int> res(n + 1);
    vector<int> vis(n);
    UnionFind U(n);
    int ober = false;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        --x;
        vis[x] = 1;
        for (auto next : {x - 1, x + 1})
            if (0 <= next && next < n && vis[next])
                U.unionSet(next, x);
        res[i] = i + 1;
        if (vis[n-1])
            res[i] -= U.sizeOfSet(n - 1);
    }
    res[0] = res[n] = 1;
    for (auto &x : res)
        cout << x << ' ';
    cout << '\n';
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