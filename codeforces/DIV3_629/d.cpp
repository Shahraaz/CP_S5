// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
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
        vector<int> v(2 * n);
        vector<int> clr(2 * n);
        for (size_t i = 0; i < n; i++)
        {
            cin >> v[i];
            v[i + n] = v[i];
        }
        int cnt = 0;
        clr[0] = 1;
        clr[n] = 1;
        for (size_t i = 1; i < n; i++)
        {
            int cc = 0;
            set<int> s;
            if (i - 1 >= 0)
                if (v[i] != v[i - 1])
                    s.insert(clr[i - 1]);
            if (clr[i + 1] > 0)
                if (v[i] != v[i + 1])
                    s.insert(clr[i + 1]);
            int ret = 1;
            while (s.count(ret))
                ++ret;
            clr[i] = clr[i + n] = ret;
        }
        cout << *max_element(all(clr)) << '\n';
        for (size_t i = 0; i < n; i++)
            cout << clr[i] << ' ';
        cout << '\n';
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