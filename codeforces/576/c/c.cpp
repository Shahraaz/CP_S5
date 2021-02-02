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
const int BLOCK = 1000;

void solveCase()
{
    int n;
    cin >> n;
    vector<vector<pair<int, pair<int, int>>>> blocks(BLOCK + 1);
    for (size_t i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        blocks[x / BLOCK].pb({y, {x, i}});
    }
    bool dir = false;
    // vector<>
    for (size_t i = 0; i <= BLOCK; i++)
    {
        if (blocks[i].empty())
            continue;
        if (dir)
            sort(blocks[i].begin(), blocks[i].end());
        else
            sort(blocks[i].rbegin(), blocks[i].rend());
        dir = !dir;
        for (auto &x : blocks[i])
            cout << x.second.second + 1 << ' ';
    }
    cout << "\n";
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