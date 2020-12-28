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
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    if (a > b)
    {
        a = n - a + 1;
        b = n - b + 1;
    }

    vector<int> bombs(m);
    for (auto &x : bombs)
        cin >> x;
    sort(all(bombs));

    auto check = [&](int cnt) -> bool {
        int maxt = 0;
        db(cnt);
        int b1 = b;
        for (int i = cnt - 1; i >= 0; i--)
        {
            if (a == b1)
                return false;
            db(cnt - 1 - i + bombs[i]);
            maxt = max(maxt, cnt - 1 - i + bombs[i]);
            b1--;
        }
        if (a == b1)
            return false;
        db(b - 1, b1, maxt);
        return (b - 1) > maxt;
    };

    int low = 0, high = m, ans = 0;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (check(mid))
        {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else
            high = mid - 1;
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