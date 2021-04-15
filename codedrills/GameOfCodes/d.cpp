#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
const int NAX = 1e6 + 5, MOD = 1000000007;

const int NAX_PRIME = NAX;
bool is_composite[NAX_PRIME];
vector<int> primes;
long long dp[NAX];

using ll = long long;
void seive(int n = NAX_PRIME)
{
    fill(is_composite, is_composite + n, false);
    for (int i = 2; i < n; i++)
    {
        if (!is_composite[i])
            primes.push_back(i);
        for (size_t j = 0; j < primes.size() && ((ll)i * primes[j] < n); j++)
        {
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
    for (size_t i = 0; i < primes.size(); i++)
    {
        auto p = primes[i] * 1LL * primes[i] * primes[i];
        if (p < NAX)
            dp[p]++;
        for (size_t j = i + 1; j < primes.size(); j++)
        {
            auto p = primes[i] * 1LL * primes[j];
            if (p >= NAX)
                break;
            dp[p]++;
        }
    }
    for (size_t i = 1; i < NAX; i++)
    {
        db(i, dp[i]);
        dp[i] += dp[i - 1];
    }
}

void solveCase()
{
    long long l, r;
    cin >> l >> r;
    cout << dp[r] - dp[l - 1] << '\n';
}

int32_t main()
{
    seive();
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