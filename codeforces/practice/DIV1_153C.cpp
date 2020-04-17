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

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        ll a, b, k;
        cin >> a >> b >> k;
        ll xx = 1;
        for (ll i = 2; i <= k; i++)
            xx = xx / __gcd(xx, i) * i;
        const int LIM = xx;
        auto go = [&](ll from, ll to) -> ll {
            vector<int> f(LIM, MOD);
            f[from] = 0;
            for (int i = LIM - 1; i >= 1; i--)
            {
                if (f[i] + 1 < f[i - 1])
                    f[i - 1] = f[i] + 1;
                for (size_t j = 2; j <= k; j++)
                {
                    int z = i - i % j;
                    if (f[i] + 1 < f[z])
                        f[z] = f[i] + 1;
                }
            }
            return f[to];
        };
        ll ans = 0;
        if (a / LIM == b / LIM)
            ans = go(a % LIM, b % LIM);
        else
        {
            ans = go(a % LIM, 0);
            ans += 1 + go(LIM - 1, b % LIM);
            ans += (1 + go(LIM - 1, 0)) * (a / LIM - b / LIM - 1);
        }
        cout << ans << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
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
