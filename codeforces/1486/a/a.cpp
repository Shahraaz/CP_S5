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
    for (size_t i = 0; i < n; i++)
        cin >> a[i];
    ll carry = 0;
    for (int i = 0; i < n; i++)
    {
        db(i, a[i], carry);
        if (i > a[i])
        {
            if (carry >= abs(i - a[i]))
                carry -= abs(i - a[i]);
            else
            {
                cout << "NO\n";
                return;
            }
        }
        else
            carry += abs(i - a[i]);
    }
    cout << "YES\n";
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