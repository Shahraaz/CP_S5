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
        string str;
        cin >> str;
        auto removePre = [&](string s) {
            reverse(all(s));
            while (s.size() && s.back() == '0')
                s.pop_back();
            reverse(all(s));
            return s;
        };
        auto removePost = [&](string s) {
            while (s.size() && s.back() == '0')
                s.pop_back();
            return s;
        };
        if (count(all(str), '.') == 0)
            str += '.';
        str = removePost(str);
        str = removePre(str);
        if (str.size() == 0)
        {
            cout << 0 << '\n';
            return;
        }
        bool decSeen = false;
        string beforeDec;
        string afterDec;
        for (auto &x : str)
        {
            if (x == '.')
            {
                decSeen = true;
            }
            else
            {
                if (decSeen)
                    afterDec += x;
                else
                    beforeDec += x;
            }
        }
        int E = 0;
        auto transfer = [&]() {
            reverse(all(afterDec));
            if (beforeDec.size() == 0)
            {
                while (afterDec.size() && afterDec.back() == '0')
                {
                    E--;
                    afterDec.pop_back();
                }
                if (afterDec.size())
                {
                    E--;
                    beforeDec += afterDec.back();
                    afterDec.pop_back();
                }
            }
            else
            {
                while (beforeDec.size() > 1)
                {
                    afterDec += beforeDec.back();
                    beforeDec.pop_back();
                    E++;
                }
            }
            reverse(all(afterDec));
        };
        transfer();
        afterDec = removePost(afterDec);
        beforeDec = removePre(beforeDec);
        if (beforeDec.size() == 0)
            beforeDec += '0';
        cout << beforeDec;
        if (afterDec.size())
            cout << "." << afterDec;
        if (E != 0)
            cout << "E" << E;
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
