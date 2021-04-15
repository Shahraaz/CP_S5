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
    int n, k;
    cin >> n >> k;
    if (k == 1)
    {
        cout << string(n, 'a') << '\n';
        return;
    }
    vector<char> temp;
    for (char c = 'a'; c < 'a' + k; c++)
    {
        temp.pb(c);
        for (char c2 = c + 1; c2 < 'a' + k; c2++)
        {
            temp.pb(c);
            temp.pb(c2);
        }
    }
    db(temp);
    string res;
    char c = 'a';
    int idx = 0;
    for (size_t i = 0; i < n; i++)
    {
        res += temp[i % temp.size()];
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}