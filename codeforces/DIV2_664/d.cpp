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
    void solveCase()
    {
        int n, d, m;
        cin >> n >> d >> m;
        vector<int> a(n);
        for (auto &x : a)
            cin >> x;
        vector<ll> a1, b1;
        for (auto &x : a)
        {
            if (x <= m)
                a1.pb(x);
            else
                b1.pb(x);
        }
        for (size_t i = 0; i < n; i++)
        {
            a1.pb(0);
            b1.pb(0);
        }
        sort(all(a1));
        sort(all(b1));
        reverse(all(a1));
        reverse(all(b1));
        for (size_t i = 1; i < a1.size(); i++)
            a1[i] += a1[i - 1];
        for (size_t i = 1; i < b1.size(); i++)
            b1[i] += b1[i - 1];
        int low = 0, high = b1.size();
        auto check = [&](int takeFromB) -> ll {
            ll temp = (takeFromB - 1LL) * (d + 1) + 1;
            if (temp < 0)
                temp = 0;
            if (temp > n)
                return LLONG_MIN;
            ll ret = 0;
            if (takeFromB > 0)
                ret += b1[takeFromB - 1];
            temp = n - temp;
            if (temp > 0)
                ret += a1[temp - 1];
            return ret;
        };
        ll maxFun = LLONG_MIN;
        while (low <= high)
        {
            ll temp = check(low);
            db(low, temp);
            maxFun = max(maxFun, temp);
            low++;
        }
        cout << maxFun << '\n';
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
