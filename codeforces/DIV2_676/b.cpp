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

void solveCase()
{
    int n;
    cin >> n;
    vector<string> grid(n);
    for (auto &x : grid)
        cin >> x;
    int a[] = {0, 0, 1, -1};
    int b[] = {1, -1, 0, 0};
    auto check = [&]() -> bool {
        vector<vector<int>> vis(n, vector<int>(n));
        queue<pair<int, int>> Q;
        Q.push({0, 0});
        vis[0][0] = 1;
        while (Q.size())
        {
            auto top = Q.front();
            if (top.f == (n - 1) && (top.s) == (n - 1))
                return true;
            Q.pop();
            for (size_t i = 0; i < 4; i++)
            {
                int x = top.f + a[i];
                int y = top.s + b[i];
                if (0 <= x && x < n && 0 <= y && y < n)
                    if (!vis[x][y] && grid[x][y] != '1')
                    {
                        vis[x][y] = 1;
                        Q.push({x, y});
                    }
            }
        }
        vis = vector<vector<int>>(n, vector<int>(n));
        Q.push({0, 0});
        vis[0][0] = 1;
        while (Q.size())
        {
            auto top = Q.front();
            if (top.f == (n - 1) && (top.s) == (n - 1))
                return true;
            Q.pop();
            for (size_t i = 0; i < 4; i++)
            {
                int x = top.f + a[i];
                int y = top.s + b[i];
                if (0 <= x && x < n && 0 <= y && y < n)
                    if (!vis[x][y] && grid[x][y] != '0')
                    {
                        vis[x][y] = 1;
                        Q.push({x, y});
                    }
            }
        }
        return false;
    };
    vector<pair<int, int>> vecc;
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
        {
            if (i == 0 && j == 0)
                continue;
            vecc.pb({i, j});
        }
    if (!check())
    {
        cout << 0 << '\n';
        return;
    }
    for (auto &x : vecc)
    {
        grid[x.f][x.s] = '1' - grid[x.f][x.s] + '0';
        if (!check())
        {
            cout << 1 << '\n';
            cout << x.f + 1 << ' ' << x.s + 1 << '\n';
            return;
        }
        for (auto &y : vecc)
        {
            if (x == y)
                continue;
            grid[y.f][y.s] = '1' - grid[y.f][y.s] + '0';
            if (!check())
            {
                cout << 2 << '\n';
                cout << x.f + 1 << ' ' << x.s + 1 << '\n';
                cout << y.f + 1 << ' ' << y.s + 1 << '\n';
                return;
            }
            grid[y.f][y.s] = '1' - grid[y.f][y.s] + '0';
        }
        grid[x.f][x.s] = '1' - grid[x.f][x.s] + '0';
    }
    assert(false);
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
