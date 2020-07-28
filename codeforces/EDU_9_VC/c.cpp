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
        vector<string> vec(n);
        for (size_t i = 0; i < n; i++)
        {
            cin >> vec[i];
            // vec[i].s = vec[i].f.size();
            // while (vec[i].f.size() < 50)
            //     vec[i].f += 'z';
        }
        sort(all(vec), [](string a, string b) {
            return a + b < b + a;
        });
        for (size_t i = 0; i < n; i++)
        {
            cout << vec[i];
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
