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
    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> b(n, vector<int>(m));
    int cnta = 0, cntb = 0;
    for (auto &x : a)
        for (auto &y : x)
        {
            cin >> y;
            cnta += y;
        }
    for (auto &x : b)
        for (auto &y : x)
        {
            cin >> y;
            cntb += y;
        }
    if (n == 1 || m == 1)
    {
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < m; j++)
            {
                if (a[i][j] != b[i][j])
                {
                    cout << "NO\n";
                    return;
                }
            }
        }
        cout << "YES\n";
        return;
    }
    db(cnta, cntb);
    for (size_t i = 0; i < n; i++)
    {
        int meowa = 0, meowb = 0;
        for (size_t j = 0; j < m; j++)
        {
            meowa += a[i][j];
            meowb += b[i][j];
        }
        if ((meowa & 1) != (meowb & 1))
        {
            cout << "NO\n";
            return;
        }
    }
    for (size_t j = 0; j < m; j++)
    {
        int meowa = 0, meowb = 0;
        for (size_t i = 0; i < n; i++)
        {
            meowa += a[i][j];
            meowb += b[i][j];
        }
        if ((meowa & 1) != (meowb & 1))
        {
            cout << "NO\n";
            return;
        }
    }
    if ((cnta & 1) == (cntb & 1))
    {
        cout << "YES\n";
    }
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}