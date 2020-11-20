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
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n = 8 * 8 * 8 + 16;
    cout << n << '\n';
    vector<vector<string>> vecc;
    for (size_t i = 0; i < 8 * 8 * 8; i++)
    {
        int k = i % 8;
        cout << 3 << ' ' << 3 << '\n';
        cout << bitset<3>(k) << '\n';
        int i1 = i / 8;
        k = i1 % 8;
        cout << bitset<3>(k) << '\n';
        i1 = i1 / 8;
        k = i1 % 8;
        cout << bitset<3>(k) << '\n';
    }
    for (size_t i = 0; i < 4 * 4; i++)
    {
        int k = i % 4;
        cout << 2 << ' ' << 2 << '\n';
        cout << bitset<2>(k) << '\n';
        int i1 = i / 4;
        cout << bitset<2>(i1) << '\n';
    }
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