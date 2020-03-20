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
        int n, k;
        cin >> n >> k;
        if (n == 1)
        {
            cout << 0 << ' ' << 0 << '\n';
            return;
        }
        multiset<pair<int, int>> mySet;
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            mySet.insert({x, i});
        }
        vector<pair<int, int>> res;
        while (k--)
        {
            pc(mySet);
            auto low = *mySet.begin();
            auto high = *mySet.rbegin();
            db(low, high);
            if (low.f == high.f || (low.f + 1) == high.f)
                break;
            res.pb({high.s, low.s});
            mySet.erase(mySet.find(low));
            mySet.erase(mySet.find(high));
            high.f--;
            low.f++;
            mySet.insert(high);
            mySet.insert(low);
            // res.pb(high);
        }
        pc(mySet);
        auto low = *mySet.begin();
        auto high = *mySet.rbegin();
        cout << high.f - low.f << ' ';
        cout << res.size() << '\n';
        for (auto &x : res)
            cout << x.f + 1 << ' ' << x.s + 1 << '\n';
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