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

int n;
vector<int> a;

void solve()
{
    vector<char> res(n, '+');
    int low = 0;
    while (low <= n)
    {
        if (a[low] == '0')
            continue;
        int rptr = low;
        while (rptr <= n && a[rptr] > 0)
            rptr++;
        int l = low, r = rptr - 1;
        low = rptr;
        while (l <= r && a[l] == 1)
            ++l;
        while (l >= r && a[r] == 1)
            --r;
        if (l >= r)
            continue;
        
    }
    cout << a[0];
    for (size_t i = 1; i < n; i++)
        cout << res[i] << a[i];
    cout << '\n';
}

void solveCase()
{
    cin >> n;
    a.resize(n);
    for (auto &x : a)
        cin >> x;
    string str;
    cin >> str;
    if (str.size() == 1)
    {
        cout << a[0];
        for (size_t i = 1; i < n; i++)
            cout << str[0] << a[i];
        cout << '\n';
        return;
    }
    sort(all(str));
    if (str == "*+" || str == "*+-")
    {
        solve();
        return;
    }
    else if (str == "*-")
    {
        cout << a[0];
        bool ok = a[0] == 0;
        for (size_t i = 1; i < n; i++)
        {
            if (ok)
                cout << "*";
            else
            {
                if (a[i] == 0)
                {
                    cout << "-";
                    ok = true;
                }
                else if (a[i + 1] == 0)
                {
                    cout << "-";
                    ok = true;
                }
                else
                    cout << "*";
            }
            cout << a[i];
        }
        cout << '\n';
        return;
    }
    else if (str == "+-")
    {
        cout << a[0];
        for (size_t i = 1; i < n; i++)
        {
            cout << '+' << a[i];
        }
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}