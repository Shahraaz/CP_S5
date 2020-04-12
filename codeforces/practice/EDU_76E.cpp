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
        int k1, k2, k3;
        cin >> k1 >> k2 >> k3;
        int n = k1 + k2 + k3;
        vector<int> a(n);
        for (size_t i = 0; i < k1; i++)
        {
            int x;
            cin >> x;
            a[x - 1] = 0;
        }
        for (size_t i = 0; i < k2; i++)
        {
            int x;
            cin >> x;
            a[x - 1] = 1;
        }
        for (size_t i = 0; i < k3; i++)
        {
            int x;
            cin >> x;
            a[x - 1] = 2;
        }
        int ans = 0;
        int bestp = 0;
        for (size_t i = 0; i < n; i++)
            if (a[i] != 2)
                ans++;
        vector<int> cntl(3);
        vector<int> cntr(3);
        for (size_t i = 0; i < n; i++)
            cntr[a[i]]++;

        for (size_t i = 0; i < n; i++)
        {
            cntl[a[i]]++;
            cntr[a[i]]--;
            bestp = max(bestp, cntl[0] - cntl[1]);
            int currans = cntr[0] + cntr[1] + cntl[2] + cntl[0] - bestp;
            ans = min(ans, currans);
        }
        cout << ans << '\n';
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
