// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    int n, k;
    cin >> n >> k;
    string str;
    cin >> str;
    vector<vector<int>> cache(n, vector<int>(3 * k, -1));
    function<int(int, int)> solve = [&](int pos, int diff) -> int {
        if (pos == n)
            return abs(diff) == k;
        if (abs(diff) >= k)
            return 0;
        int dd = diff + k;
        auto &ret = cache[pos][dd];
        if (ret >= 0)
            return ret;
        ret = 0;
        if (str[pos] == 'W')
            ret = solve(pos + 1, diff + 1);
        else if (str[pos] == 'L')
            ret = solve(pos + 1, diff - 1);
        else if (str[pos] == 'D')
            ret = solve(pos + 1, diff);
        else
        {
            ret = solve(pos + 1, diff + 1);
            if (ret)
            {
                str[pos] = 'W';
                return ret;
            }
            ret = solve(pos + 1, diff);
            if (ret)
            {
                str[pos] = 'D';
                return ret;
            }
            ret = solve(pos + 1, diff - 1);
            if (ret)
            {
                str[pos] = 'L';
                return ret;
            }
        }
        return ret;
    };
    if (solve(0, 0))
        cout << str << '\n';
    else
    {
        cout << "NO\n";
    }
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
