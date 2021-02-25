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
    ll n, k;
    cin >> n >> k;
    if (n % 2 == 0)
    {
        --k;
        ll curr = (k) % n;
        cout << curr + 1 << '\n';
        return;
    }
    ll a = n - 1, b = 0;
    if (k == 1)
    {
        cout << 1 << '\n';
        return;
    }
    b = 0;
    --k;
    b += (k);
    ll len = (n - 1) / 2;
    if (k >= (len - 1))
    {
        b++;

        k -= len;
        b += (k) / len;
    }
    b %= n;
    cout << b + 1 << '\n';
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