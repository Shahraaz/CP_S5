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
    vector<string> vecc(n);
    for (auto &x : vecc)
        cin >> x;
    vector<vector<int>> res;
    auto perform = [&](pair<int, int> start, pair<int, int> leave) {
        vector<int> ops;
        for (auto x : {start.first, start.first + 1})
            for (auto y : {start.second, start.second + 1})
            {
                if (x == leave.first && y == leave.second)
                    continue;
                vecc[x][y] = '1' + '0' - vecc[x][y];
                ops.push_back(x + 1);
                ops.push_back(y + 1);
            }
        res.pb(ops);
    };
    db("inp", vecc);
    // if (n == 2 && m == 2)
    auto pick_and_perform = [&](int x, int y, char c) {
        for (auto dx : {0, 1})
            for (auto dy : {0, 1})
                if (vecc[x + dx][y + dy] == c)
                {
                    perform({x, y}, {x + dx, y + dy});
                    return;
                }
        assert(false);
    };
    auto solveblock = [&](int x, int y) {
        vector<pair<int, int>> ones;
        for (auto dx : {0, 1})
            for (auto dy : {0, 1})
                if (vecc[x + dx][y + dy] == '1')
                    ones.pb({x + dx, y + dy});
        int i = x, j = y;
        if (ones.size() == 1)
        {
            pick_and_perform(i, j, '0');
            pick_and_perform(i, j, '1');
            pick_and_perform(i, j, '0');
        }
        else if (ones.size() == 2)
        {
            pick_and_perform(i, j, '1');
            pick_and_perform(i, j, '0');
        }
        else if (ones.size() == 3)
            pick_and_perform(i, j, '0');
        else if (ones.size() == 4)
        {
            pick_and_perform(i, j, '1');
            pick_and_perform(i, j, '0');
            pick_and_perform(i, j, '1');
            pick_and_perform(i, j, '0');
        }
    };
    for (size_t i = 0; i + 2 < n; i += 1)
    {
        for (size_t j = 0; j + 1 < m; j += 2)
        {
            if (vecc[i][j] == vecc[i][j + 1])
            {
                if (vecc[i][j] == '1')
                    perform({i, j}, {i + 1, j});
            }
            else if (vecc[i][j] == '1')
                perform({i, j}, {i, j + 1});
            else if (vecc[i][j + 1] == '1')
                perform({i, j}, {i, j});
        }
        if (m & 1)
        {
            if (vecc[i][m - 1] == '1')
                perform({i, m - 2}, {i, m - 2});
        }
        db(vecc[i], res.size());
    }
    int i = n - 2;
    for (size_t j = 0; j + 2 < m; j += 1)
    {
        if (vecc[i][j] == vecc[i + 1][j])
        {
            if (vecc[i][j] == '1')
                perform({i, j}, {i, j + 1});
        }
        else if (vecc[i][j] == '1')
            perform({i, j}, {i + 1, j});
        else if (vecc[i + 1][j] == '1')
            perform({i, j}, {i, j});
    }
    solveblock(n - 2, m - 2);
    db(vecc);
    assert(res.size() <= n * m);
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            assert(vecc[i][j] == '0');
    cout << res.size() << '\n';
    for (auto &x : res)
    {
        for (auto &y : x)
            cout << y << ' ';
        cout << '\n';
    }
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