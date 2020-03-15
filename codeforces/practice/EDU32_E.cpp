//https://codeforces.com/contest/888/problem/E
// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#define pc(...)
#endif

#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

class Solution
{
private:
    int n, m, res;
    vector<int> a;
    vector<int> firstHalf;
    int add(int a, int b)
    {
        return ((ll)a + b) % m;
    }
    void solve(int start, int end, bool type, int prevSum = 0)
    {
        db(start, end, type, prevSum);
        if (start > end)
        {
            res = max(res, prevSum);
            if (type && firstHalf.size())
            {
                int temp = (m - prevSum - 1);
                db(prevSum, temp);
                auto it = upper_bound(all(firstHalf), temp);
                if (it != firstHalf.begin())
                {
                    --it;
                    db(*it, temp, add(prevSum, *it));
                    res = max(res, add(prevSum, *it));
                }
            }
            else
                firstHalf.pb(prevSum);
            return;
        }
        solve(start + 1, end, type, add(prevSum, a[start]));
        solve(start + 1, end, type, prevSum);
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n >> m;
        a.resize(n);
        for (auto &x : a)
            cin >> x;
        res = 0;
        solve(0, n / 2, 0);
        sort(all(firstHalf));
        pc(firstHalf);
        firstHalf.pb(MOD);
        solve(n / 2 + 1, n - 1, 1);
        cout << res << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}