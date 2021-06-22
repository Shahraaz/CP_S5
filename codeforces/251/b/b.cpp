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
    vector<int> q(n), s(n);
    for (auto &x : q)
    {
        cin >> x;
        --x;
    }
    auto qinv = q;
    for (size_t i = 0; i < n; i++)
        qinv[q[i]] = i;
    db(q);
    db(qinv);
    for (auto &x : s)
    {
        cin >> x;
        --x;
    }
    vector<int> now;
    for (size_t i = 0; i < n; i++)
        now.pb(i);
    if (now == s)
    {
        cout << "NO\n";
        return;
    }
    int forward = 0;
    auto b = now;
    while (true)
    {
        vector<int> next(n);
        for (size_t i = 0; i < n; i++)
            next[i] = now[q[i]];
        if (next == s)
            break;
        forward++;
        if (forward == k)
            break;
        now = next;
    }
    int rev = 0;
    now = b;
    while (true)
    {
        vector<int> next(n);
        for (size_t i = 0; i < n; i++)
            next[i] = now[qinv[i]];
        if (next == s)
            break;
        rev++;
        if (rev == k)
            break;
        now = next;
    }
    db(forward, rev);
    if (forward == k && rev == k)
    {
        cout << "NO\n";
        return;
    }
    // if (forward != k)
    {
        if (rev > 0 || forward >= 1)
        {
            if ((forward & 1) != (k & 1))
            {
                cout << "YES\n";
                return;
            }
        }
        else
        {
            if (forward == k - 1)
            {
                cout << "YES\n";
                return;
            }
        }
    }
    // if (rev != k)
    {
        if (forward > 0 || rev >= 1)
        {
            if ((rev & 1) != (k & 1))
            {
                cout << "YES\n";
                return;
            }
        }
        else
        {
            if (rev == k - 1)
            {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
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