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

#include <bits/stdc++.h>
using namespace std;

template <typename inpType, int (*func)(int, int)>
struct sparseTree
{
    int n, logLim, def;
    vector<vector<int>> lookup;

    void buildSparseTable(inpType arr, int n, int def)
    {
        this->n = n;
        this->def = def;
        logLim = __lg(n) + 1;
        lookup.resize(n, vector<int>(logLim, def));
        // pc(arr);
        for (int i = 0; i < n; i++)
        {
            lookup[i][0] = arr[i];
            // db(i, 0, lookup[i][0]);
        }
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 0; (i + (1 << j) - 1) < n; i++)
            {
                // db(lookup[i][j - 1], lookup[i + (1 << (j - 1))][j - 1]);
                lookup[i][j] = func(lookup[i][j - 1], lookup[i + (1 << (j - 1))][j - 1]);
                // db(i, j, lookup[i][j]);
            }
    }

    int query(int L, int R)
    {
        if (L < 0 || L > n - 1 || R < 0 || R > n - 1 || L > R)
            return def;
        int j = (int)__lg(R - L + 1);
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
    if (a == -1)
        return b;
    if (b == -1)
        return a;
    return __gcd(a, b);
}
void Solution::solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    sparseTree<vector<int>, gcd> stree;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    stree.buildSparseTable(a, n, -1);
    db(a);
#ifdef LOCAL
    for (size_t i = 0; i < n; i++)
        for (size_t j = i; j < n; j++)
            db(i, j, stree.query(i, j));

#endif
    map<int, ll> res;
    for (int i = n - 1; i >= 0; i--)
    {
        int curr = a[i];
        int lptr = i;
        while (lptr < n)
        {
            int low = lptr;
            int high = n - 1;
            int ans = low;
            while (low <= high)
            {
                int mid = (low + high) / 2;
                if (stree.query(i, mid) == curr)
                {
                    ans = max(ans, mid);
                    low = mid + 1;
                }
                else
                    high = mid - 1;
            }
            db(i, a[i], curr, lptr, ans);
            res[curr] += ans - lptr + 1;
            lptr = ans + 1;
            if (lptr < n)
            {
                curr = stree.query(i, lptr);
                db(i, lptr, curr);
            }
        }
    }
    int q;
    cin >> q;
    for (size_t i = 0; i < q; i++)
    {
        int x;
        cin >> x;
        cout << res[x] << '\n';
    }
}

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
