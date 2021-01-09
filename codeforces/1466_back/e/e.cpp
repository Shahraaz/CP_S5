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
    vector<ll> a(n);
    const int LOGN = 62;
    vector<int> cnt(LOGN);
    for (auto &x : a)
    {
        cin >> x;
        for (size_t i = 0; i < LOGN; i++)
            if ((x >> i) & 1)
                cnt[i]++;
    }
    ll res = 0;
    for (size_t i = 0; i < n; i++)
    {
        ll OR = 0;
        ll AND = 0;
        for (size_t j = 0; j < LOGN; j++)
            if ((a[i] >> j) & 1)
            {
                ll temp = 1LL << j;
                temp %= MOD;
                OR += n * temp;
                AND += cnt[j] * temp;
                OR %= MOD;
                AND %= MOD;
            }
            else
            {
                ll temp = 1LL << j;
                temp %= MOD;
                OR += cnt[j] * temp;
                OR %= MOD;
            }
        res += OR * AND;
        res %= MOD;
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