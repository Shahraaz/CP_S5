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

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        vector<pair<ll, ll>> v(n);
        for (auto &x : v)
            cin >> x.f >> x.s;
        sort(all(v), [](const pair<ll, ll> &a, const pair<ll, ll> &b) -> bool {
            return a.f + a.s <= b.f + b.s;
        });
        // int ans = 0;
        int last = 0, ans = 1;
        for (size_t i = 1; i < n; i++)
            if (v[i].f - v[i].s >= v[last].f + v[last].s)
            {
                last = i;
                ans++;
            }
        cout << ans << '\n';
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
