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
    int k, x;
    cin >> k >> x;
    db(k, x);
    deque<ll> divisors;
    auto xback = x;
    for (ll i = 2; i * i <= x; i++)
        if (x % i == 0)
        {
            int temp = 1;
            while (x % i == 0)
            {
                temp *= i;
                x /= i;
            }
            divisors.pb(temp);
        }
    if (x > 1)
        divisors.pb(x);
    sort(all(divisors));
    if (divisors.size() <= k)
    {
        ll res = 0;
        for (auto &x : divisors)
            res += x;
        res += k - divisors.size();
        cout << res << '\n';
        return;
    }
    int ndiv = divisors.size();
    map<pair<int, int>, int> cache;
    function<int(int, int)> check = [&](int mask, int remslots) -> int {
        if (mask == 0)
            return remslots;
        if (remslots == 0)
            return MOD;
        auto it = cache.find({mask, remslots});
        if (cache.end() != it)
            return it->second;
        auto &ret = cache[{mask, remslots}];
        ret = MOD;
        for (int s = mask; s; s = (s - 1) & mask)
        {
            // ... you can use s...;
            int sum = 1;
            for (size_t i = 0; i < ndiv; i++)
                if (s & (1 << i))
                    sum *= divisors[i];
            ret = min(ret, sum + check(mask ^ s, remslots - 1));
        }
        return ret;
    };
    cout << check((1 << ndiv) - 1, k) << '\n';
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