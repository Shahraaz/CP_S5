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

int abcd[10][10][10 * 10 * 10 * 10];
void Solution::solveCase()
{
    vector<vector<string>> str(50, vector<string>(8));
    for (size_t i = 0; i < 8; i++)
        cin >> str[0][i];
    for (size_t i = 1; i < 50; i++)
    {
        for (size_t j = 0; j < 8; j++)
            str[i][0].push_back('.');
        for (size_t j = 1; j < 8; j++)
        {
            str[i][j] = str[i - 1][j - 1];
        }
        if (i < 8)
            db(str[i]);
    }
    queue<pair<pair<int, int>, int>> Q;
    Q.push({{7, 0}, 0});
    abcd[7][0][0] = 1;
    int a[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int b[] = {1, -1, 0, 0, 1, 1, -1, -1};
    auto check = [&](int x, int y, int time) -> int {
        if (time >= 50)
            return true;
        if (0 <= x && x < 8 && 0 <= y && y < 8)
            if (str[time][x][y] == 'S' || str[time - 1][x][y] == 'S')
                return false;
        return true;
    };
    while (Q.size())
    {
        auto top = Q.front();
        db(top);
        if (top.f.f == 0 && top.f.s == 7)
        {
            cout << "WIN\n";
            return;
        }
        Q.pop();
        if (!abcd[top.f.f][top.f.s][top.s + 1] && str[top.s + 1][top.f.f][top.f.s] != 'S')
        {
            Q.push({top.f, top.s + 1});
            abcd[top.f.f][top.f.s][top.s + 1] = 1;
        }
        for (size_t i = 0; i < 8; i++)
        {
            int x = top.f.f;
            int y = top.f.s;
            while (true)
            {
                x += a[i];
                y += b[i];
                if (0 <= x && x < 8 && 0 <= y && y < 8)
                {
                    if (str[0][x][y] == 'S')
                        break;
                    if (check(x, y, top.s + 1) && !abcd[x][y][top.s + 1])
                    {
                        abcd[x][y][top.s + 1] = 1;
                        Q.push({{x, y}, top.s + 1});
                    }
                }
                break;
            }
        }
    }
    cout << "LOSE\n";
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
