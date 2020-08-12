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

int a[] = {6, 10, 14};
struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        if (n <= 30)
        {
            cout << "NO\n";
        }
        else
        {
            cout << "YES\n";
            cout << 6 << ' ' << 10 << ' ';
            if (count(a, a + 3, n - 30))
            {
                cout << 15 << ' ' << n - 31 << '\n';
            }
            else
            {
                cout << 14 << ' ' << n - 30 << '\n';
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
