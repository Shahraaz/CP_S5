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
    // swap(n, m);
    vector<deque<int>> vecc(n, deque<int>(m));
    vector<vector<int>> res(n, vector<int>(m));
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            cin >> vecc[i][j];
    for (size_t i = 0; i < n; i++)
        sort(all(vecc[i]));
    for (size_t j = 0; j < m; j++)
    {
        int minidx = 0;
        for (size_t i = 0; i < n; i++)
            if (vecc[i].front() < vecc[minidx].front())
                minidx = i;
            else if (vecc[i].front() == vecc[minidx].front() && vecc[i].back() < vecc[minidx].back())
                minidx = i;
        for (size_t i = 0; i < n; i++)
            if (i == minidx)
            {
                res[i][j] = vecc[i].front();
                // cout << vecc[j].front() << ' ';
                vecc[i].pop_front();
            }
            else
            {
                res[i][j] = vecc[i].back();
                // cout << vecc[j].back() << ' ';
                vecc[i].pop_back();
            }
        // cout << '\n';
    }
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            cout << res[i][j] << ' ';
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