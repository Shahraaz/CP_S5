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
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x : a)
            cin >> x;
        vector<ll> prefSum(n + 1);
        vector<ll> maxRptr(n + 1);
        prefSum[0] = 0;
        map<ll, deque<int>> ms;
        for (size_t i = 1; i <= n; i++)
        {
            prefSum[i] = prefSum[i - 1] + a[i - 1];
            ms[prefSum[i]].pb(i);
        }
        ll res = 0;
        for (size_t i = 1; i <= n; i++)
        {
            if (ms[prefSum[i - 1]].size())
            {
                maxRptr[i] = ms[prefSum[i - 1]].front();
            }
            else
                maxRptr[i] = n + 1;
            ms[prefSum[i]].pop_front();
        }
        for (int i = n; i >= 1; i--)
        {
            if (i != n)
                maxRptr[i] = min(maxRptr[i], maxRptr[i + 1]);
            res += max(0LL, maxRptr[i] - i);
        }
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