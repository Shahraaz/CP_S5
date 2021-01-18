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
    map<pair<char, char>, int> mp;
    for (size_t i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        map<char, int> cnt;
        for (auto &x : str)
            cnt[x]++;
        if (cnt.size() == 1)
        {
            auto x = (cnt.begin())->first;
            for (char c = 'a'; c <= 'z'; c++)
            {
                mp[{x, c}] += str.size();
                if (x != c)
                    mp[{c, x}] += str.size();
            }
        }
        else if (cnt.size() == 2)
        {
            auto x = (cnt.begin())->first;
            auto y = (++cnt.begin())->first;
            mp[{x, y}] += str.size();
            mp[{y, x}] += str.size();
        }
    }
    int res = 0;
    for (auto &x : mp)
        res = max(res, x.second);
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