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

// int dp[NAX];
class Solution
{
private:
    int a, b, n;
    vector<int> X;

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n;
        X.resize(n);
        for (auto &x : X)
            cin >> x;
        cin >> a >> b;
        sort(all(X));
        X.erase(unique(all(X)), X.end());
        // for (int i = 0; i < NAX; i++)
        // {
        //     dp[i] = MOD;
        // }
        // dp[b] = 0;
        // for (int x = b + 1; x <= a; x++)
        // {
        //     dp[x] = min(dp[x], dp[x - 1] + 1);
        //     for (auto &elem : X)
        //     {
        //         dp[x] = min(dp[x], 1 + dp[x - x % elem]);
        //     }
        //     db(x, dp[x]);
        // }
        int cnt = 0;
        while (a != b)
        {
            int a1 = a - 1;
            for (int i = X.size() - 1; i >= 0; i--)
            {
                int cur = a - a % X[i];
                db(i, a, a1, X[i], cur);
                if (cur >= b && cur < a1)
                    a1 = cur;
            }
            db(a1, cnt);
            while (!X.empty() && a - a % X.back() < b)
                X.pop_back();
            swap(a, a1);
            ++cnt;
        }
        cout << cnt << '\n';
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