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

const int NAX = 5e3 + 5, MOD = 1000000007;

int h[NAX], n, S[NAX];
int dp[NAX][NAX];
int val[NAX];
int perm[NAX];

int cmp(int a, int b)
{
    return val[a] < val[b];
}

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n;
        for (size_t i = 0; i < n; i++)
            cin >> h[i];
        partial_sum(h, h + n, S);
        for (size_t i = 0; i <= n; i++)
            for (size_t j = 0; j <= n; j++)
                dp[i][j] = MOD;
        for (size_t i = 0; i < n; i++)
            dp[1][i] = S[i];
        for (size_t k = 2; k <= n; k++)
        {
            int cnt = 0;
            for (size_t j = 0; j < n; j++)
                if (dp[k - 1][j] < MOD)
                {
                    val[j] = dp[k - 1][j] + S[j];
                    perm[cnt++] = j;
                }
            sort(perm, perm + cnt, cmp);
            int at = 0, mx = -1;
            for (size_t j = 0; j < n; j++)
            {
                while (at < cnt && val[perm[at]] <= S[j])
                {
                    mx = max(mx, perm[at]);
                    ++at;
                }
                if (mx == -1)
                    dp[k][j] = MOD;
                else
                    dp[k][j] = S[j] - S[mx];
                // db(k,j,dp[k][])
            }
            if (dp[k][n - 1] >= MOD)
                break;
        }
        for (int i = n; i >= 0; i--)
        {
            if (dp[i][n - 1] < MOD)
            {
                cout << n - i << '\n';
                return;
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