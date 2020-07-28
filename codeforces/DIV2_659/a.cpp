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
            int x;
            cin >> x;
            a[i] = x;
        }
        string prev;
        for (size_t i = 0; i < 150; i++)
            prev += 'a';
        vector<string> ans(n + 1, prev);
        ans[0] = prev;
        char run = 'b';
        for (size_t i = 0; i < n; i++)
        {
            ans[i + 1] = ans[i];
            while (ans[i + 1][a[i]] == run)
            {
                if (run == 'z')
                    run = 'b';
                else
                    run++;
            }

            ans[i + 1][a[i]] = run;
        }
        for (auto &x : ans)
        {
            cout << x << '\n';
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
