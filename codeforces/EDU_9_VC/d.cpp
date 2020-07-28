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
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        map<int, int> a;
        vector<int> b(n);
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            b[i] = x;
            if (x <= m)
                a[x]++;
        }
        vector<int> cnt(m + 1);
        for (auto &x : a)
        {
            for (int i = x.f; i <= m; i += x.f)
                cnt[i] += x.s;
        }
        auto it = max_element(cnt.begin() + 1, cnt.end()) - cnt.begin();
        db(b);
        cout << it << ' ' << cnt[it] << '\n';
        for (size_t i = 0; i < n; i++)
        {
            // db(i, b[i], it, b[i] % it);
            if (it % b[i] == 0 && (cnt[it]--) > 0)
                cout << i + 1 << ' ';
        }
        cout << '\n';
    }
};

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
