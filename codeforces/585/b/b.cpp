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
    int n, k;
    cin >> n >> k;
    vector<string> tunnel(3);
    vector<vector<int>> trains(26), possible(3, vector<int>(n + 1));
    pair<int, int> curr;
    for (int i = 0; i < 3; i++)
    {
        cin >> tunnel[i];
        tunnel[i] += '.';
        db(i, tunnel[i]);
        int prevchar = -1;
        int previdx = -1;
        for (int j = 0; j < n + 1; j++)
        {
            if (tunnel[i][j] == 's')
                possible[i][j] = 1;

            if (prevchar != tunnel[i][j])
            {
                if ('A' <= prevchar && prevchar <= 'Z')
                {
                    trains[prevchar - 'A'] = {i, previdx, j - 1};
                    db(char(prevchar), trains[prevchar - 'A']);
                }
                prevchar = tunnel[i][j];
                previdx = j;
            }
        }
    }
    auto issoke = [&](int i, int j, int tq) -> int {
        for (size_t k = 0; k < 26; k++)
        {
            if (trains[k].empty())
                continue;
            int x = trains[k][0];
            int y1 = trains[k][1] - 2 * tq;
            int y2 = trains[k][2] - 2 * tq + 2;
            if (x == i)
                if (y1 <= j && j <= y2)
                    return false;
        }
        return true;
    };
    for (int j = 0; j < n; ++j)
        for (int i = 0; i < 3; i++)
        {
            db(i, j, possible[i][j]);
            if (!possible[i][j])
                continue;
            for (auto i2 : {i - 1, i, i + 1})
            {
                if (0 <= i2 && i2 < 3 && issoke(i, j + 1, j) && issoke(i2, j + 1, j + 1))
                    possible[i2][j + 1] = 1;
            }
        }
    if (possible[0][n] || possible[1][n] || possible[2][n])
        cout << "YES\n";
    else
        cout << "NO\n";
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