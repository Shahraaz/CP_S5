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
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> adj[4];
        vector<int> pref[4];
        for (size_t i = 0; i < n; i++)
        {
            int t, a, b;
            cin >> t >> a >> b;
            int idx = a;
            if (b)
                idx += 2;
            adj[idx].pb(t);
        }
        for (size_t i = 0; i < 4; i++)
        {
            sort(all(adj[i]));
            int sz = adj[i].size();
            pref[i].resize(sz);
            for (size_t j = 0; j < sz; j++)
            {
                if (j > 0)
                    pref[i][j] = pref[i][j - 1];
                pref[i][j] += adj[i][j];
            }
        }
        db(pref);
        ll res = LLONG_MAX;
        for (int commonCount = 0; commonCount <= pref[3].size(); commonCount++)
        {
            ll curr = 0;
            if (commonCount > 0)
                curr = pref[3][commonCount - 1];
            ll extraneeded = k - commonCount;
            if (pref[1].size() < extraneeded || pref[2].size() < extraneeded)
                continue;
            if (extraneeded > 0)
                curr += pref[1][extraneeded - 1] + pref[2][extraneeded - 1];
            res = min(res, curr);
        }
        if (res == LLONG_MAX)
            cout << -1 << '\n';
        else
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
