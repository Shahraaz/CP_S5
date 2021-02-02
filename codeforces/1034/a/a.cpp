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
const int NAX = 1.5 * 1e7 + 5, MOD = 1000000007;

int mp[NAX];
int cnt[NAX];

const int NAX_PRIME = NAX;
bool is_composite[NAX_PRIME];
vector<int> primes;
int spf[NAX];

void seive(int n = NAX_PRIME)
{
    fill(is_composite, is_composite + n, false);
    for (int i = 2; i < n; i++)
    {
        if (!is_composite[i])
        {
            spf[i] = i;
            primes.push_back(i);
        }
        for (size_t j = 0; j < primes.size() && ((ll)i * primes[j] < n); j++)
        {
            spf[i * primes[j]] = (primes[j]);
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

void solveCase()
{
    seive();
    int n;
    cin >> n;
    int g = 0;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        g = __gcd(g, x);
        db(i, x, g);
        mp[x]++;
    }
    int res = n;
    for (size_t i = 1; i < NAX; i++)
    {
        if (mp[i])
        {
            db(i);
            int now = i / g;
            while (true)
            {
                int pf = spf[now];
                cnt[spf[now]] += mp[i];
                db(now, spf[now]);
                if (now == 1 || spf[now] == 0)
                    break;
                while (now % pf == 0)
                    now = now / pf;
            }
        } // for (size_t j = 2 * i; j < NAX; j += i)
        //     cnt[i] += mp[j];
    }
    for (size_t curr = 2; curr < NAX; curr += 1)
    {
        if (cnt[curr])
        {
            db(curr, cnt[curr]);
            res = min(res, n - cnt[curr]);
        }
    }

    if (res == n)
        res = -1;
    cout << res << '\n';
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