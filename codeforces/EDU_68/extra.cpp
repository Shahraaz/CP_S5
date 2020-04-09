// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
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
        int n, k;
        cin >> n >> k;
        // if (n == k)
        // {
        //     cout << "Alice\n";
        //     return;
        // }
        // if (n > k && k % 3 == 0)
        // {
        //     if (n % 4 == 0)
        //         cout << "Bob\n";
        //     else
        //         cout << "Alice\n";
        // }
        // else
        // {
        //     if (n % 3 == 0)
        //         cout << "Bob\n";
        //     else
        //         cout << "Alice\n";
        // }
        for (size_t k = 3; k < 20; k += 3)
        {
            vector<int> dp(20 + 1, -1);
            function<bool(int, int)> solve = [&dp, &solve](int n, int k) -> bool {
                if (n == 0)
                    return false;
                int &ret = dp[n];
                if (ret >= 0)
                    return ret;
                ret = !solve(n - 1, k);
                if (!ret && n - 2 >= 0)
                    ret = !solve(n - 2, k);
                if (!ret && n - k >= 0)
                    ret = !solve(n - k, k);
                // db(n, ret);
                return ret;
            };
            db(k);
            for (size_t n = 0; n < 20; n++)
                cout << '(' << n << ' ' << (solve(n, k) ? "W)" : "L)") << ' ';
            cout << '\n';
        }

        // if (solve(n, k))
        //     cout << "Alice\n";
        // else
        //     cout << "Bob\n";
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