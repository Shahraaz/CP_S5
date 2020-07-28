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
        int n, k, l;
        cin >> n >> k >> l;
        vector<int> d(n);
        for (auto &x : d)
            cin >> x;
        for (auto &x : d)
            if (x > l)
            {
                cout << "No\n";
                return;
            }
        int pos = min(k, l - d[0]);
        int sign = -1;
        db("---------");
        for (size_t i = 0; i < n; i++)
        {
            db(i, pos, d[i] + pos, l);
            if (d[i] + pos > l)
            {
                if (sign == 1)
                {
                    cout << "No\n";
                    return;
                }
                pos = l - d[i];
            }
            db(i, pos, d[i] + pos, l, "\n");
            if (l - d[i] >= k)
            {
                sign = -1;
                pos = k;
            }
            if (sign == -1)
            {
                pos--;
                if (pos == -1)
                {
                    sign = 1;
                    pos = 1;
                }
            }
            else
            {
                pos++;
                if (pos == (k + 1))
                {
                    sign = -1;
                    pos = k - 1;
                }
            }
        }
        cout << "Yes\n";
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
