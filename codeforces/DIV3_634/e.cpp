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
        int n;
        cin >> n;
        vector<int> a(n);
        const int DIM = 201 + 1;
        vector<vector<int>> poses(DIM);
        for (auto &x : a)
            cin >> x;
        for (size_t i = 0; i < n; i++)
            poses[a[i]].pb(i);
        vector<vector<int>> dp2(n, vector<int>(DIM));
        for (size_t i = 0; i < n; i++)
        {
            if (i > 0)
                dp2[i] = dp2[i - 1];
            dp2[i][a[i]]++;
        }
        int res = 0;
        // db(poses);
        db(a);
        for (size_t startElem = 0; startElem < DIM; startElem++)
        {
            res = max(res, (int)poses[startElem].size());
            // db(poses[startElem]);
            for (size_t len = 1; 2 * len <= n; len++)
            {
                int tot = 2 * len;
                if (dp2[n - 1][startElem] < tot)
                    continue;
                int startIdx = poses[startElem][len - 1];
                int EndIdx = poses[startElem][poses[startElem].size() - len];
                db(len, startElem, startIdx, EndIdx);
                if (startIdx > EndIdx)
                    continue;
                for (size_t secElen = 0; secElen < DIM; secElen++)
                {
                    int temp = 0;
                    if (EndIdx - 1 >= 0)
                        temp += dp2[EndIdx - 1][secElen];
                    temp -= dp2[startIdx][secElen];
                    res = max(res, (int)len * 2 + temp);
                }
            }
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
