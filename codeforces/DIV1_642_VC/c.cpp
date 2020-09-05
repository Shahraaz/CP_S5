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

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    int n, m;
    cin >> n >> m;
    ll x, y, k;
    cin >> x >> k >> y;
    vector<int> posInA(n, -1);
    vector<int> poses(n, 1);
    vector<int> posInB(n, -1);
    vector<int> a(n), b(m);
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        a[i]--;
        posInA[a[i]] = i;
    }
    vector<int> myvec;
    for (size_t i = 0; i < m; i++)
    {
        cin >> b[i];
        b[i]--;
        if (posInA[b[i]] == -1)
        {
            cout << -1 << '\n';
            return;
        }
        else
        {
            myvec.pb(posInA[b[i]]);
            poses[posInA[b[i]]] = 0;
        }
        posInB[b[i]] = i;
    }
    db(poses);
    auto solve = [&](int cnt, int prev, int next, int maxi) -> ll {
        if (cnt < 1)
            return 0;
        ll ret = 0;
        if (cnt < k && maxi > (max(prev, next)))
        {
            cout << -1 << '\n';
            exit(0);
        }
        int rem = cnt % k;
        ret += rem * y;
        cnt -= rem;
        if (y * k >= x)
            ret += cnt / k * x;
        else if (maxi < (max(prev, next)))
        {
            ret += cnt * y;
        }
        else
            ret += (cnt - k) * y + x;
        return ret;
    };
    if (is_sorted(all(myvec)))
    {
        int cnt = 0;
        ll res = 0;
        ll prev = 0, next = 0;
        int maxi = 0;
        for (size_t i = 0; i < n; i++)
        {
            if (poses[i] == 0)
            {
                next = a[i];
                res += solve(cnt, prev, next, maxi);
                maxi = 0;
                cnt = 0;
                prev = next;
            }
            else
            {
                cnt++;
                maxi = max(maxi, a[i]);
            }
        }
        if (cnt)
            res += solve(cnt, prev, next, maxi);
        cout << res << '\n';
    }
    else
    {
        cout << -1 << '\n';
    }
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
