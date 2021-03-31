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
    map<int, vector<int>> mp;
    int x;
    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        mp[x % m].pb(x);
    }
    int res = 0;
    for (auto &x : mp)
    {
        db(x);
        int val = x.first;
        if (x.second.empty())
            continue;
        int inv = (m - val) % m;
        db(val, inv);
        if (inv == val)
        {
            res++;
            mp[val].clear();
        }
        else
        {
            int a = mp[val].size();
            int b = mp[inv].size();
            if (a > b)
                swap(a, b);
            db(a, b);
            if (a)
            {
                int diff = min(a + 1, b);
                if (diff > 0)
                    res++;
                a = max(0, a - diff);
                b = max(0, b - diff);
            }
            res += a + b;
            db(res, a, b);
        }
        db(res);
        mp[val].clear();
        mp[inv].clear();
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