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
    vector<int> a(n + 2);
    for (size_t i = 1; i <= n; i++)
        cin >> a[i];
    vector<ll> fr(n + 2), ba(n + 2);
    vector<ll> dfr(n + 2, 1), dba(n + 2, 1);
    for (int i = 1; i <= n; i++)
    {
        fr[i] = a[i];
        fr[i] -= fr[i - 1];
        dfr[i] = dfr[i - 1] && (fr[i] >= 0);
    }
    for (int i = n; i >= 1; i--)
    {
        ba[i] = a[i];
        ba[i] -= ba[i + 1];
        dba[i] = dba[i + 1] && (ba[i] >= 0);
    }
    if (dfr[n] && fr[n] == 0)
    {
        cout << "YES\n";
        return;
    }
    for (int i = 1; i + 1 <= n; i++)
    {
        vector<ll> temp;
        if (dfr[i - 1] && dba[i + 2])
        {
            temp.pb(fr[i - 1]);
            temp.pb(a[i]);
            temp.pb(a[i + 1]);
            temp.pb(ba[i + 1]);
            bool ok = true;
            for (size_t i = 1; i < 4; i++)
            {
                temp[i] -= temp[i - 1];
                ok = ok && (temp[i] >= 0);
            }
            if (ok && temp[3] == 0)
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
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}