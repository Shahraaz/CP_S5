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
        int n = 10, m = 10;
        vector<vector<int>> vec(n, vector<int>(m));
        int ctr = 1;
        for (size_t i = 0; i < 20; i++)
        {
            int x = 0, y = i;
            while (y >= 0)
            {
                if (0 <= x && x < 10 && 0 <= y && y < 10)
                    vec[x][y] = ctr++;
                x++,
                    y--;
            }
        }
        db(vec);
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x2 -= x1, y2 -= y1;
        if (x1 == 0 || y1 == 0)
            cout << 1 << '\n';
        else
        {
            
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
