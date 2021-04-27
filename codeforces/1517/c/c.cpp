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

int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};

void solveCase()
{
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto &x : p)
        cin >> x;
    vector<vector<int>> res(n, vector<int>(n));
    auto ok = [&](int x, int y) -> bool {
        return (0 <= x && x < n && 0 <= y && y <= x);
    };
    for (int i = n - 1; i >= 0; i--)
    {
        int x = p[i];
        int cnt = x;
        function<void(int, int)> dfs = [&](int x, int y) -> void {
            if (cnt == 0)
                return;
            db(i, x, y, p[i], res[x][y]);
            assert(ok(x, y) && res[x][y] == 0);
            res[x][y] = p[i];
            cnt--;
            for (size_t k = 0; k < 4; k++)
            {
                int x1 = x + dx[k];
                int y1 = y + dy[k];
                if (ok(x1, y1) && res[x1][y1] == 0)
                    dfs(x1, y1);
            }
        };
        dfs(i, i);
    }
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j <= i; j++)
        {
            cout << res[i][j] << ' ';
        }
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}