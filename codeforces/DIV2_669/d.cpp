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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>

void Solution::solveCase()
{
    int n;
    cin >> n;
    vector<int> h(n);
    vector<int> dp(n);
    ordered_set o;
    ordered_set o_neg;
    vector<int> nextIdx[n];
    for (size_t i = 0; i < n; i++)
    {
        cin >> h[i];
        o.insert({h[i], i});
        o_neg.insert({-h[i], i});
        dp[i] = i;
    }
    for (int i = 0; i < n; i++)
    {
        if (i + 1 < n)
            nextIdx[i].pb(i + 1);

        o.erase({h[i], i});
        auto it = o.lower_bound({h[i], 0});
        if (it != o.end())
            nextIdx[i].pb(it->s);

        o_neg.erase({-h[i], i});
        it = o_neg.lower_bound({-h[i], 0});
        if (it != o_neg.end())
            nextIdx[i].pb(it->s);
    }

    reverse(all(h));
    for (size_t i = 0; i < n; i++)
    {
        o.insert({h[i], i});
        o_neg.insert({-h[i], i});
    }
    for (int i = 0; i < n; i++)
    {
        o.erase({h[i], i});
        auto it = o.lower_bound({h[i], 0});
        if (it != o.end())
            nextIdx[n - 1 - it->s].pb(n - i - 1);

        o_neg.erase({-h[i], i});
        it = o_neg.lower_bound({-h[i], 0});
        if (it != o_neg.end())
            nextIdx[n - 1 - it->s].pb(n - i - 1);
    }
    for (size_t i = 0; i < n; i++)
    {
        db(i, nextIdx[i]);
        for (auto &x : nextIdx[i])
            dp[x] = min(dp[x], dp[i] + 1);
    }
    cout << dp.back() << '\n';
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