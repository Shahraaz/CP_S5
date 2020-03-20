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

struct point
{
    int x, y, z;
    point(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
};

class Solution
{
private:
    int n;

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n;
        vector<vector<int>> points(n, vector<int>(3));
        for (auto &elem : points)
            for (auto &ord : elem)
                cin >> ord;
        function<int(int, vector<int>)> Solve = [&Solve, &points](int idx, vector<int> ids) {
            if (idx == 3)
                return ids[0];
            map<int, vector<int>> mp;
            for (auto &x : ids)
                mp[points[x][idx]].pb(x);
            vector<int> a;
            for (auto &q : mp)
            {
                int cur = Solve(idx + 1, q.s);
                if (cur != -1)
                    a.pb(cur);
            }
            for (size_t i = 0; i + 1 < a.size(); i += 2)
                cout << a[i] + 1 << ' ' << a[i + 1] + 1 << '\n';
            return a.size() % 2 == 1 ? a.back() : -1;
        };
        vector<int> t(n);
        iota(all(t), 0);
        Solve(0, t);
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