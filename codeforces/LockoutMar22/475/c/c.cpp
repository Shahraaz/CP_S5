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

const int NAX_PRIME = 1e6 + 5;
int is_composite[NAX_PRIME], cnt[NAX_PRIME];
// vector<int> primes;

void seive(int n = NAX_PRIME)
{
    // fill(is_composite, is_composite + n, false);
    for (int i = 1; i < n; i++)
    {
        // if (!is_composite[i])
        //     primes.push_back(i);
        for (size_t j = i; j < n; j += i)
        {
            cnt[j] += 1;
        }
    }
}

void solveCase()
{
    seive();
    ll res = accumulate(cnt, cnt + NAX_PRIME, 0LL);
    db(res);
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
        solveCase();
    return 0;
}