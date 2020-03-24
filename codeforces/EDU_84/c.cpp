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

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m, k;
        cin >> n >> m >> k;
        if (n == 1 && m == 1)
        {
            cout << "0";
            return;
        }
        vector<char> res;
        for (size_t i = 1; i < m; i++)
        {
            res.pb('L');
            // cout << "L";
        }
        for (size_t i = 1; i < n; i++)
        {
            res.pb('U');
            // cout << "L";
        }
        for (size_t i = 0; i < m; i++)
        {
            if (i & 1)
            {
                for (int i = n - 2; i >= 0; i--)
                {
                    // cout << 'U';
                    res.pb('U');
                }
            }
            else
            {
                for (size_t j = 1; j < n; j++)
                {
                    // cout << 'D';
                    res.pb('D');
                }
            }
            // cout << "R";
            if (i != m - 1)
                res.pb('R');
        }
#ifdef LOCAL
        cout << n * m * 2 << '\n';
#else

#endif
        cout << res.size() << '\n';
        for (auto &x : res)
            cout << x;
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