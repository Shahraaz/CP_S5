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
    deque<pair<int, int>> left, right;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        right.pb({x, i});
    }
    auto maxi = *max_element(all(right));
    int val = maxi.f;
    for (int i = 0; i < n; i++)
    {
        if (right[i].f == val)
        {
            if (i + 1 < n)
                if (right[i + 1].f != val)
                {
                    cout << i + 1 << '\n';
                    return;
                }
            if (i - 1 >= 0)
                if (right[i - 1].f != val)
                {
                    cout << i + 1 << '\n';
                    return;
                }
        }
    }
    cout << -1 << '\n';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
