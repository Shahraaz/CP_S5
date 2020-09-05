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

void Solution::solveCase()
{
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> myVec(4);
    for (size_t i = 0; i < n; i++)
    {
        int w, c;
        cin >> w >> c;
        myVec[w].pb(c);
    }
    auto pref = myVec;
    for (size_t i = 0; i < 4; i++)
    {
        sort(all(pref[i]));
        reverse(all(pref[i]));
        for (size_t j = 1; j < pref[i].size(); j++)
            pref[i][j] += pref[i][j - 1];
    }
    ll res = 0;
    for (ll oneCnt = 0; oneCnt <= pref[1].size(); oneCnt++)
    {
        int remWt = m - oneCnt;
        if (remWt < 0)
            break;
        auto count = [&](int twoCnt) -> ll {
            ll ret = 0;
            twoCnt = min(twoCnt, (int)pref[2].size());
            if (twoCnt)
                ret += pref[2][twoCnt - 1];
            int remFor3 = remWt - 2 * twoCnt;
            remFor3 /= 3;
            remFor3 = min(remFor3, (int)pref[3].size());
            if (remFor3)
                ret += pref[3][remFor3 - 1];
            db(remWt, oneCnt, twoCnt, remFor3, ret);
            return ret;
        };
        ll currCost = 0;
        int low = 0, high = remWt / 2;
        high = min(high, int(pref[2].size()));
        while (low + 500 <= high)
        {
            int mid1 = low + low + high;
            int mid2 = low + high + high;
            mid1 /= 3;
            mid2 /= 3;
            ll a = count(mid1);
            ll b = count(mid2);
            currCost = max(currCost, a);
            currCost = max(currCost, b);
            if (a < b)
                low = mid1;
            else
                high = mid2;
        }
        while (low <= high)
        {
            currCost = max(currCost, count(low));
            ++low;
        }
        if (oneCnt > 0)
            currCost += pref[1][oneCnt - 1];
        res = max(res, currCost);
    }
    cout << res << '\n';
}

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
