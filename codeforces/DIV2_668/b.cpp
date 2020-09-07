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
    deque<int> pos, neg;
    vector<int> vecc;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        vecc.pb(x);
        if (x < 0)
            neg.pb(i);
        else
            pos.pb(i);
    }
    ll res = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (vecc[i] == 0)
            continue;
        if (vecc[i] > 0)
        {
            while (vecc[i] > 0 && neg.size())
            {
                auto idx = neg.front();
                int diff = min(-vecc[idx], vecc[i]);
                vecc[i] -= diff;
                vecc[idx] += diff;
                if (vecc[idx] == 0)
                    neg.pop_front();
            }
            if (vecc[i] > 0)
                res += vecc[i];
        }
        else
        {
            while (vecc[i] < 0 && pos.size())
            {
                auto idx = pos.back();
                int diff = min(vecc[idx], -vecc[i]);
                vecc[i] += diff;
                vecc[idx] -= diff;
                res += diff;
                if (vecc[idx] == 0)
                    pos.pop_back();
            }
            if (vecc[i] < 0)
                res -= vecc[i];
        }
    }
    cout << res << '\n';
}

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
