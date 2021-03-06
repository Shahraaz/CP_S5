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
    vector<int> b(n);
    int ans = 0;
    for (auto &x : a)
        cin >> x;
    for (int bit = 0; bit < 29; bit++)
    {
        for (size_t i = 0; i < n; i++)
            b[i] = a[i] % (1 << (bit + 1));
        sort(all(b));
        int tot = 0;
        for (size_t i = 0; i < n; i++)
        {
            int x = lower_bound(all(b), (1 << bit) - b[i]) - b.begin();
            if (x <= i)
                tot--;
            tot += n - x;

            x = lower_bound(all(b), (1 << (bit + 1)) - b[i]) - b.begin();
            if (x <= i)
                tot++;
            tot -= n - x;

            x = lower_bound(all(b), (1 << (bit + 1)) + ((1 << bit)) - b[i]) - b.begin();
            if (x <= i)
                tot--;
            tot += n - x;
        }
        tot /= 2;
        if (tot & 1)
            ans |= (1 << bit);
    }
    cout << ans << '\n';
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
