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
    for (size_t i = 0; i < n; i++)
        cin >> a[i];
    string posssss;
    cin >> posssss;
    for (size_t i = 0; i < n; i++)
    {
        if (i < posssss.size() && posssss[i] == '0')
        {
            if (a[i] != (i + 1))
            {
                cout << "NO\n";
                return;
            }
        }
        else
        {
            int l = i;
            int r = i;
            vector<int> toCheck;
            while (r < posssss.size() && posssss[r] == '1')
                ++r;
            for (size_t j = l; j <= r; j++)
                toCheck.pb(a[j]);
            sort(all(toCheck));
            db(posssss);
            db(i, l, r, toCheck);
            if (toCheck.front() == (l + 1) && toCheck.back() == (r + 1))
            {
                i = r;
            }
            else
            {
                cout << "NO\n";
                return;
            }
        }
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
