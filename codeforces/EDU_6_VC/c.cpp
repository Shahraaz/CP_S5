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
        int n;
        cin >> n;
        vector<int> a(n);
        map<int, deque<int>> mp;
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
            mp[a[i]].pb(i);
        }
        auto seek = [&](int i) {
            int rptr = -1;
            for (; i < n; i++)
                if (mp[a[i]].size() >= 2)
                {
                    rptr = mp[a[i]][1];
                    break;
                }
            return rptr;
        };
        int lptr = 0, rptr = seek(lptr);
        if (rptr == -1)
        {
            cout << -1 << '\n';
            return;
        }
        vector<int> v;
        while (lptr < n)
        {
            if (lptr == rptr)
            {
                v.pb(rptr);
                mp[a[lptr]].pop_front();
                lptr++;
                rptr = seek(lptr);
                if (rptr == -1)
                {
                    if (v.size())
                        v.pop_back();
                    v.pb(n - 1);
                    break;
                }
            }
            else
            {
                if (mp[a[lptr]].size() > 1)
                    rptr = min(rptr, mp[a[lptr]][1]);
                mp[a[lptr]].pop_front();
                ++lptr;
            }
        }
        v.erase(unique(all(v)), v.end());
        cout << v.size() << '\n';
        lptr = 0;
        for (size_t i = 0; i < v.size(); i++)
        {
            cout << lptr + 1 << ' ' << v[i] + 1 << '\n';
            lptr = v[i] + 1;
        }
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
