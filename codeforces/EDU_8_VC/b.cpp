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
        set<string> ss;
        for (size_t i = 0; i <= 100; i += 4)
        {
            auto I = to_string(i);
            ss.insert(I);
            if (i < 10)
            {
                I = "0" + I;
                ss.insert(I);
            }
        }
        string str;
        cin >> str;
        char prev = '\0';
        ll res = 0;
        db(ss);
        for (size_t i = 0; i < str.size(); i++)
        {
            string curr = "";
            curr += str[i];
            if (ss.count(curr))
                res++;
            if (i > 0)
            {
                curr = prev + curr;
                if (ss.count(curr))
                    res += i;
            }
            db(i, curr, res);
            prev = str[i];
        }
        cout << res << '\n';
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
