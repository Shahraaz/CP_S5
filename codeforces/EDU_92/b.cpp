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
        int n, k, z;
        cin >> n >> k >> z;
        vector<ll> a(n);
        for (auto &x : a)
            cin >> x;
        ll res = 0;
        for (size_t i = 0; i <= z; i++)
        {
            int left = i;
            int right = k - left;
            int pos = right - left;
            ll temp = 0;
            db(left, right, pos);
            if (right < 0 || pos < 0)
                break;
            for (size_t i = 0; i <= pos; i++)
                temp += a[i];
            ll temp2 = 0;
            for (size_t i = 0; i <= pos; i++)
                if (i + 1 < n)
                    temp2 = max(temp2, a[i] + a[i + 1]);
            res = max(res, temp + temp2 * left);
        }
        cout << res << '\n';
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
