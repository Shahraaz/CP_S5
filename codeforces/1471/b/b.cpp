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
    ll n, x;
    cin >> n >> x;
    vector<ll> a(n);
    vector<ll> cnter(n);
    ll res = 0, sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += a[i];
        int cnt = 0, now = a[i];
        while (now % x == 0)
        {
            now /= x;
            cnt++;
        }
        cnter[i] = cnt;
    }
    auto it = min_element(all(cnter)) - cnter.begin();
    db(a, sum);
    db(cnter);
    db(it);
    res += sum * (cnter[it] + 1);
    for (size_t i = 0; i < it; i++)
        res += a[i];
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