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

const int NAX = 3e5 + 5, MOD = 1000000007;

ll a[NAX];
ll ans = 0;
int n;

void erase(int i)
{
    if (i < 1 || i > n)
        return;
    if (a[i - 1] < a[i] && a[i] > a[i + 1])
        ans -= a[i];
    if (a[i - 1] > a[i] && a[i] < a[i + 1])
        ans += a[i];
}

void insert(int i)
{
    if (i < 1 || i > n)
        return;
    if (a[i - 1] < a[i] && a[i] > a[i + 1])
        ans += a[i];
    if (a[i - 1] > a[i] && a[i] < a[i + 1])
        ans -= a[i];
}

void solveCase()
{
    int q;
    cin >> n;
    cin >> q;
    a[0] = a[n + 1] = -1;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i - 1] < a[i] && a[i] > a[i + 1])
            ans += a[i];
        if (a[i - 1] > a[i] && a[i] < a[i + 1])
            ans -= a[i];
    }
    cout << ans << '\n';
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        set<int> ss = {l - 1, l, l + 1, r - 1, r, r + 1};
        db(l, r, ss);
        for (auto &x : ss)
            erase(x);
        swap(a[l], a[r]);
        for (auto &x : ss)
            insert(x);
        cout << ans << '\n';
    }
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
