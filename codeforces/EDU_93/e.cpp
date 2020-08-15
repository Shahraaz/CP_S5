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

set<int> fire, elec;
set<int> big, small;
ll sum_all, sum_big;

void add_one(int x)
{
    if (big.empty() || x < *big.begin())
        small.insert(x);
    else
    {
        big.insert(x);
        sum_big += x;
    }
}

void remove_one(int x)
{
    if (small.count(x))
        small.erase(x);
    else
    {
        big.erase(x);
        sum_big -= x;
    }
}

void calc_ans()
{
    while (big.size() < elec.size())
    {
        auto x = *small.rbegin();
        small.erase(x);
        big.insert(x);
        sum_big += x;
    }
    while (big.size() > elec.size())
    {
        auto x = *big.begin();
        big.erase(x);
        small.insert(x);
        sum_big -= x;
    }
    ll ans = 0;
    ans += sum_all + sum_big;
    if (elec.size() > 0 && (fire.empty() || *fire.rbegin() < *elec.begin()))
    {
        ans -= *elec.begin();
        if (!fire.empty())
            ans += *fire.rbegin();
    }
    cout << ans << '\n';
}

void Solution::solveCase()
{
    int n;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        int t, d;
        cin >> t >> d;
        sum_all += d;
        if (d < 0)
        {
            d = -d;
            if (t == 0)
                fire.erase(d);
            else
                elec.erase(d);
            remove_one(d);
        }
        else
        {
            if (t == 0)
                fire.insert(d);
            else
                elec.insert(d);
            add_one(d);
        }
        calc_ans();
    }
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
