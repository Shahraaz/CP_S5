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

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

// #define ordered_set tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>

void Solution::solveCase()
{
    int n;
    cin >> n;
    vector<int> h(n);
    vector<int> dp(n);
    vector<int> nextIdx[n];
    for (size_t i = 0; i < n; i++)
    {
        cin >> h[i];
        dp[i] = i;
    }
    vector<pair<int, int>> st;

    // prev Next greater
    db("prev Next greater");
    for (size_t i = 0; i < n; i++)
    {
        db(i, h[i], st);
        while (st.size() && st.back().f < h[i])
            st.pop_back();
        if (st.size())
            nextIdx[st.back().s].pb(i);
        st.pb({h[i], i});
    }
    st.clear();

    // prev Next Lower
    db("prev Next Lower");
    for (size_t i = 0; i < n; i++)
    {
        db(i, h[i], st);
        while (st.size() && st.back().f > h[i])
            st.pop_back();
        if (st.size())
            nextIdx[st.back().s].pb(i);
        st.pb({h[i], i});
    }
    st.clear();

    // prev Next greater
    db("prev Next greater");
    for (size_t i = 0; i < n; i++)
    {
        db(i, h[i], st);
        while (st.size() && st.back().f < h[i])
            st.pop_back();
        if (st.size())
            nextIdx[st.back().s].pb(i);
        st.pb({h[i], i});
    }
    st.clear();

    // Next Next Lower
    db("Next Next Lower");
    for (int i = n - 1; i >= 0; i--)
    {
        db(i, h[i], st);
        while (st.size() && st.back().f > h[i])
            st.pop_back();
        if (st.size())
            nextIdx[i].pb(st.back().s);
        st.pb({h[i], i});
    }
    st.clear();

    // Next Next greater
    db("Next Next greater");
    for (int i = n - 1; i >= 0; i--)
    {
        db(i, h[i], st);
        while (st.size() && st.back().f < h[i])
            st.pop_back();
        if (st.size())
            nextIdx[i].pb(st.back().s);
        st.pb({h[i], i});
    }
    st.clear();

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