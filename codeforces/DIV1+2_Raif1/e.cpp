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

ll cost(int len, int parts)
{
    int large = len % parts;
    int small = parts - large;
    ll smallCost = (len / parts) * 1LL * (len / parts);
    ll largeCost = (len / parts + 1) * 1LL * (len / parts + 1);
    db(len, parts);
    db(small, large);
    db(smallCost, largeCost);
    ll ret = smallCost * small + largeCost * large;
    db(ret);
    return ret;
}

void solveCase()
{
    int n, k;
    cin >> n >> k;
    k -= n;
    ll res = 0;
    priority_queue<pair<ll, pair<int, int>>> Q;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        res += x * 1LL * x;
        // db(x, i);
        // db(cost(x, 1) - cost(x, 2));
        Q.push({cost(x, 1) - cost(x, 2), {x, 1}});
    }
    while (k--)
    {
        auto top = Q.top();
        // db(res, top);
        Q.pop();
        res -= top.f;
        top.s.s++;
        // db(top);
        // db(cost(top.f, top.s.s) - cost(top.f, top.s.s + 1));
        Q.push({cost(top.s.f, top.s.s) - cost(top.s.f, top.s.s + 1), {top.s.f, top.s.s}});
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
