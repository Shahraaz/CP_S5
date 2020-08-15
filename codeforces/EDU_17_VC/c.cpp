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
    vector<int> solve(string a, string b)
    {
        // swap(a, b);
        int n = a.size();
        vector<int> ret(n);
        // int ptr = 0;
        for (size_t i = 0; i < n; i++)
        {
            int x = 0, y = -1;
            if (i > 0)
            {
                x = ret[i - 1];
                // y = ret[i - 1].s;
            }
            if (x == b.size())
            {
                ret[i] = x;
                // ret[i].s = y;
            }
            else
            {
                if (a[i] == b[x])
                {
                    ret[i] = x + 1;
                    // ret[i].s = i;
                }
                else
                {
                    ret[i] = x;
                }
            }
        }
        return ret;
    }
    Solution() {}
    void solveCase()
    {
        string a, b;
        cin >> a >> b;
        auto forw = solve(a, b);
        reverse(all(a));
        reverse(all(b));
        auto back = solve(a, b);
        reverse(all(back));
        reverse(all(b));
        db(forw, back);
        int maxLen = forw.back(), maxforw = forw.back();
        for (size_t i = 0; i < a.size(); i++)
        {
            int len2 = back[i];
            int len1 = 0;
            if (i > 0)
                len1 = forw[i - 1];
            if (len1 + len2 > maxLen)
            {
                maxLen = len1 + len2;
                maxforw = len1;
            }
        }
        if (maxLen > b.size())
        {
            maxLen = b.size();
        }
        int backLen = maxLen - maxforw;
        cout << b.substr(0, maxforw);
        db('-');
        cout << b.substr(b.size() - backLen);
        if (maxLen == 0)
            cout << '-';
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
