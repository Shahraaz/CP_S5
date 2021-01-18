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

void solveCase()
{
    int n, m;
    cin >> n >> m;
    string str;
    cin >> str;

    int curr = 0;
    vector<int> base;
    base.pb(0);
    for (auto &x : str)
    {
        if (x == '+')
            curr++;
        else
            curr--;
        base.pb(curr);
    }

    db(n, m, str);
    db(base);
    sparseTree<vector<int>, max> maxtree;
    sparseTree<vector<int>, min> mintree;
    maxtree.buildSparseTable(base, n + 1, 0);
    mintree.buildSparseTable(base, n + 1, 0);

    for (size_t i = 0; i < m; i++)
    {
        int l, r;
        cin >> l >> r;

        auto prefmax = maxtree.query(0, l - 1);
        auto prefmin = mintree.query(0, l - 1);

        db(l, r);
        db(prefmax, prefmin);
        if (r == n)
        {
            cout << prefmax - prefmin + 1 << '\n';
            continue;
        }

        auto suffmax = maxtree.query(r + 1, n);
        auto suffmin = mintree.query(r + 1, n);

        db(suffmax, suffmin);

        auto diff = suffmax - suffmin;
        auto endptr = base[r];

        auto newsuffmax = base[l - 1] + suffmax - endptr;
        auto newsuffmin = base[l - 1] + suffmin - endptr;

        cout << max(newsuffmax, prefmax) - min(newsuffmin, prefmin) + 1 << '\n';
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
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}