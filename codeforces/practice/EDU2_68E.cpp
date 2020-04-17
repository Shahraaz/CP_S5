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
        const int D = 5000, N = 2 * D + 1;
        vector<pair<int, int>> hs[N], vs[N];
        for (size_t i = 0; i < n; i++)
        {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1 += D;
            y1 += D;
            x2 += D;
            y2 += D;
            if (y1 == y2)
                hs[y1].pb({min(x1, x2), max(x1, x2)});
            else
                vs[x1].pb({min(y1, y2), max(y1, y2)});
        }
        ll res = 0;
        int f[N + 1];
        auto upd = [&f, &N](int idx, int delta) -> void {
            for (++idx; idx < N; idx += idx & -idx)
                f[idx] += delta;
        };
        auto get = [&f, &N](int idx) -> int {
            int ret = 0;
            for (++idx; idx > 0; idx -= idx & -idx)
                ret += f[idx];
            return ret;
        };
        auto getRange = [&f, &N, &get](int l, int r) -> int {
            return get(r) - (l > 0 ? get(l - 1) : 0);
        };
        for (size_t y = 0; y < N; y++)
            for (auto &s : hs[y])
            {
                vector<vector<int>> d(N);
                memset(f, 0, sizeof f);
                int l = s.f, r = s.s;
                for (size_t x = l; x <= r; x++)
                    for (auto &s2 : vs[x])
                        if (s2.f <= y && s2.s > y)
                        {
                            d[s2.s].pb(x);
                            upd(x, 1);
                        }
                for (size_t y2 = y + 1; y2 < N; y2++)
                {
                    for (auto &s2 : hs[y2])
                    {
                        int cnt = getRange(s2.f, s2.s);
                        db(cnt);
                        res += cnt * (cnt - 1) / 2;
                    }
                    for (auto &x : d[y2])
                        upd(x, -1);
                }
            }
        cout << res << '\n';
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
