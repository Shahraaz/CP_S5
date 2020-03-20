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

const int NAX = 5e2 + 5;
int MOD = 1000000007;

int dp[2][NAX][NAX];
class Solution
{
private:
    int n, m, maxBugCnt;
    int add(int a, int b)
    {
        a += b;
        if (a >= MOD)
            a -= MOD;
        return a;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n >> m >> maxBugCnt >> MOD;
        vector<int> bugPerLine(n + 1);
        for (size_t i = 0; i < n; i++)
            cin >> bugPerLine[i + 1];
        if (MOD == 1)
        {
            cout << 0 << '\n';
            return;
        }
        bool curr = 0;
        bool next = 1;
        dp[0][0][0] = 1;
        for (int idx = 0; idx <= n; idx++)
        {
            for (size_t prevLinesWritten = 0; prevLinesWritten <= m; prevLinesWritten++)
                for (int prevBugCnt = 0; prevBugCnt <= maxBugCnt; prevBugCnt++)
                    dp[next][prevLinesWritten][prevBugCnt] = 0;
            for (size_t prevLinesWritten = 0; prevLinesWritten <= m; prevLinesWritten++)
                for (int prevBugCnt = 0; prevBugCnt <= maxBugCnt; prevBugCnt++)
                {
                    if (dp[curr][prevLinesWritten][prevBugCnt] == 0)
                        continue;
                    // db(curr, prevLinesWritten, prevBugCnt, dp[curr][prevLinesWritten][prevBugCnt]);
                    dp[next][prevLinesWritten][prevBugCnt] = add(dp[next][prevLinesWritten][prevBugCnt], dp[curr][prevLinesWritten][prevBugCnt]);
                    if (idx > 0)
                        if (prevLinesWritten + 1 <= m)
                            if (prevBugCnt + bugPerLine[idx] <= maxBugCnt)
                                dp[curr][prevLinesWritten + 1][prevBugCnt + bugPerLine[idx]] = add(dp[curr][prevLinesWritten + 1][prevBugCnt + bugPerLine[idx]], dp[curr][prevLinesWritten][prevBugCnt]);
                }
            swap(curr, next);
        }
        int res = 0;
        for (int prevBugCnt = 0; prevBugCnt <= maxBugCnt; prevBugCnt++)
        {
            // res = add(res, dp[n][m][prevBugCnt]);
            res = add(res, dp[curr][m][prevBugCnt]);
        }
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