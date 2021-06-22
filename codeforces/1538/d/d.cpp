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

const int NAX_PRIME = sqrt(MOD) + 5;
bool is_composite[NAX_PRIME];
vector<int> primes;

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
}

int factors(int x)
{
    int cnt = 0;
    db(x);
    for (auto &y : primes)
        while (x % y == 0)
            ++cnt, x /= y;
    if (x > 1)
        ++cnt;
    db(cnt);
    return cnt;
}

void solveCase()
{
    ll a, b, k;
    cin >> a >> b >> k;
    auto f_a = factors(a);
    auto f_b = factors(b);
    if (k == 1)
    {
        if (a == b)
        {
            cout << "NO\n";
            return;
        }
        if (a % b == 0 || b % a == 0)
            cout << "YES\n";
        else
            cout << "NO\n";
        return;
    }
    if (k <= f_a + f_b)
        cout << "YES\n";
    else
        cout << "NO\n";
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