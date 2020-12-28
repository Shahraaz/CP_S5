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
    if (str.size() & 1)
    {
        cout << -1 << '\n';
        return;
    }
    int cnt = count(all(str), '0');
    if (cnt == 0 || cnt == str.size())
    {
        cout << -1 << '\n';
        return;
    }
    else
        cout << abs(cnt - (int)str.size() / 2) << '\n';
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