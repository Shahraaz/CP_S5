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
    for (auto &x : a)
        cin >> x;
    set<int> ss;
    a.back()++;
    ss.insert(a.back());
    for (int i = n - 2; i >= 0; i--)
    {
        if (ss.count(a[i] + 1) == 0)
        {
            ++a[i];
            ss.insert(a[i]);
        }
        else
        {
            ss.insert(a[i]);
        }
    }
    cout << ss.size() << '\n';
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