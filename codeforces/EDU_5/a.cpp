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
        string a, b;
        cin >> a >> b;
        reverse(all(a));
        reverse(all(b));
        while (a.size() && a.back() == '0')
            a.pop_back();
        while (b.size() && b.back() == '0')
            b.pop_back();
        reverse(all(a));
        reverse(all(b));
        if (a.length() == b.length())
        {
            if (a == b)
            {
                cout << "=";
            }
            else if (a < b)
                cout << "<";
            else
                cout << ">";
        }
        else if (a.length() < b.length())
            cout << "<";
        else
            cout << ">";
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
