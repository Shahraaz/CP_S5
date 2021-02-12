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
    int n, m, k;
    cin >> n >> m >> k;
    k = min(k, m - 1);
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    int len_window = n - m + 1;
    vector<int> ok;
    for (size_t i = 0; i < n; i++)
    {
        int rptr = i + len_window - 1;
        if (rptr >= n)
            break;
        ok.pb(max(a[i], a[rptr]));
    }
    int res = 0, totake = ok.size() - k;
    set<pair<int, int>> ss;
    for (size_t i = 0; i < totake; i++)
    {
        ss.insert({ok[i], i});
    }
    res = (*(ss.begin())).first;
    for (int i = totake; i < ok.size(); i++)
    {
        ss.insert({ok[i], i});
        ss.erase({ok[i - totake], i - totake});
        res = max(res, (*(ss.begin())).first);
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