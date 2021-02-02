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

const int LIM = 6;
ll cache[LIM + 1][LIM + 1];

// vector<pair<int, int>> dirs = {{1, -2}, {2, -1}, {3, 0}, {1, 2}, {2, 1}, {0, 3}};

// ll brute_force(int a, int b)
// {
//     if (a <= 0 || b <= 0 || a > LIM || b > LIM)
//         return 0;
//     // assert(a <= LIM && b <= LIM);
//     ll &ret = cache[a][b];
//     // db(a, b, ret);
//     if (ret != -1)
//         return ret;
//     vector<vector<int>> adj(a * b);
//     // PushReLabel p(a * b + 2);
//     // db(a, b);
//     for (int i = 0; i < a; i++)
//     {
//         for (int j = 0; j < b; j++)
//         {
//             // p.addEdge(a * b, i * b + j, 1);
//             // p.addEdge(i * b + j, a * b + 1, 1);
//             for (auto dir : dirs)
//             {
//                 int x = i + dir.first;
//                 int y = j + dir.second;
//                 if (0 <= x && x < a && 0 <= y && y < b)
//                 {
//                     // db(i, j, a, b);
//                     // p.addEdge(i * b + j, x * b + y, 1);
//                     adj[i * b + j].pb(x * b + y);
//                     // [] = 1;
//                     adj[x * b + y].pb(i * b + j);
//                     // [i * b + j] = 1;
//                 }
//             }
//         }
//     }
//     vector<int> dp_mask(1 << (a * b), -1);
//     function<int(int mask)> solve = [&](int mask) -> int {
//         auto &ret = dp_mask[mask];
//         if (ret >= 0)
//             return ret;
//         ret = 0;
//         for (size_t i = 0; i < a * b; i++)
//         {
//             if (mask & (1 << i))
//                 ;
//             else
//             {
//                 for (auto &x : adj[i])
//                 {
//                     if (mask & (1 << x))
//                         ;
//                     else
//                     {
//                         ret = max(ret, 2 + solve(mask | (1 << i) | (1 << x)));
//                     }
//                 }
//             }
//         }
//         return ret;
//     };
//     ret = solve(0);
//     db(a, b, ret);
//     return ret;
// }

void solveCase()
{
    memset(cache, 0, sizeof cache);
    cache[1][4] = 2;
    cache[1][5] = 4;
    cache[1][6] = 6;

    cache[2][3] = 4;
    cache[2][4] = 8;
    cache[2][5] = 10;
    cache[2][6] = 12;

    cache[3][2] = 4;
    cache[3][3] = 8;
    cache[3][4] = 12;
    cache[3][5] = 15;
    cache[3][6] = 18;

    cache[4][1] = 2;
    cache[4][2] = 8;
    cache[4][3] = 12;
    cache[4][4] = 16;
    cache[4][5] = 20;
    cache[4][6] = 24;

    cache[5][1] = 4;
    cache[5][2] = 10;
    cache[5][3] = 14;
    cache[5][4] = 20;
    cache[5][5] = 24;

    // for (size_t i = 0; i <= LIM; i++)
    // {
    //     for (size_t j = 0; j <= LIM; j++)
    //     {
    //         brute_force(i, j);
    //     }
    // }

    int n, m;
    cin >> n >> m;

    map<pair<int, int>, ll> cache_2;

    function<ll(int, int)> solve = [&](int x, int y) -> ll {
        if (x <= 0 || y <= 0)
            return 0;
        if (x > y)
            swap(x, y);
        if (x < LIM && y < LIM)
            return cache[x][y];
        if (cache_2.count({x, y}))
            return cache_2[{x, y}];
        auto &ret = cache_2[{x, y}];
        for (size_t i = 1; i < LIM; i++)
        {
            for (size_t j = 1; j < LIM; j++)
            {
                int rowrem = x % i;
                int colrem = y % j;
                ll curr = cache[i][j] * (x / i) * (y / j);
                auto one = solve(rowrem, y) + solve(x - rowrem, colrem);
                auto two = solve(x, colrem) + solve(rowrem, y - colrem);
                ret = max(ret, curr + max(one, two));
            }
        }
        db(x, y, ret);
        return ret;
    };
    cout << solve(n, m) << '\n';
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