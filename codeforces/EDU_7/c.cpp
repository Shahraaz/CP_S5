// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#define pc(...)
#endif

#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 1e6 + 5, MOD = 1000000007;

template <typename inpType, int (*func)(int, int)>
struct sparseTree
{
    int n, logLim, def;
    vector<vector<int>> lookup;

    void buildSparseTable(inpType arr, int n, int def)
    {
        this->n = n;
        this->def = def;
        logLim = log2(n) + 1;
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
        int j = (int)log2(R - L + 1);
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

vector<int> pos[NAX];
class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        vector<int> v(n);
        int cnt = 0;
        for (auto &x : v)
        {
            cin >> x;
            pos[x].pb(cnt++);
        }
        sparseTree<vector<int>, min> smin;
        sparseTree<vector<int>, max> smax;
        smin.buildSparseTable(v, n, MOD);
        smax.buildSparseTable(v, n, -MOD);
        pc(v);
        for (size_t i = 0; i < m; i++)
        {
            int l, r, x;
            cin >> l >> r >> x;
            --l, --r;
            int a = smin.query(l, r);
            int b = smax.query(l, r);
            db(l, r, x, a, b);
            if (a == x && b == x)
            {
                cout << -1 << '\n';
            }
            else if (a != x)
            {
                db(a);
                pc(pos[a]);
                cout << *lower_bound(all(pos[a]), l) + 1 << '\n';
            }
            else
            {
                db(b);
                pc(pos[b]);
                cout << *lower_bound(all(pos[b]), l) + 1 << '\n';
            }
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
#ifdef MULTI_TEST
    cin >> t;
#endif
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}