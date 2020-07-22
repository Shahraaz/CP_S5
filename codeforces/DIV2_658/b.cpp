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
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        vector<int> canWin(n);
        canWin[n - 1] = true;
        for (int i = n - 2; i >= 0; i--)
        {
            if (a[i] == 1)
            {
                canWin[i] = 1 - canWin[i + 1];
            }
            else if (a[i] == 2)
            {
                canWin[i] = 1;
            }
            else
            {
                if (canWin[i + 1])
                {
                    canWin[i] = 1;
                }
                else
                {
                    if (a[i] == 3)
                    {
                        canWin[i] = 0;
                    }
                    else
                    {
                        canWin[i] = 1;
                    }
                }
            }
        }
        db(canWin);
        if (canWin[0])
            cout << "First\n";
        else
            cout << "Second\n";
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
