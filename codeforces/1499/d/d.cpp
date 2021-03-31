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
const int NAX = 2e7 + 5, MOD = 1000000007;

const int NAX_PRIME = NAX;
bool is_composite[NAX_PRIME];
ll w[NAX];
// ll spf[NAX];
vector<int> primes;

void seive(int n = NAX_PRIME)
{
    fill(is_composite, is_composite + n, false);
    w[1] = 1;
    for (int i = 2; i < n; i++)
    {
        if (!is_composite[i])
        {
            primes.push_back(i);
            w[i] = 2;
            // spf[i] = i;
        }
        for (size_t j = 0; j < primes.size() && ((ll)i * primes[j] < n); j++)
        {
            ll curr = i * primes[j];
            // if (spf[curr] == 0)
            //     spf[curr] = primes[j];
            is_composite[curr] = true;
            if (i % primes[j] == 0)
            {
                w[curr] = w[i];
                break;
            }
            else
                w[curr] = w[i] << 1;
        }
        // db(i, spf[i]);
        // assert(spf[i] != 0);
    }
}

void solveCase()
{
    int c = 1e7, d = 1e7, x = 1e7;
    cin >> c >> d >> x;
    vector<int> divisors;
    for (ll i = 1; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            ll x2 = x / i;
            divisors.pb(i);
            if (i != x2)
                divisors.pb(x2);
        }
    }
    sort(all(divisors));
    db(divisors);
    ll ret = 0;
    db(c, d, x);
    for (auto &g : divisors)
    {
        int x_g = x / g + d;
        if (x_g > 0 && x_g % c == 0)
        {
            int k = x_g / c;
            auto temp = w[k];
            ret += temp;
        }
    }
    cout << ret << '\n';
}

int32_t main()
{
    seive();
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1e4;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}