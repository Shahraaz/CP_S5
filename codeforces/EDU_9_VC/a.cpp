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
        int n, p;
        cin >> n >> p;
        ll ans = 0;
        ll currAppleCnt = 0;
        stack<string> st;
        for (size_t i = 0; i < n; i++)
        {
            string str;
            cin >> str;
            st.push(str);
            // auto temp = currAppleCnt;
            // if (str == "halfplus")
            //     temp += 0.5;
            // ans += temp * p;
        }
        while (st.size())
        {
            long double temp = currAppleCnt;
            if (st.top() == "halfplus")
                temp += 0.5;
            ans += temp * p;
            currAppleCnt = (2 * currAppleCnt);
            if (st.top() == "halfplus")
                currAppleCnt++;
            db(currAppleCnt);
            st.pop();
        }
        cout << ans << '\n';
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
