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
const int NAX = 2000 + 5, MOD = 1000000007;

string grid[NAX];
int n, m;
int ways_down[NAX][NAX];
int ways_right[NAX][NAX];
int filled_right[NAX][NAX];
int filled_down[NAX][NAX];

int vertical_rocks_inrange(int col, int r0, int r1)
{
    if (r1 < r0)
        return 0;
    return filled_down[r0][col] - filled_down[r1 + 1][col];
}

int horizontal_rocks_inrange(int row, int c0, int c1)
{
    if (c1 < c0)
        return 0;
    return filled_right[row][c0] - filled_right[row][c1 + 1];
}

void solveCase()
{
    cin >> n >> m;
    for (size_t i = 0; i < n; i++)
    {
        cin >> grid[i];
        // db(i, grid[i]);
    }
    // db("inp over");
    if (n == 1 && m == 1)
    {
        cout << 1 << '\n';
        return;
    }

    if (grid[n - 1][m - 1] == 'R')
    {
        cout << 0 << '\n';
        return;
    }

    for (int i = n - 1; i >= 0; i--)
        for (int j = m - 1; j >= 0; j--)
        {
            filled_down[i][j] = (grid[i][j] == 'R') + filled_down[i + 1][j];
            filled_right[i][j] = (grid[i][j] == 'R') + filled_right[i][j + 1];
        }
    // db("step 2 over");
    vector<deque<pair<int, int>>> row_helper(n);
    vector<int> row_dp(n);
    ways_down[n - 1][m - 1] = 1;
    ways_right[n - 1][m - 1] = 1;
    for (int j = m - 1; j >= 0; j--)
    {
        deque<pair<int, int>> col_dp;
        int col_dp_res = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            int hori_rocks = horizontal_rocks_inrange(i, j + 1, m - 1);
            int right_steps = m - j - 1 - hori_rocks;
            int vert_rocks = vertical_rocks_inrange(j, i + 1, n - 1);
            int down_steps = n - i - 1 - vert_rocks;

            // if (horizontal_rocks_inrange(i, j, m - 1) == (m - j))
            //     down_steps = 0;

            // if (vertical_rocks_inrange(j, i, n - 1) == (n - i))
            //     right_steps = 0;

            db(i, j, right_steps, down_steps, hori_rocks, vert_rocks);
            while (row_helper[i].size() && row_helper[i].back().first > (j + right_steps))
            {
                row_dp[i] -= row_helper[i].back().second;
                if (row_dp[i] < 0)
                    row_dp[i] += MOD;
                row_helper[i].pop_back();
            }
            if (right_steps)
            {
                row_helper[i].push_front({j + 1, ways_down[i][j + 1]});
                row_dp[i] += ways_down[i][j + 1];
                if (row_dp[i] >= MOD)
                    row_dp[i] -= MOD;
            }
            ways_right[i][j] += row_dp[i];
            if (ways_right[i][j] >= MOD)
                ways_right[i][j] -= MOD;
            db(ways_right[i][j], row_helper[i]);

            while (col_dp.size() && col_dp.back().first > (i + down_steps))
            {
                col_dp_res -= col_dp.back().second;
                if (col_dp_res < 0)
                    col_dp_res += MOD;
                col_dp.pop_back();
            }
            if (down_steps)
            {
                col_dp.push_front({i + 1, ways_right[i + 1][j]});
                col_dp_res += ways_right[i + 1][j];
                if (col_dp_res >= MOD)
                    col_dp_res -= MOD;
            }
            ways_down[i][j] += col_dp_res;
            if (ways_down[i][j] >= MOD)
                ways_down[i][j] -= MOD;

            db(ways_down[i][j], col_dp, '\n');
        }
    }
    int res = ways_down[0][0];
    res += ways_right[0][0];
    if (res >= MOD)
        res -= MOD;
    cout << res << '\n';
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