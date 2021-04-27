#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 1e6 + 5, MOD = 1000000007;

// struct Bit
// {
//     int size;
//     vector<int> table;
//     Bit(int size)
//     {
//         this->size = size;
//         table.resize(size);
//     }
//     void update(int i, int delta)
//     {
//         while (i < size)
//         {
//             table[i] = max(table[i], delta);
//             i = i | (1 + i);
//         }
//     }
//     int sum(int i)
//     {
//         int ret = 0;
//         while (i >= 0)
//         {
//             // ret += table[i];
//             ret = max(ret, table[i]);
//             i = (i & (i + 1)) - 1;
//         }
//         return ret;
//     }
//     int rangeSum(int i, int j)
//     {
//         if (i == 0)
//             return sum(j);
//         return sum(j) - sum(i - 1);
//     }
//     void print()
//     {
// #ifdef LOCAL
//         for (int i = 0; i < size; i++)
//             cout << rangeSum(i, i) << ' ';
//         cout << '\n';
// #else

// #endif
//     }
// };

int a[NAX], pref[NAX], suff[NAX];
vector<int> poses[NAX];

void solveCase()
{
    int n, x;
    cin >> n >> x;
    for (size_t i = 1; i <= n; i++)
    {
        cin >> a[i];
        poses[a[i]].pb(i);
    }
    int prevptr = MOD;
    suff[x + 1] = MOD;
    for (int i = x; i >= 1; i--)
    {
        if (poses[i].size())
        {
            if (poses[i].back() <= prevptr)
                prevptr = poses[i].front();
            else
                prevptr = -1;
        }
        suff[i] = prevptr;
        db(i, suff[i]);
    }
    prevptr = 0;
    for (size_t i = 1; i <= x; i++)
    {
        if (poses[i].size())
        {
            if (prevptr <= poses[i].front())
                prevptr = poses[i].back();
            else
                prevptr = MOD;
        }
        pref[i] = prevptr;
        db(i, pref[i]);
    }
    long long res = 0;
    for (int i = 1; i <= x; i++)
    {
        if (pref[i - 1] == MOD)
            continue;
        int low = i, high = x, ans = x + 1;
        while (low <= high)
        {
            auto mid = (low + high) / 2;
            if (pref[i - 1] <= suff[mid + 1])
            {
                ans = mid;
                high = mid - 1;
            }
            else
                low = mid + 1;
        }
        db(i, ans, pref[i - 1], suff[ans + 1]);
        if (pref[i - 1] <= suff[ans + 1])
            res += x + 1 - ans;
    }
    cout << res << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}