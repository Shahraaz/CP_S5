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

int n;
int c[30];
int s[1 << 13];
char dp[13][1 << 13][25];

class Solution
{
private:
    char f(int pos, int mask, int leaves)
    {
        if (c[pos] == 1)
            return leaves == 0;
        if ((mask >> pos) & 1)
            return 0;
        char &res = dp[pos][mask][leaves];
        if (res != -1)
            return res;
        res = 0;
        for (int nmask = mask;; nmask = (nmask - 1) & mask)
        {
            int tmp = __builtin_popcount(nmask);
            if (s[nmask] <= c[pos] - 1)
            {
                int take = c[pos] - 1 - s[nmask];
                if (take <= leaves && take + tmp > 1)
                {
                    char cres = f(pos + 1, mask ^ nmask, leaves - take);
                    res |= cres;
                }
            }
            if (nmask == 0)
                break;
        }
        return res;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        int leaves = 0;
        bool bad = false;
        for (size_t i = 0; i < n; i++)
        {
            cin >> c[i];
            leaves += c[i] == 1;
            bad |= c[i] == 2;
        }
        if (n == 1)
        {
            if (c[0] == 1)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
        else
        {
            int inner = n - leaves;
            if (2 * leaves <= n || bad)
            {
                cout << "NO\n";
            }
            else
            {
                sort(c, c + n);
                reverse(c, c + n);
                memset(dp, -1, sizeof dp);
                for (size_t mask = 0; mask < (1 << inner); mask++)
                {
                    s[mask] = 0;
                    for (size_t i = 0; i < inner; i++)
                        if ((mask >> i) & 1)
                            s[mask] += c[i];
                }
                if (f(0, ((1 << inner) - 1) ^ 1, leaves))
                    cout << "YES\n";
                else
                    cout << "NO\n";
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
