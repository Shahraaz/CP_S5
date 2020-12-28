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
    int n, q;
    cin >> n >> q;

    vector<ll> a(n);
    for (auto &x : a)
        cin >> x;
    sort(all(a));

    auto b = a;
    for (size_t i = 1; i < n; i++)
        b[i] += b[i - 1];

    auto getsum = [&](int l, int r) -> ll {
        return b[r] - (l > 0 ? b[l - 1] : 0);
    };

    queue<pair<int, int>> Q;
    set<pair<int, int>> vis;
    Q.push({0, n - 1});
    set<ll> myset;

    while (Q.size())
    {
        auto top = Q.front();
        Q.pop();
        if (vis.find(top) != vis.end())
            continue;
        myset.insert(getsum(top.first, top.second));
        vis.insert(top);
        auto mid = (a[top.first] + a[top.second]) / 2;
        // auto idx1 = lower_bound(all(a), mid) - a.begin();
        auto idx2 = lower_bound(all(a), mid + 1) - a.begin();

        db(top, a[top.first], a[top.second]);
        db(mid, idx2);

        pair<int, int> next;

        next.first = top.first;
        next.second = idx2 - 1;
        db(next);
        if (next.first <= next.second && vis.find(next) == vis.end())
            Q.push(next);

        next.first = idx2;
        next.second = top.second;
        db(next);
        if (next.first <= next.second && vis.find(next) == vis.end())
            Q.push(next);
    }

    db(myset);

    for (size_t i = 0; i < q; i++)
    {
        int x;
        cin >> x;
        if (myset.find(x) == myset.end())
            cout << "No\n";
        else
            cout << "Yes\n";
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
        solveCase();
    return 0;
}