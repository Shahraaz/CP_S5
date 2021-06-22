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
    vector<int> a(4);
    for (auto &x : a)
        cin >> x;
    auto b = a;
    sort(all(a));
    b[0] = max(b[0], b[1]);
    b[1] = max(b[2], b[3]);
    if (b[0] > b[1])
        swap(b[0], b[1]);
    if (a[2] == b[0] && a[3] == b[1])
        cout << "YES\n";
    else
        cout << "NO\n";
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}