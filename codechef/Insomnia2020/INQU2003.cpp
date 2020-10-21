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

const int NAX = 1e3 + 5, MOD = 1000000007;

string s1, s2;
int dp[NAX][NAX][4];

int solve(int p1, int p2, int idx)
{
    if (idx == 4)
        return 0;
    if (p1 == s1.size() || p2 == -1)
        return 0;
    int &ret = dp[p1][p2][idx];
    if (ret >= 0)
        return ret;
    ret = solve(p1, p2, idx + 1);
    if (idx == 0 || idx == 2)
    {
        ret = max(ret, solve(p1 + 1, p2, idx));
        ret = max(ret, solve(p1, p2 - 1, idx));
    }
    if (idx == 1)
        if (s1[p1] == s2[p2])
            ret = max(ret, 1 + solve(p1 + 1, p2 - 1, idx));
        else
            ret = max(ret, solve(p1 + 1, p2 - 1, idx + 1));
    else if (idx == 3)
        if (s1[p1] == s2[p2])
            ret = max(ret, 1 + solve(p1 + 1, p2 - 1, idx));
        else
            ret = max(ret, solve(p1 + 1, p2 - 1, idx + 1));
    return ret;
}

void solveCase()
{
    cin >> s1 >> s2;
    memset(dp, -1, sizeof dp);
    cout << 2 * solve(0, s2.size() - 1, 0) << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
