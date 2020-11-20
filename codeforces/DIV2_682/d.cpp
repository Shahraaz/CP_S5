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
    db(a);
    vector<vector<int>> Q;
    for (int i = 1; i + 1 < n; i += 2)
    {
        int temp = a[0] ^ a[i] ^ a[i + 1];
        a[0] = a[i] = a[i + 1] = temp;
        Q.pb({1, i + 1, i + 2});
    }
    db(a);
    for (int i = 1; i + 1 < n; i += 2)
    {
        int temp = a[0] ^ a[i] ^ a[i + 1];
        a[0] = a[i] = a[i + 1] = temp;
        Q.pb({1, i + 1, i + 2});
    }
    db(a);
    sort(all(a));
    a.resize(unique(all(a)) - a.begin());
    if (a.size() == 1)
    {
        cout << "YES\n";
        cout << Q.size() << '\n';
        for (auto &x : Q)
        {
            for (auto &y : x)
                cout << y << ' ';
            cout << '\n';
        }
    }
    else
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
    {
        solveCase();
#ifdef TIMER
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}