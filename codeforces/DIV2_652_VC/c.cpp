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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), w(k);
    for (auto &x : a)
        cin >> x;
    for (auto &x : w)
        cin >> x;
    sort(all(a));
    sort(all(w));
    reverse(all(w));
    int i = 0;
    ll res = 0;
    vector<vector<int>> vecc(k);
    for (size_t k = 0; k < w.size(); k++)
    {
        vecc[w.size() - k - 1].pb(a.back());
        a.pop_back();
        w[k]--;
    }
    while (w.size() && w.back() == 0)
        w.pop_back();
    for (int k = w.size() - 1; k >= 0; k--)
    {
        while (w[k]--)
        {
            vecc[k].pb(a.back());
            a.pop_back();
        }
    }
    for (auto &x : vecc)
    {
        db(x);
        res += x.front() + x.back();
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
