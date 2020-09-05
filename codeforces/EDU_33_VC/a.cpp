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
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    for (int i = 1; i <= 1; i++)
    {
        for (int j = 2; j <= 2; j++)
        {
            set<int> ss = {i, j};
            int sum = i + j;
            bool ok = true;
            for (auto &x : a)
            {
                db(ss, x);
                if (ss.count(x))
                {
                    ss.erase(sum - x);
                    int loser = sum - x;
                    sum = 6 - loser;
                    ss.insert(6 - x - loser);
                }
                else
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
            {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
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
