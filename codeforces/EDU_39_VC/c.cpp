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

const int NAX = 1e5 + 5, MOD = 1000000007;

int dp[26][NAX];
string s;
string target = "abcdefghijklmnopqrstuvwxyz";
string backup;

int solve(int chIdx, int idx)
{
    if (chIdx == 26)
        return true;
    if (idx == s.length())
        return false;
    auto &ret = dp[chIdx][idx];
    if (ret >= 0)
        return ret;
    ret = false;
    ret = solve(chIdx, idx + 1);
    if (!ret)
        if (s[idx] <= target[chIdx])
        {
            s[idx] = target[chIdx];
            ret = solve(chIdx + 1, idx + 1);
            if (!ret)
                s[idx] = backup[idx];
        }
    return ret;
}

void solveCase()
{
    cin >> s;
    backup = s;
    memset(dp, -1, sizeof dp);
    if (solve(0, 0))
        cout << s << '\n';
    else
        cout << -1 << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
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
