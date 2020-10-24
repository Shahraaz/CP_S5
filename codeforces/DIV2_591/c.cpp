// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    vector<ll> p(n);
    for (auto &x : p)
        cin >> x;
    sort(all(p));
    reverse(all(p));
    ll x, a;
    cin >> x >> a;
    ll y, b;
    cin >> y >> b;
    if (x > y)
    {
        swap(x, y);
        swap(a, b);
    }
    ll k;
    cin >> k;
    int low = 1, high = n;
    int ans = MOD;
    db(p);
    db(x, y);
    db(a, b);
    auto check = [&](int cnt) -> bool {
        int cnt1 = cnt / a;
        int cnt2 = cnt / b;
        int cnt3 = cnt / (a * b / __gcd(a, b));
        cnt1 -= cnt3;
        cnt2 -= cnt3;
        db(cnt, cnt1, cnt2, cnt3);
        ll one = (y + x) * accumulate(p.begin(), p.begin() + cnt3, 0LL) / 100;
        db(cnt3, one);
        one += y * accumulate(p.begin() + cnt3, p.begin() + cnt3 + cnt2, 0LL) / 100;
        db(cnt2, one);
        one += x * accumulate(p.begin() + cnt3 + cnt2, p.begin() + cnt1 + cnt2 + cnt3, 0LL) / 100;
        db(cnt1, one);
        return one >= k;
    };
    while (low <= high)
    {
        int mid = low + high;
        mid /= 2;
        if (check(mid))
        {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    if (ans == MOD)
        ans = -1;
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
