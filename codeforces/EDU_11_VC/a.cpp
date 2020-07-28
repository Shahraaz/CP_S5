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
        deque<int> a;
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            if (a.size() == 0)
                a.push_back(x);
            else
            {
                if (__gcd(a.back(), x) != 1)
                {
                    a.push_back(1);
                }
                a.push_back(x);
            }
            db(i, x, a);
        }
        cout << a.size() - n << '\n';
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
