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
    int n, m;
    cin >> n >> m;
    using ld = long double;
    vector<ld> probs;
    vector<int> a(n);
    for (auto &x : a)
    {
        cin >> x;
        --x;
    }
    int pos = n - 1;
    while (pos >= 0 && a[pos] == pos)
        --pos;
    for (size_t i = 0; i < m; i++)
    {
        int r;
        ld p;
        cin >> r >> p;
        --r;
        if (pos <= r)
            probs.pb(p);
    }

    if (pos == -1)
    {
        cout << "1.0000000000" << '\n';
        return;
    }
    if (probs.size() == 0)
    {
        cout << "0.0000000000" << '\n';
        return;
    }
    ld tail = 1;
    for (auto &x : probs)
        tail *= 1 - x;
    cout << fixed << setprecision(10);
    cout << 1 - tail << '\n';
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
        solveCase();
    return 0;
}