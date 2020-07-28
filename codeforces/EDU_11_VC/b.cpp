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
        int n, m;
        cin >> n >> m;
        vector<deque<int>> left(n), right(n);
        int ctr = 0;
        for (size_t i = 0; i < m; i++)
        {
            int idx = ctr / 2;
            if (ctr < 2 * n)
            {
                if (left[idx].size() == 0)
                {
                    left[idx].push_back(i);
                }
                else
                {
                    right[idx].push_front(i);
                }
            }
            else
            {
                idx -= n;
                if (left[idx].size() == right[idx].size())
                {
                    left[idx].push_back(i);
                }
                else
                {
                    right[idx].push_front(i);
                }
            }
            ctr++;
        }
        db(left, right);
        // ctr = 0;
        for (size_t i = 0; i < n; i++)
        {
            while (left[i].size())
            {
                cout << left[i].back() + 1 << ' ';
                left[i].pop_back();
            }
            while (right[i].size())
            {
                cout << right[i].front() + 1 << ' ';
                right[i].pop_front();
            }
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
