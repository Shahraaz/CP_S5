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
    map<int, int> dp;
    int solve(int a, int b)
    {
        if (abs(b - a) > 20)
            return MOD;
        if (a < 0)
            return MOD;
        if (a == b)
            return 0;
        auto it = dp.find(a);
        if (it != dp.end())
            return it->s;
        dp[a] = MOD;
        dp[a] = min(dp[a], 1 + solve(a + 1, b));
        dp[a] = min(dp[a], 1 + solve(a + 2, b));
        dp[a] = min(dp[a], 1 + solve(a + 5, b));
        dp[a] = min(dp[a], 1 + solve(a - 1, b));
        dp[a] = min(dp[a], 1 + solve(a - 2, b));
        dp[a] = min(dp[a], 1 + solve(a - 5, b));
        return dp[a];
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int a, b;
        cin >> a >> b;
        int diff;
        if (a < b)
        {
            diff = b - a;
            diff /= 5;
            a += diff * 5;
        }
        else
        {
            diff = a - b;
            diff /= 5;
            a -= diff * 5;
        }
        dp.clear();
        cout << diff + solve(a, b) << '\n';
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