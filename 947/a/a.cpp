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
bool is_composite[NAX_PRIME];
vector<int> primes;
vector<int> spf;

void seive(int n = NAX_PRIME)
{
    fill(is_composite, is_composite + n, false);
    spf.resize(NAX_PRIME, 1);
    for (int i = 2; i < n; i++)
    {
        if (!is_composite[i])
        {
            primes.push_back(i);
            for (size_t j = 2 * i; j < n; j += i)
            {
                if (spf[j] == 1)
                    spf[j] = i;
                is_composite[j] = 1;
            }
        }
        // for (size_t j = 0; j < primes.size() && ((ll)i * primes[j] < n); j++)
        // {
        //     is_composite[i * primes[j]] = true;
        //     if (i % primes[j] == 0)
        //         break;
        // }
    }
}

void solveCase()
{
    int x;
    cin >> x;
    seive();
    function<pair<int, int>(int)> getranges = [&](int x) -> pair<int, int> {
        deque<int> Q;
        auto n = x;
        while (true)
        {
            // db(x, spf[x]);
            if (spf[x] == 1)
            {
                Q.pb(x);
                break;
            }
            else
                Q.pb(spf[x]);
            x /= spf[x];
        }
        sort(all(Q));
        Q.resize(unique(all(Q)) - Q.begin());
        // db(Q);
        int mini = n, maxi = n;
        for (auto &x : Q)
        {
            if (n % x == 0)
            {
                mini = min(mini, n - x + 1);
            }
            else
            {
                mini = min(mini, n / x * x + 1);
            }
        }
        // db(mini, maxi);
        return {mini, maxi};
    };
    auto ranges = getranges(x);
    int mini = ranges.second;
    int maxi = ranges.second;
    for (int i = ranges.first; i <= ranges.second; i++)
    {
        if (!is_composite[i])
            continue;
        auto temp = getranges(i);
        db(i, temp);
        mini = min(mini, temp.first);
    }
    cout << mini << '\n';
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