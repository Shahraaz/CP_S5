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
    int n, m;
    cin >> n >> m;
    vector<pair<string, string>> pals;
    set<string> cache;
    for (size_t i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        auto rev = str;
        reverse(all(rev));
        if (cache.find(rev) != cache.end())
        {
            cache.erase(rev);
            pals.pb({str, rev});
        }
        else
            cache.insert(str);
    }
    string middle;
    for (auto &x : cache)
    {
        auto rev = x;
        reverse(all(rev));
        if (x == rev)
        {
            middle = x;
            break;
        }
    }
    cout << pals.size() * 2 * m + (middle.size()) << '\n';
    for (auto &x : pals)
        cout << x.first;
    cout << middle;
    reverse(all(pals));
    for (auto &x : pals)
        cout << x.second;
    cout << '\n';
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