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
    if (k > n * n)
    {
        cout << -1 << '\n';
        return;
    }
    vector<pair<int, int>> pp;
    vector<vector<int>> mat(n, vector<int>(n));
    if (k == 3)
    {
        if (n > 1)
        {
            mat[0][0] = mat[0][1] = mat[1][0] = 1;
            k = 0;
        }
    }
    int k1 = 0;
    // if (k & 1)
    //     k--;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            if (i != j)
            {
                if (k >= 2)
                {
                    if (mat[i][j])
                        continue;
                    mat[j][i] = mat[i][j] = 1;
                    k -= 2;
                }
            }
            else
            {
                if (k >= 1)
                {
                    if (mat[i][j])
                        continue;
                    mat[j][i] = mat[i][j] = 1;
                    k -= 1;
                }
            }
    if (k || k1)
        cout << -1 << '\n';
    else
    {
        for (auto &x : mat)
        {
            for (auto &y : x)
            {
                cout << y << ' ';
            }
            cout << '\n';
        }
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
