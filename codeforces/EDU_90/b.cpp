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

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        string s;
        cin >> s;
        string str = "";
        int moveCnt = 0;
        for (auto &x : s)
        {
            if (str.size())
            {
                if (x != str.back())
                {
                    str.pop_back();
                    moveCnt++;
                }
                else
                    str += x;
            }
            else
                str += x;
        }
        db(str, moveCnt);
#ifdef LOCAL
        cout << str.size() << ' ' << moveCnt << '\n';
#endif
        if (str.size())
        {
            if (moveCnt % 2 == 0)
                cout << "NET\n";
            else
                cout << "DA\n";
        }
        else
        {
            if (moveCnt % 2 == 0)
                cout << "NET\n";
            else
                cout << "DA\n";
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
