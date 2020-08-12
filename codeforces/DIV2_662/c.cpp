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
        map<int, int> cnt;
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            cnt[x]++;
        }
        vector<pair<int, int>> v;
        for (auto &x : cnt)
            v.pb({x.s, x.f});
        sort(all(v));
        reverse(all(v));
        if (cnt.size() == 1)
        {
            cout << 0 << '\n';
        }
        else
        {
            // if (cnt.size() > 1 && v[0].f == 2)
            // {
            //     cout << n - 2 << '\n';
            // }
            // else
            {
                vector<deque<int>> vec(v[0].f);
                int ptr = 0;
                int maxi = v[0].f;
                for (size_t i = 0; i < cnt.size(); i++)
                {
                    int prev = v[i].f;
                    while (v[i].f--)
                    {
                        if (prev != maxi)
                            if (ptr + 1 == vec.size())
                                ptr = 0;
                        vec[ptr].pb(v[i].s);
                        ptr++;
                        ptr %= vec.size();
                    }
                }
                db(vec);
                int res = MOD;
                map<int, vector<int>> mp;
                ptr = 0;
                for (size_t i = 0; i < vec.size(); i++)
                    for (auto &x : vec[i])
                    {
                        if (mp[x].size())
                            res = min(res, ptr - mp[x].back() - 1);
                        mp[x].pb(ptr);
                        ++ptr;
                    }
                db(mp);
                cout << res << '\n';
            }
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
