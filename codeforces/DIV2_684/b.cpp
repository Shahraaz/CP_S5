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
    int n, k;
    cin >> n >> k;
    vector<int> a(n * k);
    for (auto &x : a)
        cin >> x;
    sort(all(a));
    int med = (n + 1) / 2;
    ll res = 0;
    int curr = n, cnt = 0;
    for (int i = n * k - 1; i >= 0; i--)
    {
        curr--;
        db(i, curr, a[i], res, cnt);
        if (curr == (med - 1))
        {
            res += a[i];
            cnt++;
            curr = n;
        }
        if (cnt == k)
            break;
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