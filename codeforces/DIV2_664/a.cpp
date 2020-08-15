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
        int r, b, g, w;
        cin >> r >> b >> g >> w;
        if (r % 2 == 0 && b % 2 == 0 && b % 2 == 0 && w % 2 == 0)
            cout << "Yes\n";
        else if (r % 2 == 0 && b % 2 == 0 && g % 2 == 0 && w % 2 == 1)
            cout << "Yes\n";
        else if (r % 2 == 0 && b % 2 == 0 && g % 2 == 1 && w % 2 == 0)
        {
            cout << "Yes\n";
        }
        else if (r % 2 == 0 && b % 2 == 1 && g % 2 == 0 && w % 2 == 0)
        {
            cout << "Yes\n";
        }
        else if (r % 2 == 1 && b % 2 == 0 && g % 2 == 0 && w % 2 == 0)
        {
            cout << "Yes\n";
        }
        else
        {
            if (r >= 1 && b >= 1 && g >= 1)
            {
                r--, b--, g--;
                w++;
                if (r % 2 == 0 && b % 2 == 0 && g % 2 == 0 && w % 2 == 0)
                    cout << "Yes\n";
                else if (r % 2 == 0 && b % 2 == 0 && g % 2 == 0 && w % 2 == 1)
                    cout << "Yes\n";
                else if (r % 2 == 0 && b % 2 == 0 && g % 2 == 1 && w % 2 == 0)
                {
                    cout << "Yes\n";
                }
                else if (r % 2 == 0 && b % 2 == 1 && g % 2 == 0 && w % 2 == 0)
                {
                    cout << "Yes\n";
                }
                else if (r % 2 == 1 && b % 2 == 0 && g % 2 == 0 && w % 2 == 0)
                {
                    cout << "Yes\n";
                }
                else
                    cout << "No\n";
            }
            else
                cout << "No\n";
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
