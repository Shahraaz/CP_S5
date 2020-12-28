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
    vector<pair<int, int>> a(n);
    vector<int> start, END;
    for (auto &x : a)
    {
        cin >> x.first >> x.second;
        start.pb(x.first);
        END.pb(x.second);
    }
    int res = MOD;
    sort(all(start));
    sort(all(END));
    db(start, END);
    for (auto &x : a)
    {
        ll temp = n;
        int endbefore = upper_bound(all(END), x.first - 1) - END.begin();
        int startAfter = start.end() - upper_bound(all(start), x.second);
        db(x, temp, endbefore, startAfter);
        res = min(res, endbefore + startAfter);
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