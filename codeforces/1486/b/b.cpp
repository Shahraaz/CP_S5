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
    vector<ll> x(n), y(n);
    for (size_t i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    auto cnt = [&](vector<ll> &curr) -> ll {
        sort(all(curr));
        ll mini = LLONG_MAX, cnt = 1;
        int cntl = 0, cntr = n;
        ll suml = 0, sumr = accumulate(all(curr), 0LL);
        vector<ll> ans(n);
        for (size_t i = 0; i < n; i++)
        {
            sumr -= curr[i];
            cntr--;
            ans[i] = sumr - suml + curr[i] * (cntl - cntr);
            suml += curr[i];
            cntl++;
        }
        for (size_t i = 0; i + 1 < n; i++)
        {
            if (ans[i] < mini)
            {
                mini = ans[i];
                cnt = 1;
                if (ans[i + 1] == ans[i])
                    cnt = curr[i + 1] - curr[i] + 1;
            }
            else if (ans[i] == mini)
            {
                if (ans[i + 1] == ans[i])
                    cnt = max(cnt, curr[i + 1] - curr[i] + 1);
            }
        }
        return cnt;
    };
    cout << cnt(x) * cnt(y) << '\n';
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