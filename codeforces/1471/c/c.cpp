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
    vector<int> k(n);
    for (auto &x : k)
    {
        cin >> x;
        --x;
    }
    vector<int> c(m);
    for (auto &x : c)
        cin >> x;
    sort(all(k));
    reverse(all(k));
    int lptr = 0, ptr = 0;
    ll res = 0;
    db(n, m);
    db(c);
    db(k);
    while (ptr < n)
    {
        if (lptr < k[ptr])
        {
            res += c[lptr];
            ++lptr;
        }
        else
        {
            res += c[k[ptr]];
        }
        ++ptr;
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
        solveCase();
    return 0;
}