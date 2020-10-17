// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> diff;
    int one;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        if (i > 0)
            diff.pb(a[i] - a[i - 1]);
        else
            one = a[i];
    }
    vector<int> diff2;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        if (i > 0)
            diff2.pb(a[i] - a[i - 1]);
        else if (one != a[i])
        {
            cout << "No\n";
            return;
        }
    }
    sort(all(diff));
    sort(all(diff2));
    if (diff == diff2)
        cout << "Yes\n";
    else
        cout << "No\n";
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
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
