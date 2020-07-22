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

struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        UnionFind U(n * m);
        vector<string> matrix(n);
        for (auto &x : matrix)
            cin >> x;
        int a[] = {0, 0, 1, -1};
        int b[] = {1, -1, 0, 0};
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (matrix[i][j] == '.')
                    for (size_t k = 0; k < 4; k++)
                    {
                        int x = i + a[k];
                        int y = j + b[k];
                        if (0 <= x && x < n && 0 <= y && y < m)
                            if (matrix[x][y] == '.')
                                U.unionSet(i * m + j, x * m + y);
                    }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == '.')
                    cout << '.';
                else
                {
                    set<int> idices;
                    for (size_t k = 0; k < 4; k++)
                    {
                        int x = i + a[k];
                        int y = j + b[k];
                        if (0 <= x && x < n && 0 <= y && y < m)
                            if (matrix[x][y] == '.')
                                idices.insert(U.findSet(x * m + y));
                    }
                    int res = 0;
                    for (auto &x : idices)
                        res += U.sizeOfSet(x);
                    cout << (res + 1) % 10;
                }
                // cout << ' ';
            }
            cout << '\n';
        }
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
