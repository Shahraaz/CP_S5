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
    vector<int> a(n);
    set<int> ss;
    for (auto &x : a)
    {
        cin >> x;
        ss.insert(x);
    }
    if (*ss.begin() < 0)
    {
        cout << "NO\n";
        return;
    }
    // sort(all(a));
    cout << "YES\n";
    cout << 101 << '\n';
    for (size_t i = 0; i <= 100; i++)
        cout << i << ' ';
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