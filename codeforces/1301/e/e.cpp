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

string ss = "RYGB";
const int N = 510, M = 301000;
int n, m, q, cnt[6][N][N], ans[M];
int r1[M], c1[M], r2[M], c2[M];
string s;

void solveCase()
{
    cin >> n >> m >> q;
    for (size_t i = 1; i <= n; i++)
    {
        cin >> s;
        s = "$" + s;
        for (size_t j = 1; j <= m; j++)
        {
            for (size_t k = 0; k < 4; k++)
                if (s[i] == ss[k])
                    cnt[k][i][j] = 1;
        }
    }
    for (size_t k = 0; k < 4; k++)
        for (size_t i = 1; i <= n; i++)
            for (size_t j = 1; j <= m; j++)
            {
                cnt[k][i][j] += cnt[k][i - 1][j];
                cnt[k][i][j] += cnt[k][i][j - 1];
            }
    for (size_t i = 0; i < q; i++)
        cin >> r1[i] >> c1[i] >> r2[i] >> c2[i];
    auto query = [&](int k, int r1, int c1, int r2, int c2) -> int {
        return cnt[k][r2][c2] - cnt[k][r1 - 1][c2] - cnt[k][r2][c1 - 1] + cnt[k][r1 - 1][c1 - 1];
    };
    for (size_t l = 1; l < 251; l++)
    {
        if (n < 2 * l || m < 2 * l)
            break;
        for (size_t i = 1; i <= n; i++)
            for (size_t j = 1; j <= m; j++)
                cnt[4][i][j] = 0;
        for (int x = l; x <= n - l; x++)
            for (int y = l; y <= m - l; y++)
                if (query(0, x - l + 1, y - l + 1, x, y) == l * l)
                    if (query(1, x - l + 1, y + 1, x, y + l) == l * l)
                        if (query(2, x + 1, y - l + 1, x + l, y) == l * l)
                            if (query(3, x + 1, y + 1, x + l, y + l) == l * l)
                                cnt[4][x - 1 + 1][y - l + 1] = 1;
        for (int x = 1; x <= n + 1 - 2 * l; x++)
            for (int y = 1; y <= m + 1 - 2 * l; y++)
            {
                cnt[4][x][y] += cnt[4][x - 1][y];
                cnt[4][x][y] += cnt[4][x][y - 1];
            }
        for (size_t i = 0; i < q; i++)
        {
            if (r2[i] - r1[i] + 1 >= 2 * l && c2[i] - c1[i] + 1 >= 2 * l)
                if (query(4, r1[i], c1[i], r2[i] - 2 * l + 1, c2[i] - 2 * l + 1))
                    ans[i] = l;
        }
    }
    for (size_t i = 0; i < q; i++)
        cout << ans[i] * ans[i] << '\n';
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
        solveCase();
    return 0;
}