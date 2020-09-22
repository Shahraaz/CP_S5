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
    vector<int> res(n);
    for (auto &x : a)
        cin >> x;
    sort(all(a));
    int ans = 0, low = 0, high = n;
    auto check = [&](int num) -> bool {
        int rptr = (num, n - num - 1), rbndry = n;
        rptr = max(rptr, 0);
        int lptr = 0, lbndry = rptr;
        int i = 0;
        db(lptr, rptr, n, num);
        while (i < n)
        {
            if (i & 1)
            {
                if (lptr < lbndry)
                    res[i] = a[lptr++];
                else
                    res[i] = a[rptr++];
            }
            else
            {
                if (rptr < rbndry)
                    res[i] = a[rptr++];
                else
                    res[i] = a[lptr++];
            }
            ++i;
        }
        db(res);
        for (size_t i = 1; i + 1 < n; i += 1)
        {
            if (res[i - 1] > res[i] && res[i] < res[i + 1])
                num--;
        }
        db(num);
        return num <= 0;
    };
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (check(mid))
        {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    cout << ans << '\n';
    check(ans);
    for (auto &x : res)
    {
        cout << x << ' ';
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}