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
    vector<int> a(n), b(n);
    for (auto &x : a)
        cin >> x;
    for (auto &x : b)
        cin >> x;
    int prev = 0;
    db(a);
    db(b);
    for (size_t i = 0; i < n; i++)
    {
        int d = b[i] - a[i];
        if (d < 0)
        {
            cout << "NO\n";
            return;
        }
        if (d > 0)
        {
            if (prev == 0)
                prev = d;
            else if (prev != d)
            {
                cout << "NO\n";
                return;
            }
        }
        b[i] = d;
    }
    int cnt = count(all(b), prev);
    db(prev, cnt);
    db(b);
    if (prev == 0)
    {
        cout << "YES\n";
        return;
    }
    for (size_t i = 0; i < n; i++)
    {
        if (b[i] == prev)
        {
            int j = i;
            while (cnt && j < n && b[j] == prev)
            {
                ++j, --cnt;
            }
            if (cnt == 0)
            {
                cout << "YES\n";
                return;
            }
            else
            {

                cout << "NO\n";
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