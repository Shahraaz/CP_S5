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

int n, k;
char grid[2001][2001];
int cost_to_reach[2001][2001];

void solveCase()
{
    n = 2000, k = 1;
    cin >> n >> k;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
            grid[i][j] = 'a';

        cin >> grid[i];
    }
    for (size_t i = 0; i <= n; i++)
        for (size_t j = 0; j <= n; j++)
            cost_to_reach[i][j] = 2 * k + 1;
    if (grid[0][0] == 'a')
        cost_to_reach[0][0] = 0;
    else
        cost_to_reach[0][0] = 1;
    int dist = 0;
    vector<pair<int, int>> srces;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i + 1 < n)
                cost_to_reach[i + 1][j] = min(cost_to_reach[i + 1][j], cost_to_reach[i][j] + (grid[i + 1][j] != 'a'));
            if (j + 1 < n)
                cost_to_reach[i][j + 1] = min(cost_to_reach[i][j + 1], cost_to_reach[i][j] + (grid[i][j + 1] != 'a'));
            if (cost_to_reach[i][j] <= k)
            {
                int d = i + j;
                if (d == dist)
                {
                    srces.pb({i, j});
                }
                else if (d > dist)
                {
                    dist = d;
                    srces.clear();
                    srces.pb({i, j});
                }
            }
        }
    }
    db(dist);
    db(srces);
    string str;
    if (srces.empty())
    {
        str += grid[0][0];
        srces.pb({0, 0});
    }
    else
    {
        for (size_t i = 0; i <= dist; i++)
            str += 'a';
    }
    while (srces.size())
    {
        db(srces);
        // assert(srces.size());
        if (srces.size() == 1 && srces[0].first >= (n - 1) && srces[0].second >= (n - 1))
            break;
        vector<vector<pair<int, int>>> nnext(26);
        for (auto &x : srces)
        {
            if (x.first + 1 < n)
                nnext[grid[x.first + 1][x.second] - 'a'].pb({x.first + 1, x.second});
            if (x.second + 1 < n)
                nnext[grid[x.first][x.second + 1] - 'a'].pb({x.first, x.second + 1});
        }
        db(nnext);
        srces.clear();
        for (size_t i = 0; i < 26; i++)
        {
            if (nnext[i].size())
            {
                str += char('a' + i);
                srces = nnext[i];
                sort(all(srces));
                srces.erase(unique(all(srces)), srces.end());
                break;
            }
        }
    }
    cout << str << '\n';
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