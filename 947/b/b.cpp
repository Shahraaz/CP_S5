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
#define int ll

void solveCase()
{
    int n;
    cin >> n;
    deque<pair<int, int>> D1(n);
    set<pair<int, int>> D;
    for (size_t i = 0; i < n; i++)
        cin >> D1[i].first;

    ll already_t = 0;
    for (size_t i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        ll res = 0;
        D.insert({D1[i].first + already_t, i});
        while (D.size())
        {
            auto it = *D.begin();
            if (it.first <= already_t + t)
            {
                res += it.first - already_t;
                D.erase(it);
            }
            else
            {
                break;
            }
        }
        already_t += t;
        res += t * D.size();
        cout << res << ' ';
    }
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