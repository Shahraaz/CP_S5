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
    char opposite(char c)
    {
        if (c == '{')
            return '}';
        if (c == '[')
            return ']';
        if (c == '<')
            return '>';
        if (c == '(')
            return ')';

        if (c == '}')
            return '{';
        if (c == ']')
            return '[';
        if (c == '>')
            return '<';
        if (c == ')')
            return '(';
        return c;
    }
    Solution() {}
    void solveCase()
    {
        string s;
        cin >> s;
        int n = s.length();
        vector<int> matchPos(n);
        stack<int> st;
        vector<char> opens = {'<', '{', '[', '('};
        for (size_t i = 0; i < n; i++)
        {
            if (count(all(opens), s[i]))
                st.push(i);
            else
            {
                if (st.size())
                {
                    matchPos[i] = st.top();
                    matchPos[st.top()] = i;
                    st.pop();
                }
                else
                {
                    cout << "Impossible\n";
                    return;
                }
            }
        }
        if (st.size())
            cout << "Impossible\n";
        else
        {
            db(matchPos);
            int ret = 0;
            for (size_t i = 0; i < n; i++)
            {
                db(i, matchPos[i], s[i], s[matchPos[i]]);
                ret += opposite(s[i]) != s[matchPos[i]];
            }
            cout << ret / 2 << '\n';
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
