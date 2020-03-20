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

const int NAX = 1e2 + 5, MOD = 1000000007;

int a[NAX][NAX];
int p[NAX][NAX];

class Solution
{
private:
    int n, m, k;

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n >> m >> k;
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                cin >> a[i][j];
        int ans = MOD;
        if (n <= 5 && m <= 5)
        {
            int b[5];
            for (size_t i = 0; i < m; i++)
                b[i] = a[0][i];
            for (int mask = 0; mask < (1 << m); mask++)
            {
                int r = 0;
                for (size_t i = 0; i < m; i++)
                {
                    
                }
            }
        }
        else if (n > 5)
        {
        }
        else
        {
        }
        cout << (ans <= k ? ans : -1) << '\n';
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