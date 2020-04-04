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
    int d, m, lend;
    map<int, int> dp;
    int solve(int firstSetBit)
    {
        if (firstSetBit == lend)
        {
            return (d ^ (1 << lend)) + 1;
        }
        auto it = dp.find(firstSetBit);
        if (it != dp.end())
            return it->s;
        int ret = 1;
        for (size_t nextSetBit = firstSetBit + 1; nextSetBit <= lend; nextSetBit++)
            ret = (ret + solve(nextSetBit)) % m;
        return dp[firstSetBit] = ret * (1LL << firstSetBit) % m;
    }
    int len(int x)
    {
        int c = 0;
        while (x)
        {
            ++c;
            x /= 2;
        }
        return c;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> d >> m;
        // ++d;
        dp.clear();
        lend = len(d) - 1;
        db(d, lend);
        ll res = 0;
        for (size_t firstSetBit = 0; firstSetBit <= lend; firstSetBit++)
            res = (res + solve(firstSetBit)) % m;
        cout << res << '\n';
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