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
        vector<int> a(n), b(n), c(n);
        string s1, s2;
        cin >> s1 >> s2;
        for (size_t i = 0; i < n; i++)
        {
            c[i] = i;
            a[i] = s1[i] - '0';
        }
        for (size_t i = 0; i < n; i++)
        {
            // cin >> b[i];
            b[i] = s2[i] - '0';
        }
        vector<int> res;
        auto do_op = [&](int idx) {
            reverse(a.begin(), a.begin() + idx + 1);
            reverse(c.begin(), c.begin() + idx + 1);
            for (size_t i = 0; i <= idx; i++)
            {
                c[i] = -c[i];
                a[i] = 1 - a[i];
            }
            res.pb(idx + 1);
        };
        db(c);
        for (int i = n - 1; i >= 0; i--)
        {
            if (a[i] == b[i])
                continue;
            if (a[0] == (1 - b[i]))
            {
                /*
                    a x 000 x
                    b ~ 000 !x
                */
               /*
                    1 2 3 4 5 
                    -5 -4 -3 -2 -1
                    -5 -4 -3 -2
               */
                do_op(i);
            }
            else
            {
                /*
                    a x 000 !x
                    b ~ 000 x
                */
                if (i == 0)
                {
                    do_op(i);
                }
                else
                {
                    /*
                        a x 000 !x
                        b ~ 000 x
                    */
                    do_op(0);
                    /*
                        a !x 000 !x
                        b ~ 000 x
                    */
                    do_op(i);
                    /*
                        1 2 3 4 5 6 7
                        -1 2 3 4 5 6 7
                        -7 -6 -5 -4 -3 -2 1
                        -7 -6 -5 -4 -3 -2
                    */

                }
            }
            db(i, c);
            // db(i, a, b);
        }
        db(a, b);
        cout << res.size() << ' ';
        for (auto &x : res)
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
