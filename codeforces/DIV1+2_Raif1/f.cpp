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

const int NAX = 5e5 + 5, MOD = 1000000007;

ll hist[NAX];

void solveCase()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = '$' + s;
    ll res = 0, curr = 0;
    for (size_t i = 1; i <= n; i++)
    {
        if (s[i] == '0')
            res += curr;
        else
        {
            int l = i, r = i;
            while (r < n && s[r + 1] == '1')
                ++r;
            for (int x = 1; x <= (r - l + 1); x++)
            {
                curr += (l - 1 + x) - hist[x];
                res += curr;
                hist[x] = r - x + 1;
            }
            i = r;
        }
    }
    cout << res << '\n';
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
