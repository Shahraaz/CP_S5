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
        ll n;
        cin >> n;
        vector<ll> sizes(n + 2);
        for (size_t i = 1; i <= n; i++)
            sizes[i] = sizes[i - 1] + 2 * (n - i);
        sizes[n + 1] = sizes[n] = 1 + sizes[n - 1];
        auto get = [&sizes, &n](ll idx) -> ll {
            if (idx == (n * (n - 1LL) + 1))
                return 1;
            auto index = lower_bound(all(sizes), idx) - sizes.begin();
            // return 0;
            index--;
            ll diff = idx - sizes[index];
            db(idx, index, diff);
            if (diff % 2)
                return index + 1;
            return index + 1 + diff / 2;
        };
        ll l, r;
        cin >> l >> r;
        db(n, l, r);
        while (l <= r)
        {
            // db(get(l++));
            cout << get(l++) << ' ';
        }
        cout << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
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
