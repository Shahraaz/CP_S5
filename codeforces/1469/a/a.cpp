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
        cout << "NO\n";
    else
    {
        auto i1 = find(all(str), '(') - str.begin();
        auto i2 = find(all(str), ')') - str.begin();
        if (i1 < i2)
        {
            cout << "YES\n";
        }
        else
        {
            if (i2 > 0 && i1 + 1 < str.size())
                cout << "YES\n";
            else
                cout << "NO\n";
        }
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