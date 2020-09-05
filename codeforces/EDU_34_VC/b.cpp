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
    int h1, a1, c1;
    int h2, a2;
    cin >> h1 >> a1 >> c1;
    cin >> h2 >> a2;
    vector<string> vecc;
    bool turn = 1;
    while (true)
    {
        if (turn)
        {
            if (h2 - a1 <= 0)
            {
                h2 -= a1;
                vecc.pb("STRIKE");
                break;
            }
            if (h1 - a2 > 0)
            {
                h2 -= a1;
                vecc.pb("STRIKE");
            }
            else
            {
                h1 += c1;
                vecc.pb("HEAL");
            }
        }
        else
        {
            h1 -= a2;
            if (h1 <= 0)
                break;
        }
        turn = !turn;
    }
    cout << vecc.size() << '\n';
    for (auto &x : vecc)
    {
        cout << x << '\n';
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
