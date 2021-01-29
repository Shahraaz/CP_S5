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
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    auto b = a;
    for (size_t i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        for (size_t j = 0; j < n; j++)
            a[i][j] = str[j] - '0';
        // cin >> a[i][j];
    }
    cin.ignore();
    for (size_t i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        for (size_t j = 0; j < n; j++)
            b[i][j] = str[j] - '0';
        // cin >> a[i][j];
    }
    // for (size_t j = 0; j < n; j++)
    //     cin >> b[i][j];
    vector<int> isColFlipped(n);
    db(a);
    db(b);
    for (size_t j = 0; j < n; j++)
        isColFlipped[j] = a[0][j] != b[0][j];
    db(isColFlipped);
    for (size_t i = 1; i < n; i++)
    {
        int pat = -1;
        for (size_t j = 0; j < n; j++)
        {
            if (isColFlipped[j])
                a[i][j] = 1 - a[i][j];
        }
        db(i);
        db(a[i]);
        db(b[i]);
        for (size_t j = 0; j < n; j++)
        {
            if (pat == -1)
                pat = a[i][j] == b[i][j];
            else if (pat != (a[i][j] == b[i][j]))
            {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
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