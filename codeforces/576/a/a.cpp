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
const int NAX = 1e3 + 5, MOD = 1000000007;

int dp[NAX];

const int _NSeive = 1e3 + 10;
vector<bool> isPrime(_NSeive, true);
vector<int> primes;
void buildSeive()
{
    isPrime[1] = false;
    isPrime[0] = false;
    primes.pb(2);
    for (int i = 4; i < _NSeive; i += 2)
        isPrime[i] = false;
    for (int i = 3; i * i < _NSeive; i += 2)
        if (isPrime[i])
        {
            primes.pb(i);
            for (int j = i * i; j < _NSeive; j += i)
                isPrime[j] = false;
        }
}

int solve(int x)
{
    // if (x <= 1)
    //     return 0;
    // if (x == 2)
    //     return 1;
    // auto &ret = dp[x];
    // if (ret >= 0)
    //     return ret;
    // auto up = upper_bound(all(primes), x) - primes.begin();
    // db(x, up);
    // assert(up > 0);
    // ret = MOD;
    // vector<int> temp;
    // for (size_t i = 0; i < up; i++)
    // {
    //     temp.pb(1 + solve(x / primes[i]));
    // }
    // return ret;
}

void solveCase()
{
    // memset(dp, -1, sizeof dp);
    int n;
    // buildSeive();
    // db(primes);
    cin >> n;
    // cout << solve(n) << '\n';
    vector<int> asked(n + 1);
    vector<int> res;
    for (size_t i = 2; i <= n; i++)
    {
        if (!asked[i])
        {
            db(i, res);
            for (size_t j = 2; j <= n; j++)
                if (asked[j])
                {
                    auto lcm = i * j / __gcd(i, j);
                    if (lcm <= n)
                        asked[lcm] = 1;
                }
            asked[i] = 1;
            db(asked);
            res.pb(i);
        }
    }
    cout << res.size() << '\n';
    for (auto &x : res)
        cout << x << ' ';
    cout << '\n';
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