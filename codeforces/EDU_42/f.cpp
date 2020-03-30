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
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        bool isInside = false;
        int n;
        cin >> n;
        vector<pair<int, int>> polygon;
        int prevExit = false, cntOutside = 0;
        for (size_t i = 0; i < n; i++)
        {
            int x, y;
            cin >> x >> y;
            polygon.pb({x, y});
            cntOutside += !(x1 < x && x < x2 && y1 < y && y < y2);
        }
        if (cntOutside == 0)
        {
            cout << 1 << '\n';
            return;
        }
        if (cntOutside == n)
        {
            cout << 0 << '\n';
            return;
        }
        for (size_t i = 0; i < n; i++)
        {
            int x = polygon[i].f, y = polygon[i].s;
            if (!(x1 < x && x < x2 && y1 < y && y < y2))
            {
                int j = i, res = 0;
                bool isOutSide = true;
                for (size_t j = 0; j < n; j++)
                {
                    if (!isOutSide && !(x1 < x && x < x2 && y1 < y && y < y2))
                    {
                        res++;
                        isOutSide = true;
                    }
                    else
                        isOutSide = false;
                }
                cout << isOutSide << '\n';
                break;
            }
        }
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