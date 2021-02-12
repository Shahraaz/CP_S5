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
    string a, b, c;
    cin >> a >> b >> c;
    for (size_t i = 0; i < a.size(); i++)
    {
        db(i, a[i], b[i], c[i]);
        if (a[i] == c[i])
            continue;
        if (b[i] == c[i])
            continue;
        cout << "NO\n";
        return;
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