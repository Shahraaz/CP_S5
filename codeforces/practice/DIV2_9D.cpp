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

ll dp[40][40];
class Solution
{
private:
    int add(int a, int b)
    {
        a += b;
        if (a >= MOD)
            a -= MOD;
        return a;
    }
    int mul(int a, int b)
    {
        return a * b % MOD;
    }
    ll solve(int nodeCnt, int h)
    {
        if (nodeCnt < 0 || h < 0)
            return 0;
        if (h <= 1)
            return nodeCnt == h;
        ll &ret = dp[nodeCnt][h];
        if (ret >= 0)
            return ret;
        ret = 0;
        for (int rightht = 0; rightht < h; rightht++)
            for (int leftHt = 0; leftHt < h; leftHt++)
                for (size_t leftSubTreeSize = 0; leftSubTreeSize < nodeCnt; leftSubTreeSize++)
                {
                    int rightSubTreeSize = nodeCnt - leftSubTreeSize - 1;
                    if (max(leftHt, rightht) == (h - 1))
                        ret += solve(leftSubTreeSize, leftHt) * solve(rightSubTreeSize, rightht);
                }
        // ret *= 2;
        return ret;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, k;
        cin >> n >> k;
        db(n, k);
        memset(dp, -1, sizeof dp);
        ll ans = 0;
        for (size_t h = k; h <= n; h++)
            ans = ans + solve(n, h);
        cout << ans << '\n';
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