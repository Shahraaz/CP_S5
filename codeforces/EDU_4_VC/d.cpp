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
        map<pair<int, ll>, ll> mp;
        int n, k;
        cin >> n >> k;
        vector<pair<ll, ll>> ret;
        for (size_t i = 0; i < n; i++)
        {
            ll a, b;
            cin >> a >> b;
            mp[{a, 0}]++;
            mp[{b, 1}]--;
        }
        int curr = 0;
        db(mp);
        for (auto &x : mp)
        {
            db(x, curr);
            if (x.s > 0)
            {
                curr += x.s;
                if (ret.size() && ret.back().s == -MOD)
                    continue;
                if (curr >= k)
                    ret.pb({x.f.f, -MOD});
            }
            else if (x.s < 0)
            {
                curr += x.s;
                if (ret.size() && ret.back().s != -MOD)
                    continue;
                if (curr < k && ret.size())
                    ret.back().s = x.f.f;
                // ret.pb({x.f, -1});
            }
            db(curr, ret, "------------\n");
        }
        cout << ret.size() << '\n';
        for (auto &x : ret)
            cout << x.f << ' ' << x.s << '\n';
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
