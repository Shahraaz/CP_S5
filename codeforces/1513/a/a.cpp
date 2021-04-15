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
    int n, k;
    cin >> n >> k;
    deque<int> dQ;
    for (size_t i = 0; i < n; i++)
        dQ.pb(i + 1);
    vector<int> res;
    res.pb(1);
    dQ.pop_front();
    while (k--)
    {
        if (dQ.empty())
        {
            cout << -1 << '\n';
            return;
        }
        res.pb(dQ.back());
        dQ.pop_back();
        if (dQ.empty())
        {
            cout << -1 << '\n';
            return;
        }
        res.pb(dQ.front());
        dQ.pop_front();
    }
    for (auto &x : res)
    {
        cout << x << ' ';
    }
    for (auto &x : dQ)
    {
        cout << x << ' ';
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