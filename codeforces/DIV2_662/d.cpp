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

const int NAX = 2e3 + 5, MOD = 1000000007;

int n, m;
string vec[NAX];
ll res = 0;
int mat[NAX][NAX];
// int col[NAX][NAX];
// int row[NAX][NAX];
int N[NAX][NAX];
int E[NAX][NAX];
int W[NAX][NAX];
int S[NAX][NAX];

void solve()
{
    for (size_t i = 1; i <= n; i++)
        for (size_t j = 1; j <= m; j++)
            N[i][j] = E[i][j] = W[i][j] = S[i][j] = 1;
    for (int i = 1; i <= n; i++)
    {
        int len = 1;
        char prev = '\0';
        for (size_t j = 1; j <= m; j++)
        {
            if (vec[i - 1][j - 1] == prev)
                len++;
            else
                len = 1;
            if (i - 2 >= 0 && vec[i - 2][j - 1] == vec[i - 1][j - 1])
                N[i][j] = min(N[i - 1][j] + 1, len);
            prev = vec[i - 1][j - 1];
        }
    }
    for (int i = n; i >= 1; i--)
    {
        int len = 1;
        char prev = '\0';
        for (size_t j = 1; j <= m; j++)
        {
            if (vec[i - 1][j - 1] == prev)
                len++;
            else
                len = 1;
            if (i + 1 <= n && vec[i][j - 1] == vec[i - 1][j - 1])
                E[i][j] = min(E[i + 1][j] + 1, len);
            prev = vec[i - 1][j - 1];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int len = 1;
        char prev = '\0';
        for (int j = m; j >= 1; j--)
        {
            if (vec[i - 1][j - 1] == prev)
                len++;
            else
                len = 1;
            if (i - 2 >= 0 && vec[i - 2][j - 1] == vec[i - 1][j - 1])
                W[i][j] = min(W[i - 1][j] + 1, len);
            prev = vec[i - 1][j - 1];
        }
    }
    for (int i = n; i >= 1; i--)
    {
        int len = 1;
        char prev = '\0';
        for (int j = m; j >= 1; j--)
        {
            if (vec[i - 1][j - 1] == prev)
                len++;
            else
                len = 1;
            if (i + 1 <= n && vec[i][j - 1] == vec[i - 1][j - 1])
                S[i][j] = min(S[i + 1][j] + 1, len);
            prev = vec[i - 1][j - 1];
        }
    }
    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            int temp = min({N[i][j], E[i][j], W[i][j], S[i][j]});
            // db(i, j, temp, N[i][j], E[i][j], W[i][j], S[i][j]);
            res += temp;
            // cout << temp << ' ';
        }
        // cout << '\n';
    }
}

struct Solution
{
    Solution() {}
    void solveCase()
    {
        cin >> n >> m;
        for (size_t i = 0; i < n; i++)
            cin >> vec[i];
        solve();
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