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
    void solveCase();
};

void Solution::solveCase()
{
    int n;
    cin >> n;
    ll minVal, maxVal;
    minVal = -2e9;
    maxVal = 2e9;
    for (size_t i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        ll x;
        cin >> x;
        string eval;
        cin >> eval;
        db(s, x, eval);
        s[0] = '<' - s[0] + '>';
        if (s == ">")
        {
            if (eval == "Y")
                maxVal = min(maxVal, x - 1);
            else
                minVal = max(minVal, x);
        }
        else if (s == "<")
        {
            if (eval == "Y")
                minVal = max(minVal, x + 1);
            else
                maxVal = min(maxVal, x);
        }
        else if (s == ">=")
        {
            x++;
            if (eval == "Y")
                maxVal = min(maxVal, x - 1);
            else
                minVal = max(minVal, x);
        }
        else if (s == "<=")
        {
            x--;
            if (eval == "Y")
                minVal = max(minVal, x + 1);
            else
                maxVal = min(maxVal, x);
        }
        db(minVal, maxVal);
    }
    if (minVal <= maxVal)
        cout << minVal << '\n';
    else
    {
        cout << "Impossible" << '\n';
    }
}

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
