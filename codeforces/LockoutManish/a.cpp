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

struct Solution
{
    Solution() {}
    void solveCase();
};

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

void Solution::solveCase()
{
    int n;
    cin >> n;
    vector<int> ranges;
    vector<pair<int, int>> vecc;
    for (size_t i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        vecc.pb({x, y});
        ranges.pb(x);
        ranges.pb(y);
    }
    sort(all(ranges));
    ranges.erase(unique(all(ranges)), ranges.end());
    UnionFind U(ranges.size());
    vector<int> degree(ranges.size());
    for (size_t i = 0; i < n; i++)
    {
        vecc[i].f = lower_bound(all(ranges), vecc[i].f) - ranges.begin();
        vecc[i].s = lower_bound(all(ranges), vecc[i].s) - ranges.begin();
        U.unionSet(vecc[i].f, vecc[i].s);
        degree[vecc[i].f]++;
        degree[vecc[i].s]++;
    }
    db(vecc);
    db(ranges);
    db(degree);
    vector<vector<int>> oddDegreeCompent(ranges.size());
    set<int> disjSets;
    for (size_t i = 0; i < n; i++)
    {
        disjSets.insert(U.findSet(vecc[i].f));
        oddDegreeCompent[U.findSet(vecc[i].f)].pb(i);
    }
    // cout << U.numDisjointSets() - 1 << '\n';
    vector<int> representatives;
    db(disjSets);
    for (auto &x : disjSets)
        representatives.pb(x);
    cout << representatives.size() - 1 << '\n';
    for (int i = 1; i < representatives.size(); i++)
    {
        vector<int> a = {MOD};
        for (auto &x : oddDegreeCompent[representatives[i]])
        {
            int edgeIdx = x;
            a = min(a, {degree[vecc[edgeIdx].f], vecc[edgeIdx].f, edgeIdx});
            a = min(a, {degree[vecc[edgeIdx].s], vecc[edgeIdx].s, edgeIdx});
        }
        int u = vecc[oddDegreeCompent[representatives[0]][0]].f;
        cout << a[2] + 1 << ' ' << ranges[a[1]] << ' ' << ranges[u] << '\n';
    }
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
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
