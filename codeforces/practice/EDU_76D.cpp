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
        int n;
        cin >> n;
        vector<int> monsterPower(n);
        for (auto &x : monsterPower)
            cin >> x;
        vector<int> maxPowerWithEnd(n + 2);
        int m;
        cin >> m;
        for (size_t i = 0; i < m; i++)
        {
            int powerHer, endurance;
            cin >> powerHer >> endurance;
            maxPowerWithEnd[endurance] = max(maxPowerWithEnd[endurance], powerHer);
        }
        for (int i = n - 1; i >= 0; i--)
            maxPowerWithEnd[i] = max(maxPowerWithEnd[i], maxPowerWithEnd[i + 1]);
        int res = 0, pos = 0;
        db(maxPowerWithEnd);
        while (pos < n)
        {
            ++res;
            int npos = pos, mx = 0;
            db(pos);
            while (npos < n)
            {
                mx = max(mx, monsterPower[npos]);
                db(npos, mx, maxPowerWithEnd[npos - pos + 1]);
                if (mx > maxPowerWithEnd[npos - pos + 1])
                    break;
                npos++;
            }
            if (pos == npos)
            {
                cout << -1 << '\n';
                return;
            }
            pos = npos;
        }
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
