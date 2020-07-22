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
        string s;
        cin >> s;
        auto s1 = s;
        for (size_t i = 0; i < n; i++)
        {
            int a = s[i] - 'a';
            int z = 'z' - s[i];
            if (a > z)
                s1[i] = 'a';
            else
                s1[i] = 'z';
            if (k < max(a, z))
            {
                int excess = max(a, z) - k;
                if (a > z)
                    s1[i] = 'a' + excess;
                else
                    s1[i] = 'z' - excess;
                k = 0;
                break;
            }
            k -= max(a, z);
            if (k == 0)
                break;
        }
        if (k == 0)
            cout << s1 << '\n';
        else
            cout << "-1\n";
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
