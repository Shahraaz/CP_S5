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
    int n, x;
    cin >> n >> x;
    vector<ll> a(n);
    for (auto &x : a)
        cin >> x;
    a[0] %= x;
    for (size_t i = 1; i < n; i++)
    {
        a[i] += a[i - 1];
        a[i] %= x;
    }
    db(a);
    map<int, int> farthest;
    set<int> vis;
    int res = -1;
    for (int i = n - 1; i >= 0; i--)
    {
        db(i, a[i], farthest[a[i]]);
        db(farthest);
        if (farthest.size())
        {
            auto it = farthest.end();
            if (it != farthest.begin())
            {
                --it;
                if (it->second != a[i])
                    res = max(res, it->first - i);
            }
            if (it != farthest.begin())
            {
                --it;
                if (it->second != a[i])
                    res = max(res, it->first - i);
            }
        }
        if (vis.count(a[i]) == 0)
        {
            farthest[i] = a[i];
            vis.insert(a[i]);
        }
    }
    if (farthest.size())
    {
        auto it = farthest.end();
        if (it != farthest.begin())
        {
            --it;
            if (it->second != 0)
                res = max(res, it->first + 1);
        }
        if (it != farthest.begin())
        {
            --it;
            if (it->second != 0)
                res = max(res, it->first + 1);
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
    cin >> t;
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