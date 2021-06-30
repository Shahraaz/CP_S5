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
    UnionFind U(n);
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        U.unionSet(u, v);
    }
    vector<int> mini(n, n);
    vector<int> maxi(n, -1);
    map<int, pair<int, int>> mp;
    for (int i = 0; i < n; i++)
    {
        mini[U.findSet(i)] = min(mini[U.findSet(i)], i);
        maxi[U.findSet(i)] = max(maxi[U.findSet(i)], i);
    }
    vector<pair<int, int>> intervals;
    for (int i = 0; i < n; i++)
        intervals.pb({mini[U.findSet(i)], maxi[U.findSet(i)]});
    sort(all(intervals));
    intervals.resize(unique(all(intervals)) - intervals.begin());
    db(intervals);
    int res = 0;
    for (size_t i = 0; i < intervals.size();)
    {
        int rptr = intervals[i].second;
        int j = i;
        while (j < intervals.size())
        {
            db(i, j, res, rptr, intervals[j]);
            if (rptr < intervals[j].first)
                break;
            rptr = max(rptr, intervals[j].second);
            ++j;
            ++res;
        }
        --res;
        i = j;
    }
    cout << res << '\n';
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