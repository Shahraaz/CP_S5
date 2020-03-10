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

using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 5e2 + 5, MOD = 1000000007;

int a[NAX];
int toWhomCanIbeShriked[NAX][NAX];
int len[NAX][NAX];

class Solution
{
private:
    int n;
    int canBeReduced(int start, int end)
    {
        if (start < 0 || end < 0 || start > end || start > n || end > n)
            return 1;
        int &ret = toWhomCanIbeShriked[start][end];
        if (ret >= 0)
            return ret;
        if (end == start)
            return ret = a[start];
        ret = 0;
        for (int pos = start; pos <= end; pos++)
        {
            if (canBeReduced(start, pos - 1) > 0)
            {
                if (canBeReduced(start, pos - 1) == canBeReduced(pos, end))
                    return ret = canBeReduced(start, pos - 1) + 1;
            }
            if (canBeReduced(start, pos) > 0)
            {
                if (canBeReduced(start, pos) == canBeReduced(pos + 1, end))
                    return ret = canBeReduced(start, pos) + 1;
            }
            if (canBeReduced(pos + 1, end) > 0)
            {
                if (canBeReduced(start, pos) == canBeReduced(pos + 1, end))
                    return ret = canBeReduced(start, pos - 1) + 1;
            }
            if (canBeReduced(pos, end) > 0)
            {
                if (canBeReduced(start, pos - 1) == canBeReduced(pos, end))
                    return ret = canBeReduced(start, pos - 1) + 1;
            }
        }
        return ret;
    }
    int solveLen(int start, int end)
    {
        if (start < 0 || end < 0 || start > end || start > n || end > n)
            return 0;
        int &ret = len[start][end];
        if (ret >= 0)
            return ret;
        ret = 1 + solveLen(start + 1, end);
        for (int pos = start; pos <= end; pos++)
        {
            if (canBeReduced(start, pos) > 0)
                ret = min(ret, 1 + solveLen(pos + 1, end));
            if (canBeReduced(pos + 1, end) > 0)
                ret = min(ret, 1 + solveLen(start, pos));
        }
        return ret;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i + 1];
            a[i + 1]++;
        }
        memset(toWhomCanIbeShriked, -1, sizeof toWhomCanIbeShriked);
        memset(len, -1, sizeof len);
        cout << solveLen(1, n) << '\n';
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