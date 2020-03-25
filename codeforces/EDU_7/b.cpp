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
        ll hh, mm, a;
        string str;
        cin >> str;
        hh = (str[0] - '0') * 10 + str[1] - '0';
        mm = (str[3] - '0') * 10 + str[4] - '0';
        // cin >> hh >> mm >> a;
        cin >> a;
        ll minCnt = hh * 60 + mm;
        minCnt += a;
        ll dayHrCnt = 24 * 60;
        minCnt %= dayHrCnt;
        hh = minCnt / 60;
        mm = minCnt % 60;

        if (hh == 0)
            cout << "00";
        else if (hh < 10)
            cout << 0 << hh;
        else
            cout << hh;
        cout << ":";
        if (mm == 0)
            cout << "00";
        else if (mm < 10)
            cout << 0 << mm;
        else
            cout << mm;
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