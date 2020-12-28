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
    ll sum = 0;
    for (auto &x : a)
    {
        cin >> x;
        sum += x;
    }
    auto b = a;
    bool prev = 0;
    ll diff = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (b[i] > 1)
        {
            if (prev)
                b[i] = 2;
            else if (b[i] & 1)
                b[i]--;
            prev = !prev;
        }
        diff += abs(a[i] - b[i]);
    }
    if (2 * diff <= sum)
    {
        for (auto &x : b)
            cout << x << ' ';
        cout << '\n';
        return;
    }
    b = a;
    prev = 1;
    diff = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (b[i] > 1)
        {
            if (prev)
                b[i] = 2;
            else if (b[i] & 1)
                b[i]--;
            prev = !prev;
        }
        diff += abs(a[i] - b[i]);
    }
    if (2 * diff <= sum)
    {
        for (auto &x : b)
            cout << x << ' ';
        cout << '\n';
        return;
    }
    assert(false);
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