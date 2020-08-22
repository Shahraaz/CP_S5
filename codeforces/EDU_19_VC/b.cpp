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
    vector<int> subseq[2];
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        subseq[abs(x) % 2].pb(x);
    }
    sort(all(subseq[0]));
    sort(all(subseq[1]));
    reverse(all(subseq[1]));
    ll sum = 0;
    for (auto &x : subseq[0])
        if (x >= 0)
            sum += x;
    // int sum = 0;
    ll maxSum =LLONG_MIN;
    for (size_t i = 0; i < subseq[1].size(); i++)
    {
        sum += subseq[1][i];
        if (sum & 1)
            maxSum = max(maxSum, sum);
    }
    cout << maxSum << '\n';
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
