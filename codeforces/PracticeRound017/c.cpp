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
        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<ll>> a(n, vector<ll>(m));
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                cin >> a[i][j];
        vector<int> res(m);
        vector<multiset<int>> curr(m);
        int lptr = 0, rptr = 0, maxCnt = INT_MIN, currCount = 0;
        auto addNumber = [&](multiset<int> &s, int x) {
            s.insert(x);
        };
        auto removeNumber = [&](multiset<int> &s, int x) {
            auto it = s.find(x);
            if (it != s.end())
                s.erase(it);
        };
        auto getMax = [&](multiset<int> &s) {
            if (s.size())
                return *s.rbegin();
            return 0;
        };
        auto addIdx = [&](int idx, int sign) {
            // db(idx, sign, curr);
            for (size_t i = 0; i < m; i++)
            {
                switch (sign)
                {
                case 1:
                    currCount -= getMax(curr[i]);
                    addNumber(curr[i], a[idx][i]);
                    currCount += getMax(curr[i]);
                    break;

                case -1:
                    currCount -= getMax(curr[i]);
                    removeNumber(curr[i], a[idx][i]);
                    currCount += getMax(curr[i]);
                    break;
                default:
                    break;
                }
            }
            // db(curr);
        };
        vector<bool> added(n);
        while (lptr < n)
        {
            rptr = max(lptr, rptr);
            while (rptr < n)
            {
                if (!added[rptr])
                {
                    added[rptr] = true;
                    addIdx(rptr, 1);
                }
                if (currCount > k)
                {
                    added[rptr] = false;
                    addIdx(rptr, -1);
                    rptr--;
                    break;
                }
                rptr++;
            }
            if (rptr == n)
                rptr = n - 1;
            if (maxCnt < rptr - lptr + 1)
            {
                for (size_t i = 0; i < m; i++)
                    res[i] = getMax(curr[i]);
                maxCnt = rptr - lptr + 1;
            }
            db(lptr, rptr, currCount, curr);
            addIdx(lptr, -1);
            ++lptr;
        }
        for (auto &x : res)
            cout << x << ' ';
        cout << '\n';
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
