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

int ask(int l, int r)
{
    cout << "? " << l << ' ' << r << endl;
    int idx;
    cin >> idx;
    return idx;
}

void solveCase()
{
    int n;
    cin >> n;
    int max2 = ask(1, n);
    if (max2 == 1 || (ask(1, max2) != max2)) // right half
    {
        ll low = max2 + 1, high = n;
        ll ans = n;
        while (low <= high)
        {
            ll mid = (low + high) / 2;
            if (ask(max2, mid) == max2)
            {
                ans = min(ans, mid);
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        cout << "! ";
        cout << ans << endl;
    }
    else
    {
        ll low = 1, high = max2 - 1;
        ll ans = 1;
        while (low <= high)
        {
            ll mid = (low + high) / 2;
            if (ask(mid, max2) == max2)
            {
                ans = max(ans, mid);
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        cout << "! ";
        cout << ans << endl;
    }
}

int32_t main()
{
#ifndef LOCAL
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}