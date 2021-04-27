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

vector<ll> vecc;

void solveCase()
{
    ll n;
    cin >> n;
    int rptr = vecc.size() - 1;
    int res = 0;
    while (rptr >= 0)
    {
        res += n / vecc[rptr];
        n = n % vecc[rptr];
        db(n, res, rptr, vecc[rptr], n % vecc[rptr]);
        --rptr;
    }
    db(n);
    if (n != 0)
        res = -1;
    cout << res << '\n';
}

int32_t main()
{
    ll curr = 2050;
    while (curr < LLONG_MAX)
    {
        vecc.pb(curr);
        if (curr * 10.0 >= LLONG_MAX)
            break;
        curr = curr * 10;
    }
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