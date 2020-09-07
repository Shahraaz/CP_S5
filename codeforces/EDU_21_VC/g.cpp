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

struct Solution
{
    Solution() {}
    void solveCase();
};

int lps[NAX];
int automate_precompute[NAX][26];
vector<int> dp[NAX];

void Solution::solveCase()
{
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    for (int i = 1, j = 0; i < m;)
    {
        if (t[i] == t[j])
        {
            ++j;
            lps[i] = j;
            ++i;
        }
        else if (j != 0)
            j = lps[j - 1];
        else
            ++i;
    }
    for (size_t i = 0; i <= n; i++)
        dp[i].resize(m + 1, -MOD);
    dp[0][0] = 0;
    auto preco = [&](int pref, char curr) -> int {
        return automate_precompute[pref][curr - 'a'];
    };
    auto kmp_automata = [&](int pref, char curr) -> int {
        if (pref != 0 && t[pref] != curr)
            return preco(lps[pref - 1], curr);
        if (t[pref] == curr)
            return pref + 1;
        return 0;
    };
    for (size_t i = 0; i < m; i++)
        for (char j = 'a'; j <= 'z'; j++)
            automate_precompute[i][j - 'a'] = kmp_automata(i, j);
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (dp[i][j] != -MOD)
            {
                if (s[i] == '?')
                {
                    for (char k = 'a'; k <= 'z'; k++)
                    {
                        int temp = preco(j, k);
                        if (temp == m)
                            dp[i + 1][lps[m - 1]] = max(dp[i + 1][lps[m - 1]], dp[i][j] + 1);
                        else
                            dp[i + 1][temp] = max(dp[i + 1][temp], dp[i][j]);
                    }
                }
                else
                {
                    int temp = preco(j, s[i]);
                    if (temp == m)
                        dp[i + 1][lps[m - 1]] = max(dp[i + 1][lps[m - 1]], dp[i][j] + 1);
                    else
                        dp[i + 1][temp] = max(dp[i + 1][temp], dp[i][j]);
                }
            }
    int ans = 0;
    for (size_t j = 0; j < m; j++)
        ans = max(ans, dp[n][j]);
    cout << ans << '\n';
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
