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
        int n, p;
        cin >> n >> p;
        map<int, int> cnt;
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            cnt[x]++;
        }
        vector<pair<int, int>> num;
        for (auto &x : cnt)
            num.pb(x);
        reverse(all(num));
        vector<int> res;
        const int LIM = 2e3 + 5;
        function<int(int, int)> f = [](int n, int p) -> int {
            int ans = 0;
            while (n)
            {
                n = n / p;
                ans += n;
            }
            return ans;
        };
        auto calc = [&](int n, int r, int p) -> int {
            return f(n, p) - f(n - r, p);
        };
        for (int i = 1; i < LIM; i++)
        {
            int c = 0, flag = 1, done = 0;
            for (auto &j : num)
            {
                int avail = 0;
                if (j.f > i + n - 1)
                {
                    flag = 0;
                    break;
                }
                avail = min(n, i + n - j.f) - done;
                db(i, j, avail);
                if (avail < j.s)
                {
                    flag = 0;
                    break;
                }
                done += j.s;
                c += calc(avail, j.s, p);
            }
            if (!c && flag)
                res.pb(i);
        }
        cout << res.size() << '\n';
        for (auto &&x : res)
        {
            cout << x << ' ';
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
