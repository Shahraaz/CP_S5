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

#include <bits/stdc++.h>
using namespace std;

template <typename inpType, int (*func)(int, int)>
struct sparseTree
{
    int n, logLim, def;
    vector<vector<int>> lookup;

    void buildSparseTable(inpType &arr, int n, int def)
    {
        this->n = n;
        this->def = def;
        logLim = __lg(n) + 1;
        lookup.resize(n, vector<int>(logLim, def));
        for (int i = 0; i < n; i++)
            lookup[i][0] = arr[i];
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 0; (i + (1 << j) - 1) < n; i++)
                lookup[i][j] = func(lookup[i][j - 1], lookup[i + (1 << (j - 1))][j - 1]);
    }

    int query(int L, int R)
    {
        if (L < 0 || L > n - 1 || R < 0 || R > n - 1 || L > R)
            return def;
        int j = __lg(R - L + 1);
        return func(lookup[L][j], lookup[R - (1 << j) + 1][j]);
    }
};

int min(int a, int b)
{
    return std::min(a, b);
}
int max(int a, int b)
{
    return std::max(a, b);
}

int gcd(int a, int b)
{
    return __gcd(a, b);
}

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
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    vector<pair<int, int>> vecc;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        vecc.pb({a[i], i});
    }
    sort(all(vecc));
    sparseTree<vector<int>, gcd> gcd_tree;
    gcd_tree.buildSparseTable(a, n, MOD);

    UnionFind u(n);
    db(n, p, a);
    long long res = 0;
    for (auto &x : vecc)
    {
        int val = x.first;
        int idx = x.second;
        if (val >= p)
            break;

        int low = idx, high = n - 1, r_idx = idx;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (gcd_tree.query(idx, mid) == val)
            {
                r_idx = mid;
                low = mid + 1;
            }
            else
                high = mid - 1;
        }

        low = 0, high = idx;
        int l_idx = idx;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (gcd_tree.query(mid, idx) == val)
            {
                l_idx = mid;
                high = mid - 1;
            }
            else
                low = mid + 1;
        }

        db(l_idx, idx, r_idx);

        int lptr = idx + 1;
        while (lptr <= r_idx)
        {
            if (u.isSameSet(idx, lptr))
                break;
            res += val;
            if (u.sizeOfSet(lptr) > 1)
            {
                u.unionSet(idx, lptr);
                break;
            }
            else
                u.unionSet(idx, lptr);
            ++lptr;
        }
        int rptr = idx - 1;
        while (l_idx <= rptr)
        {
            if (u.isSameSet(idx, rptr))
                break;
            res += val;
            if (u.sizeOfSet(rptr) > 1)
            {
                u.unionSet(idx, rptr);
                break;
            }
            else
                u.unionSet(idx, rptr);
            --rptr;
        }
    }
    db(res, u.numDisjointSets());
    res += (u.numDisjointSets() - 1) * 1LL * p;
    cout << res << '\n';
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