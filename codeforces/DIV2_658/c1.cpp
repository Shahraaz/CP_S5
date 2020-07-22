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
        deque<int> a(n), b(n), c(n);
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
        int state = 0;
        auto get_first = [&]() -> int {
            if (state == 0)
                return a.front();
            return 1 - a.back();
        };
        auto get_last = [&]() -> int {
            if (state == 0)
                return a.back();
            return 1 - a.front();
        };
        for (int i = n - 1; i >= 0; i--)
        {
            if (b[i] == get_last())
            {
                if (state == 0)
                    a.pop_back();
                else
                    a.pop_front();
                continue;
            }
            if (get_first() == (1 - b[i]))
            {
                if (state == 0)
                    a.pop_front();
                else
                    a.pop_back();
                res.pb(i + 1);
                state = 1 - state;
            }
            else
            {
                if (i == 0)
                {
                    res.pb(i + 1);
                }
                else
                {
                    res.pb(1);
                    res.pb(i + 1);
                    if (state == 0)
                        a.pop_front();
                    else
                        a.pop_back();
                    state = 1 - state;
                }
            }
            db(c);
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
