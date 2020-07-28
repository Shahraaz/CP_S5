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
        for (auto &x : a)
        {
            cin >> x;
        }
        db(a);
        for (int i = 31 - 1; i >= 0; i--)
        {
            int cnt = 0;
            for (size_t j = 0; j < n; j++)
                cnt += (a[j] & (1 << i)) > 0;
            if (cnt & 1)
            {
                cout << "WIN\n";
                return;
            }
            if (i == 0)
            {
                cout << "DRAW\n";
                return;
            }
            for (size_t j = 0; j < n; j++)
                a[j] = a[j] ^ (a[j] & (1 << i));
        }
        db(a);
        sort(all(a));
        reverse(all(a));
        int x, y;
        x = y = 0;
        for (size_t i = 0; i < n; i++)
        {
            if (i & 1)
                y ^= a[i];
            else
                x ^= a[i];
        }
        if (x == y)
            cout << "DRAW\n";
        else if (x < y)
            cout << "LOSE\n";
        else
            cout << "WIN\n";
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
