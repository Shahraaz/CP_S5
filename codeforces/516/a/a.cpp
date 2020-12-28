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

ll Fact[10];

void solveCase()
{
    Fact[0] = 0;
    for (size_t i = 1; i < 10; i++)
        Fact[i] = i * Fact[i - 1];
    string str;
    int n;
    cin >> n;
    cin >> str;
    string res;
    map<int, vector<int>> mp;
    mp[4] = {2, 2, 3};
    mp[6] = {3, 5};
    mp[8] = {2, 2, 2, 7};
    mp[9] = {2, 3, 3, 7};
    for (auto &x : str)
    {
        db(x, mp[x]);
        if (mp[x - '0'].size())
        {
            for (auto &y : mp[x - '0'])
            {
                res += '0' + y;
            }
        }
        else
        {
            if (x != '1' && x != '0')
                res += x;
        }
    }
    sort(all(res));
    reverse(all(res));
    for (auto &x : res)
    {
        cout << x;
    }
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