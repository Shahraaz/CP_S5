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
    if (n == 2)
    {
        if (str[0] < str[1])
        {
            cout << "YES\n";
            cout << 2 << '\n'
                 << str[0] << ' ' << str[1] << '\n';
        }
        else
            cout << "NO\n";
        return;
    }
    cout << "YES\n";
    cout << 2 << '\n'
         << str[0] << ' ' << str.substr(1) << '\n';
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