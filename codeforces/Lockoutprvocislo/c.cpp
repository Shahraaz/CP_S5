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

void Solution::solveCase()
{
    int n, k, p, sum, y;
    cin >> n >> k >> p >> sum >> y;
    db(n, k, p, sum, y);
#define ordered_set tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>
    ordered_set myset;
    vector<int> vecc[p + 1];
    for (size_t i = 0; i < k; i++)
    {
        int x;
        cin >> x;
        sum -= x;
        myset.insert({x, i});
        vecc[x].pb(i);
    }
    int lsize = n / 2 + 1;
    int rsize = n / 2;
    for (size_t i = k; i < n; i++)
    {
        myset.insert({1, i});
        sum -= 1;
    }
    for (size_t i = 0; i <= (n - k); i++)
    {
        auto it = myset.find_by_order(lsize - 1);
        // for (auto &x : myset)
        // {
        //     cout << x.f << ' ' << x.s << " , ";
        // }
        // cout << '\n';
        // cout << it->f << ' ' << it->s << '\n';
        // db(sum);
        if (it->f >= y && sum >= 0)
        {
            for (size_t j = i; j < (n - k); j++)
                cout << 1 << ' ';
            for (size_t j = 0; j < i; j++)
            {
                cout << y << ' ';
            }
            return;
        }
        int idx = i + k;
        myset.erase({1, idx});
        sum++;
        sum -= y;
        myset.insert({y, idx});
    }
    cout << -1 << '\n';
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
