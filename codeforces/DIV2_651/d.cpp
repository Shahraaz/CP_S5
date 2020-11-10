#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

int a[NAX], n, k;

bool check(int x, int cur)
{
    int len = 0;
    db(x, cur);
    for (size_t i = 0; i < n; i++)
    {
        if (cur)
            len++, cur = !cur;
        else if (a[i] <= x)
            len++, cur = !cur;
    }
    db(len);
    return len >= k;
}

void solveCase()
{
    db(ceil(-0.5));
    cin >> n >> k;
    for (size_t i = 0; i < n; i++)
        cin >> a[i];
    int low = 0, high = MOD, ans = high;
    while (low <= high)
    {
        int mid = (low + high) >> 1;
        if (check(mid, 0) || check(mid, 1))
            ans = mid, high = mid - 1;
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef TIMER
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}