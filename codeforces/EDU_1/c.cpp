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
        using ld = long double;
        using point = complex<ld>;
        vector<pair<point, int>> points(n);
        for (auto &x : points)
        {
            int a, b;
            cin >> a >> b;
            // cin >> x.f.f >> x.f.s;
            x.f = point(a, b);
        }
        for (size_t i = 0; i < n; i++)
            points[i].s = i;
        sort(all(points), [](const pair<point, int> &a, const pair<point, int> &b) -> bool {
            return arg(a.f) < arg(b.f);
        });
        long double res = 1e18;
        const ld pi = acosl(-1);
        pair<int, int> indices;
        res = 1e30;
        db(points);
        // auto correct = [&pi](ld ang) -> ld {
        //     if (ans > 2 * pi)
        //         ang -= 2 * pi;
        // };
        for (size_t i = 0; i < n; i++)
        {
            int j = i + 1;
            j %= n;
            auto curr = arg(points[j].f) - arg(points[i].f);
            db(arg(points[j].f) / pi * 180, arg(points[i].f) / pi * 180);
            while (curr < 0)
                curr += 2 * pi;
            db(curr / pi * 180);
            if (curr < res)
            {
                res = curr;
                indices = {points[i].s, points[j].s};
            }
        }
        // db(sqrt(res.f / (1.0 * res.s)));
        db(res);
        cout << indices.f + 1 << ' ' << indices.s + 1 << '\n';
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
