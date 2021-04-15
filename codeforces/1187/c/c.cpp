#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
const int NAX = 2e5 + 5, MOD = 100000007;

void solveCase()
{
    int n, m;
    cin >> n >> m;
    vector<int> l(m), r(m), t(m);
    vector<int> ok(n + 1), ok2(n + 1);
    for (size_t i = 0; i < m; i++)
    {
        cin >> t[i] >> l[i] >> r[i];
        if (t[i] == 1)
        {
            ok[r[i]]--;
            ok[l[i]]++;
        }
    }
    vector<int> arr(n + 1, -1), dx(n + 1, -1);
    arr[0] = MOD;
    for (size_t i = 1; i < n; i++)
    {
        ok[i] += ok[i - 1];
        if (ok[i])
            dx[i] = 0;
        db(i, ok[i], dx[i]);
    }
    for (size_t i = 1; i <= n; i++)
        arr[i] = dx[i - 1] + arr[i - 1];

    db(arr);
    vector<int> nexxt(n + 1, n);
    for (int i = n - 1; i >= 1; i--)
    {
        if (arr[i] <= arr[i + 1])
            nexxt[i] = nexxt[i + 1];
        else
            nexxt[i] = i;
        db(i, nexxt[i]);
    }
    for (size_t i = 0; i < m; i++)
    {
        db(i, l[i], r[i], t[i], nexxt[l[i]], r[i]);
        if (t[i] != (nexxt[l[i]] >= r[i]))
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    for (size_t i = 1; i <= n; i++)
    {
        cout << arr[i] << ' ';
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}