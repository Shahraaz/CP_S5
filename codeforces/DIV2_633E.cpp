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

const int NAX = 5000 + 5, MOD = 1000000007;

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        set<int> S;
        int cnt = 100;
        vector<int> prev;
        vector<vector<int>> dx;
        while (cnt--)
        {
            for (int i = 1; i < NAX; i++)
            {
                if (S.count(i))
                    continue;
                for (int j = i + 1; j < NAX; j++)
                {
                    if (S.count(j))
                        continue;
                    for (int k = j + 1; k < NAX; k++)
                    {
                        if (S.count(k))
                            continue;
                        if ((i ^ j ^ k) == 0)
                        {
                            // cout << bitset<4>(i) << ' ' << bitset<4>(j) << ' ' << bitset<4>(k) << ' ';
                            cout << (i & 15) << ' ' << (j & 15) << ' ' << (k & 15) << '\n';
                            S.insert(i);
                            S.insert(j);
                            S.insert(k);
                            if (prev.size())
                                dx.pb({i - prev[0], j - prev[1], k - prev[2]});
                            prev = {i, j, k};
                            goto abcd;
                        }
                    }
                }
                // cout << '\n';
            }
        abcd:;
        }
        db(dx);
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
