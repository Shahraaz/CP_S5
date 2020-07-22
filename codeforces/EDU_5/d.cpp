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
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (auto &x : a)
            cin >> x;
        int lptr = 0, rptr = 0;
        map<int, int> mp;
        pair<int, int> res;
        res.f = -MOD;
        int cnt = 0;
        while (lptr < n)
        {
            rptr = max(rptr, lptr);
            while (rptr < n)
            {
                if (mp[a[rptr]] == 0 && cnt == k)
                    break;
                cnt += mp[a[rptr]] == 0;
                mp[a[rptr]]++;
                rptr++;
            }
            db(lptr, rptr, mp);
            res = max(res, {rptr - lptr, lptr});
            mp[a[lptr]]--;
            cnt -= mp[a[lptr]] == 0;
            lptr++;
        }
        db(res);
        cout << res.s + 1 << ' ' << res.f + res.s << '\n';
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
