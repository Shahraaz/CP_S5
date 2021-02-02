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
    string str;
    cin >> str;
    vector<vector<int>> left(2, vector<int>(n + 1)), right(2, vector<int>(n + 1));
    for (size_t i = 0; i <= n; i++)
    {
        left[0][i] = left[1][i] = i;
        right[0][i] = right[1][i] = i;
    }
    db(n, str);
    for (int i = 0; i <= n; i++)
    {
        if (i - 1 >= 0)
        {
            if (str[i - 1] == 'L')
            {
                left[0][i] = left[1][i - 1];
            }
            else
            {
                left[1][i] = left[0][i - 1];
            }
        }
        db(i, left[0][i], left[1][i]);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (str[i] == 'R')
            right[0][i] = right[1][i + 1];
        else
            right[1][i] = right[0][i + 1];
        db(i, right[0][i], right[1][i]);
    }
    for (size_t i = 0; i <= n; i++)
    {
        cout << right[0][i] - left[0][i] + 1 << ' ';
    }
    cout << '\n';
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