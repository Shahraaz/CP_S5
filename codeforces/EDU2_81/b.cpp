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
        string str;
        cin >> str;
        vector<int> nextOne, nextTwo, nextThree;
        nextOne.pb(MOD);
        nextTwo.pb(MOD);
        nextThree.pb(MOD);
        for (int i = str.size() - 1; i >= 0; i--)
        {
            int a, b, c;
            a = nextOne.back();
            b = nextTwo.back();
            c = nextThree.back();
            nextOne.pb(a);
            nextTwo.pb(b);
            nextThree.pb(c);
            switch (str[i])
            {
            case '1':
                nextOne.back() = i;
                break;
            case '2':
                nextTwo.back() = i;
                break;
            case '3':
                nextThree.back() = i;
                break;
            default:
                break;
            }
        }
        reverse(all(nextOne));
        reverse(all(nextTwo));
        reverse(all(nextThree));
        // db(nextOne, nextTwo, nextThree) 
        int res = MOD;
        for (int i = 0; i < nextOne.size(); i++)
        {
            res = min(res, max({nextOne[i], nextTwo[i], nextThree[i]}) - i);
        }
        if (res >= str.size())
            res = 0;
        else res++;
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
