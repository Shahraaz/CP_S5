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
using ld = long double;
const ld step = 0.05;
struct pt
{
    ld x, y;
};

ld dist(pt a, pt b)
{
    return hypot(a.x - b.x, a.y - b.y);
}

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        ld a, r1, r2, r3;
        cin >> a >> r1 >> r2 >> r3;
        pt m1 = {0, 0};
        ld sqrt3 = sqrtl(3);
        pt m2 = {a / 2, a * sqrt3 / 2};
        pt m3 = {-a / 2, a * sqrt3 / 2};
        int res = 0;
        for (ld x = -a; x < 0; x += step)
            for (ld y = 0; y < (x + a) * sqrt3 && dist({x, y}, m1) < r1; y += step)
                if (dist({x, y}, m2) <= r2 && dist({x, y}, m3) <= r3)
                    res++;
        for (ld x = 0; x < a; x += step)
            for (ld y = 0; y < (-x + a) * sqrt3 && dist({x, y}, m1) < r1; y += step)
                if (dist({x, y}, m2) <= r2 && dist({x, y}, m3) <= r3)
                    res++;
        cout << fixed << setprecision(5);
        cout << res * step * step << '\n';
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
