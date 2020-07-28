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
        vector<int> cnt(2);
        int maxLen, maxFptr;
        maxLen = maxFptr = -1;
        while (lptr < n)
        {
            if (rptr < lptr)
            {
                cnt = {0, 0};
                rptr = lptr;
            }
            while (rptr < n)
            {
                if (a[rptr] == 0)
                {
                    if (cnt[0] == k)
                        break;
                    cnt[0]++;
                    rptr++;
                }
                else
                {
                    cnt[1]++;
                    rptr++;
                }
            }
            if (cnt[0] + cnt[1] > maxLen)
            {
                maxLen = cnt[0] + cnt[1];
                maxFptr = lptr;
            }
            cnt[a[lptr]]--;
            lptr++;
        }
        for (size_t i = 0; i < maxLen; i++)
            a[maxFptr + i] = 1;
        cout << maxLen << '\n';
        for (auto &x : a)
        {
            cout << x << ' ';
        }
        cout << '\n';
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
