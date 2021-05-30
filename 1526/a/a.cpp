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
    int n;
    cin >> n;
    vector<int> a(2 * n);
    for (auto &x : a)
        cin >> x;
    sort(all(a));
    int fptr = 0, rptr = n * 2 - 1;
    while (fptr <= rptr)
    {
        cout << a[fptr] << ' ';
        cout << a[rptr] << ' ';
        ++fptr;
        --rptr;
    }

    cout << '\n';
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