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
        vector<pair<ll, ll>> vec(2);
        for (auto &x : vec)
            cin >> x.f >> x.s;
        sort(all(vec));
        ll intLen = 0;
        ll cost_to_join = 0;
        if (vec[1].s <= vec[0].s)
            intLen = (vec[1].s - vec[1].f);
        else if (vec[1].f < vec[0].s)
            intLen = (vec[0].s - vec[1].f);
        else
            cost_to_join = vec[1].f - vec[0].s;
        ll res = LLONG_MAX;
        db(vec);
        db(intLen, cost_to_join);
        ll one_more_cost = 0;
        one_more_cost = max(vec[0].s, vec[1].s) - min(vec[1].f, vec[0].f) - intLen;
        for (int cnt = 1; cnt <= n; cnt++)
        {
            ll len_join_req = k - intLen * cnt;
            ll cost = cnt * cost_to_join;
            db(cnt, len_join_req, cost);
            if (len_join_req > 0)
            {
                ll cost_one_avail = cnt * one_more_cost;
                ll cost_one_taken = min(cost_one_avail, len_join_req);
                cost += cost_one_taken;
                db(cost_one_avail, cost_one_taken, cost);
                len_join_req -= cost_one_taken;
                cost += len_join_req * 2;
                db(cost_one_avail, len_join_req, cost);
            }
            res = min(res, cost);
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
