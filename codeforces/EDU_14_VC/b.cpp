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
        int n;
        string str;
        cin >> str;
        n = str.length();
        set<char> symmetric;
        symmetric.insert('A');
        symmetric.insert('H');
        symmetric.insert('I');
        symmetric.insert('M');
        symmetric.insert('O');
        symmetric.insert('o');
        symmetric.insert('T');
        symmetric.insert('U');
        symmetric.insert('V');
        symmetric.insert('v');
        symmetric.insert('W');
        symmetric.insert('w');
        symmetric.insert('X');
        symmetric.insert('x');
        symmetric.insert('Y');
        map<char, char> mirror;
        mirror['d'] = 'b';
        mirror['b'] = 'd';
        mirror['p'] = 'q';
        mirror['q'] = 'p';
        for (int i = 0; i < n; i++)
        {
            int rev = n - i - 1;
            if (mirror[str[i]] == str[rev])
                continue;
            if (str[i] != str[rev])
            {
                cout << "NIE\n";
                return;
            }
            if (symmetric.count(str[i]) == 0)
            {
                cout << "NIE\n";
                return;
            }
        }
        cout << "TAK\n";
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
