// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

ll ask(char c, ll x)
{
    cout << c << ' ' << x << endl;
    cin >> x;
    return x;
}

void Solution::solveCase()
{
    int n;
    cin >> n;
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = 0;
    vector<int> smol, large;
    for (ll i = 2; i <= n; i++)
        if (isPrime[i])
        {
            if (i < 400)
                smol.pb(i);
            else
                large.pb(i);
            for (ll j = i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    ll ans = 1;
    for (auto &x : smol)
    {
        ll cur = x;
        auto res = ask('B', x);
        while (true)
        {
            if (cur > n)
                break;
            res = ask('A', cur);
            if (res > 0)
            {
                ans *= x;
                cur *= x;
            }
            else
                break;
        }
    }
    db("stage2");
    const int BUCKET_SIZE = 100;
    int cnt = ask('A', 1);
    for (size_t b = 0; b < large.size(); b += BUCKET_SIZE)
    {
        int sum = 0;
        for (size_t i = b; i < min(b + BUCKET_SIZE, (large.size())); i++)
        {
            auto res = ask('B', large[i]);
            sum += res;
        }
        int cnt2 = ask('A', 1);
        if (cnt - sum != cnt2)
            for (size_t i = b; i < min(b + BUCKET_SIZE, (large.size())); i++)
            {
                auto res = ask('A', large[i]);
                if (res > 0)
                    ans *= large[i];
            }
        cnt = cnt2;
    }
    cout << "C" << ' ' << ans << endl;
}

int32_t main()
{
#ifndef LOCAL
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
