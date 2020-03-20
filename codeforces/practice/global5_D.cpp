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

const int NAX = 2e5 + 5, MOD = 1000000007;

template <typename inpType, ll (*func)(ll, ll)>
struct sparseTree
{
    int n, logLim;
    ll def;
    vector<vector<ll>> lookup;

    void buildSparseTable(inpType arr, int n, ll def)
    {
        this->n = n;
        this->def = def;
        logLim = log2(n) + 1;
        lookup.resize(n, vector<ll>(logLim, def));
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

    ll query(int L, int R)
    {
        if (L < 0 || L > n - 1 || R < 0 || R > n - 1 || L > R)
            return def;
        int j = (int)log2(R - L + 1);
        return func(lookup[L][j], lookup[R - (1 << j) + 1][j]);
    }
};

ll miin(ll a, ll b)
{
    return std::min(a, b);
}
int max(int a, int b)
{
    return std::max(a, b);
}

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        vector<int> v(4 * n + 5);
        vector<int> dp(4 * n + 5);
        for (size_t i = 0; i < n; i++)
        {
            cin >> v[i];
            v[3 * n + i] = v[n + i] = v[2 * n + i] = v[i];
        }
        sparseTree<vector<int>, miin> S;

        S.buildSparseTable(v, v.size(), 0LL);
        pc(v);
        dp[4 * n - 1] = 4 * n - 1;
        for (int i = 4 * n - 2; i >= 0; i--)
        {
            // dp[i] = i;
            int l = i, r = dp[i + 1], ans = i;
            while (l <= r)
            {
                int mid = (l + r) / 2;
                db(i, mid, v[i], S.query(i, mid));
                if (v[i] <= 2 * S.query(i, mid))
                {
                    ans = max(ans, mid);
                    l = mid + 1;
                }
                else
                    r = mid - 1;
            }
            dp[i] = min(dp[i + 1], ans);
            db(i, dp[i]);
        }
        for (size_t i = 0; i < n; i++)
        {
            if (dp[i] >= 3 * n)
                cout << -1 << ' ';
            else
                cout << dp[i] - i + 1 << ' ';
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