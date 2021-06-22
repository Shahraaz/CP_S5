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
    string str;
    cin >> str;
    int n = str.size();
    ll res = 0;
    vector<int> zero1(n);
    vector<int> one0(n);
    for (int i = n - 1; i >= 0; i--)
    {
        if (str[i] == '0')
        {
            if (i + 1 < n)
                zero1[i] = 1 + one0[i + 1];
            else
                zero1[i] = 1;
        }
        else if (str[i] == '1')
        {
            if (i + 1 < n)
                one0[i] = 1 + zero1[i + 1];
            else
                one0[i] = 1;
        }
        else
        {
            if (i + 1 < n)
                one0[i] = 1 + zero1[i + 1];
            else
                one0[i] = 1;

            if (i + 1 < n)
                zero1[i] = 1 + one0[i + 1];
            else
                zero1[i] = 1;
        }
        db(i, zero1[i], one0[i]);
        res += max(zero1[i], one0[i]);
    }
    cout << res << '\n';
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