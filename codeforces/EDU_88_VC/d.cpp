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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> vecc[66];
    for (size_t i = 0; i < 66; i++)
    {
        vecc[i].pb(0);
        vecc[i].pb(n + 1);
    }
    for (size_t i = 1; i <= n; i++)
    {
        cin >> a[i];
        vecc[a[i] + 30].pb(i);
    }
    for (int i = 65 - 1; i >= 0; i--)
    {
        for (auto &x : vecc[i + 1])
            vecc[i].pb(x);
        sort(all(vecc[i]));
        vecc[i].resize(unique(all(vecc[i])) - vecc[i].begin());
    }
    vector<ll> pref(n + 2);
    for (size_t i = 1; i <= n; i++)
        pref[i] += pref[i - 1] + a[i];
    pref[0] = 0;
    pref[n + 1] = pref[n];
    sparseTree<vector<ll>, min> smin;
    sparseTree<vector<ll>, max> smax;
    smin.buildSparseTable(pref, n + 2, MOD);
    smax.buildSparseTable(pref, n + 2, -MOD);
    ll res = 0;
    db(a);
    db(pref);
    for (int i = 1; i <= n; i++)
    {
        db(a[i], i, vecc[a[i] + 31]);
        auto it = upper_bound(all(vecc[a[i] + 31]), i);
        auto r = *it;
        auto l = *prev(it);
        ll temp = 0;
        db(l, i, r);
        ll left = pref[i - 1] - smin.query(l, i - 1);
        if (left > 0)
            temp += left;
        ll right = smax.query(i + 1, r - 1) - pref[i];
        if (right > 0)
            temp += right;
        db(i, l, r, left, right);
        res = max(temp, res);
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
