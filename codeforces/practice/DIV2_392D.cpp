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
        int BASE;
        string number;
        cin >> BASE >> number;
        ll ans = 0;
        ll f = 1;
        auto getNum = [&](int start, int End) -> ll {
            if (number[start] == '0')
            {
                if (start == End)
                    return 0;
                return -1;
            }
            ll res = 0;
            while (start <= End)
            {
                res = res * 10 + number[start] - '0';
                if (res >= BASE)
                    return -1;
                ++start;
            }
            return res;
        };
        for (int i = number.size() - 1; i >= 0; i--)
        {
            for (size_t j = 0; j <= i; j++)
            {
                ll x = getNum(j, i);
                db(j, i, x);
                if (x != -1)
                {
                    ans += f * x;
                    f *= BASE;
                    i = j;
                    break;
                }
            }
        }
        cout << ans << '\n';
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