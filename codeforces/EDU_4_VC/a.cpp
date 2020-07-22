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
    set<pair<int, string>> ss;
    int n, p, q;
    string s;
    int dp[101];
    int dfs(int pos, int n)
    {
        if (pos > n)
            return false;
        if (pos == n)
            return true;
        if (dp[pos] >= 0)
            return dp[pos];
        int ret = 0;
        if (dfs(pos + p, n))
        {
            ss.insert({pos, s.substr(pos, p)});
            ret = 1;
        }
        if (dfs(pos + q, n))
        {
            ss.insert({pos, s.substr(pos, q)});
            ret = 1;
        }
        db(pos, ret);
        return dp[pos] = ret;
    }
    Solution() {}
    void solveCase()
    {
        cin >> n >> p >> q >> s;
        memset(dp, -1, sizeof dp);
        if (dfs(0, n))
        {
            db(ss);
            vector<string> toPrint;
            int curr = 0;
            while (curr < n)
            {
                if (dfs(curr + p, n))
                {
                    toPrint.pb(s.substr(curr, p));
                    curr += p;
                }
                else
                {
                    toPrint.pb(s.substr(curr, q));
                    curr += q;
                }
            }
            cout << toPrint.size() << '\n';
            for (auto &x : toPrint)
            {
                cout << x << '\n';
            }
            cout << '\n';
        }
        else
        {
            cout << "-1\n";
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
