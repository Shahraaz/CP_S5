#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    long long n1, n2, x, y;
    // n1 = n2 = MOD;
    cin >> n1 >> n2;
    // x = 2, y = 3;
    cin >> x >> y;
    long long low = 0, high = 1e15;
    auto ans = high;
    while (low <= high)
    {
        auto mid = (low + high) / 2;
        auto cntx = mid / x;
        auto cnty = mid / y;
        auto cntxy = mid / (x * y);
        long long tot = mid - cntx - cnty + cntxy;

        long long one = cnty - cntxy;
        long long two = cntx - cntxy;

        if (n1 > one && tot >= (n1 - one))
        {
            tot -= n1 - one;
            one = n1;
        }

        if (n2 > two && tot >= (n2 - two))
        {
            tot -= n2 - two;
            two = n2;
        }

        if (one >= n1 && two >= n2)
        {
            ans = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    cout << ans << '\n';
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