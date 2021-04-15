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
    auto cnt = count(all(str), 'a');
    if (cnt == str.size())
    {
        cout << "NO\n";
        return;
    }
    auto str2 = str;
    str2 = "a" + str2;
    auto strrev = str2;
    reverse(all(strrev));
    if (str2 != strrev)
    {
        cout << "YES\n"
             << str2 << '\n';
        return;
    }
    str2 = str;
    str2 = str2 + "a";
    strrev = str2;
    reverse(all(strrev));
    if (str2 != strrev)
    {
        cout << "YES\n"
             << str2 << '\n';
        return;
    }
    assert(false);
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