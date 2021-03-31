#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    string str;
    cin >> str;
    int n = str.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, -1));
    function<int(int, int)> solve = [&](int pos, int is0) -> int {
        if (pos >= n)
            return 1;
        int &ret = dp[pos][is0];
        if (ret >= 0)
            return ret;
        ret = 0;
        if (is0)
            ret = solve(pos, 0);
        if (is0)
        {
            if (str[pos] == '0')
            {
                ret = max(ret, solve(pos + 1, is0));
            }
            else if (pos + 1 >= n || str[pos + 1] == '0')
            {
                ret = max(ret, solve(pos + 2, is0));
            }
        }
        else
        {
            if (str[pos] == '1')
            {
                ret = max(ret, solve(pos + 1, is0));
            }
            else if (pos + 1 >= n || str[pos + 1] == '1')
            {
                ret = max(ret, solve(pos + 2, is0));
            }
        }
        return ret;
    };
    if (solve(0, 1))
        cout << "YES\n";
    else
        cout << "NO\n";
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}