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

const int NAX = 2e5 + 5, MOD = 998244353;

void solveCase()
{
    int n, k;
    cin >> n >> k;
    set<pair<int, int>> avail;
    vector<int> a(n);
    vector<int> inv_a(n + 1);
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        avail.insert({i, a[i]});
        inv_a[a[i]] = i;
    }
    set<int> avail_b;
    vector<int> b(k);
    for (size_t i = 0; i < k; i++)
    {
        cin >> b[i];
        avail_b.insert(b[i]);
    }
    ll res = 1;
    for (size_t j = 0; j < k; j++)
    {
        db(j, b[j]);
        db(avail);
        db(avail_b);
        auto i = inv_a[b[j]];
        auto it = avail.lower_bound({i, a[i]});
        int cnt = 0;
        auto it2 = it;
        if (next(it2) != avail.end())
        {
            it2 = next(it2);
            if (avail_b.count(it2->s))
                it2 = it;
            else
                cnt++;
        }
        auto itprev = it;
        if (itprev != avail.begin())
        {
            itprev = prev(itprev);
            if (avail_b.count(itprev->s))
                itprev = it;
            else
                cnt++;
        }
        if (cnt == 0)
        {
            res = 0;
            break;
        }
        avail_b.erase(b[j]);
        if (cnt == 2)
        {
            res = res * 2;
            res %= MOD;
            // break;
            continue;
        }
        if (it2 != it)
        {
            assert(itprev == it);
            avail.erase(it2);
        }
        else
        {
            assert(it2 == it);
            avail.erase(itprev);
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
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
