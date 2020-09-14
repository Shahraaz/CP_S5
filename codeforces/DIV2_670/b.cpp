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
    vector<ll> pos, neg;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (x < 0)
            neg.pb(-x);
        else
            pos.pb(x);
    }
    ll res = LLONG_MIN;
    sort(all(pos));
    sort(all(neg));
    auto revPos = pos;
    auto revNeg = neg;
    reverse(all(revPos));
    reverse(all(revNeg));
    for (int negCnt = 0; negCnt <= 5; negCnt++)
    {
        ll temp = 1;
        int posCnt = 5 - negCnt;
        if (negCnt > neg.size() || posCnt > pos.size())
            continue;
        if (negCnt & 1)
        {
            for (size_t i = 0; i < negCnt; i++)
                temp *= neg[i];
            for (size_t i = 0; i < posCnt; i++)
                temp *= pos[i];
            temp = -temp;
        }
        else
        {
            for (size_t i = 0; i < negCnt; i++)
                temp *= revNeg[i];
            for (size_t i = 0; i < posCnt; i++)
                temp *= revPos[i];
            // temp = -temp;
        }
        db(negCnt, temp);
        res = max(res, temp);
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
