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
        if (n == 1)
        {
            cout << 1 << '\n';
            return;
        }
        int ctr = 1;
        vector<int> O, E;
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < n; j++)
            {
                if (ctr % 2 == 0)
                    E.push_back(ctr);
                else
                    O.push_back(ctr);
                ctr += 1;
            }
        int sgn = 1;
        int ptr = 1;
        for (size_t i = 0; i < n; i++)
        {
            int curr = n - ptr;
            curr /= 2;
            for (size_t j = 0; j < curr; j++)
            {
                cout << E.back() << ' ';
                E.pop_back();
            }
            for (size_t j = 0; j < ptr; j++)
            {
                cout << O.back() << ' ';
                O.pop_back();
            }
            for (size_t j = 0; j < curr; j++)
            {
                cout << E.back() << ' ';
                E.pop_back();
            }
            cout << '\n';
            if (ptr == n)
                sgn = -1;
            ptr += sgn * 2;
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
