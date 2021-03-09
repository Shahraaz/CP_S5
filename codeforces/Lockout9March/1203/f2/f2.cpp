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
    int n, r;
    cin >> n >> r;
    vector<pair<ll, ll>> pos, neg;
    for (size_t i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        if (b >= 0)
            pos.pb({a, b});
        else
        {
            a = max(a, -b);
            neg.pb({a, b});
        }
    }
    sort(all(pos));
    sort(all(neg), [&](auto &a, auto &b) -> bool { return a.first + a.second > b.first + b.second; });
    db(pos, neg);
    int cnt = 0;
    for (size_t i = 0; i < pos.size(); i++)
        if (r >= pos[i].first)
        {
            r += pos[i].second;
            cnt++;
        }
    vector<int> maxcnt(r + 1, 0);
    maxcnt[r] = cnt;
    for (size_t i = 0; i < neg.size(); i++)
    {
        db(i, maxcnt);
        vector<int> maxcnt2 = maxcnt;
        for (int curr_r = 0; curr_r <= r; curr_r++)
            if (curr_r >= neg[i].first && (curr_r + neg[i].second) >= 0)
                maxcnt2[curr_r + neg[i].second] = max(maxcnt2[curr_r + neg[i].second], 1 + maxcnt[curr_r]);
        db(maxcnt2);
        maxcnt.swap(maxcnt2);
    }
    cout << (*max_element(all(maxcnt))) << '\n';
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