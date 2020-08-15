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
        string s;
        cin >> s;
        vector<int> temp;
        char back = '\0';
        int len = 0;
        for (auto &x : s)
        {
            if (x == back)
                len++;
            else
            {
                if (back == '1')
                    temp.pb(len);
                len = 1;
                back = x;
            }
        }
        if (back == '1')
            temp.pb(len);
        sort(all(temp));
        reverse(all(temp));
        db(temp);
        int res = 0;
        for (size_t i = 0; i < temp.size(); i += 2)
        {
            res += temp[i];
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
