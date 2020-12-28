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
    int n, m;
    cin >> n >> m;
    vector<string> matrix(n);
    for (auto &x : matrix)
        cin >> x;
    db(n, m, matrix);
    vector<vector<int>> res(n, vector<int>(m));
    ll ret = 0;
    for (int i = n - 1; i >= 0; i--)
        for (int j = m - 1; j >= 0; j--)
        {
            if (matrix[i][j] == '.')
                continue;
            int i1 = i + 1, j1 = j;
            int temp = INT_MAX, ok = 0;
            if (0 <= i1 && i1 < n && 0 <= j1 && j1 < m)
            {
                temp = min(temp, res[i1][j1]);
                ok++;
            }
            i1 = i + 1, j1 = j + 1;
            if (0 <= i1 && i1 < n && 0 <= j1 && j1 < m)
            {
                temp = min(temp, res[i1][j1]);
                ok++;
            }
            i1 = i + 1, j1 = j - 1;
            if (0 <= i1 && i1 < n && 0 <= j1 && j1 < m)
            {
                temp = min(temp, res[i1][j1]);
                ok++;
            }
            if (ok != 3)
                temp = 1;
            else
                temp++;
            res[i][j] = temp;
            db(i, j, temp);
            ret += temp;
        }
    cout << ret << '\n';
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