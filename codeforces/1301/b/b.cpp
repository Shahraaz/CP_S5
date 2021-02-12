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
    vector<int> a, b(n);
    int prev = -1;
    int maxdiff = -1;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        b[i] = x;
    }
    for (int i = 0; i < n; i++)
    {
        int x = b[i];
        if (b[i] != -1 && ((i != 0 && b[i - 1] == -1) || ((i + 1) < n && b[i + 1] == -1)))
            a.pb(x);
        if (x != -1 && prev != -1)
            maxdiff = max(maxdiff, abs(x - prev));
        prev = x;
    }
    db(b);
    db(a);
    sort(all(a));
    if (a.empty())
    {
        cout << 0 << ' ' << 0 << '\n';
        return;
    }
    int mid = (a.front() + a.back()) / 2;
    int res = MOD;
    for (auto &x : {mid - 2, mid - 1, mid, mid + 1, mid + 2})
    {
        if (x >= 0)
        {
            int temp = max({maxdiff, abs(a.front() - x), abs(a.back() - x)});
            res = min(res, temp);
        }
    }
    for (auto &x : {mid - 2, mid - 1, mid, mid + 1, mid + 2})
    {
        if (x >= 0)
        {
            int temp = max({maxdiff, abs(a.front() - x), abs(a.back() - x)});
            // res = min(res, temp);
            if (res == temp)
            {
                cout << temp << ' ' << x << '\n';
                return;
            }
        }
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