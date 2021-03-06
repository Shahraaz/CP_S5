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

const string FIRST = "First";
const string SECOND = "Second";
auto solveCase(int64_t n, int m)
{
    UnionFind U(n);
    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        U.unionSet(u, v);
    }
    auto diff = (n * (n - 1)) / 2 - m;
    if (n % 2 == 1)
    {
        if (diff % 2 == 1)
            return FIRST;
        return SECOND;
    }
    int x = U.sizeOfSet(0), y = U.sizeOfSet(n - 1);
    if (x % 2 != y % 2)
        return FIRST;
    if ((diff - x * y) % 2 == 1)
        return FIRST;
    return SECOND;
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main()
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    // failed to analyze input format
    // TODO: edit here
    int n;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        int n, m;
        cin >> n >> m;
        cout << solveCase(n, m) << '\n';
    }
    return 0;
}