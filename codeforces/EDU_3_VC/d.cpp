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
        int n, m, k, s;
        cin >> n >> m >> k >> s;
        vector<int> a(n);
        vector<int> b(n);
        vector<pair<ll, int>> gadget[2];
        for (size_t i = 0; i < n; i++)
            cin >> a[i];
        for (size_t i = 0; i < n; i++)
            cin >> b[i];
        for (size_t i = 0; i < m; i++)
        {
            int t, x;
            cin >> t >> x;
            gadget[t - 1].pb({x, i});
        }
        gadget[0].pb({0, 0});
        gadget[1].pb({0, 0});
        sort(all(gadget[0]));
        sort(all(gadget[1]));
        for (size_t i = 1; i < gadget[0].size(); i++)
            gadget[0][i].f += gadget[0][i - 1].f;
        for (size_t i = 1; i < gadget[1].size(); i++)
            gadget[1][i].f += gadget[1][i - 1].f;
        int low = 0, high = n - 1, ans = INT_MAX;
        pair<int, int> decomposition;
        db(decomposition);
        auto check = [&](int maxD) -> bool {
            db(maxD);
            int D = *min_element(a.begin(), a.begin() + maxD + 1);
            int P = *min_element(b.begin(), b.begin() + maxD + 1);
            ll minMoniesNeeded = LLONG_MAX;
            for (int withDollar = 0; withDollar < gadget[0].size(); withDollar++)
            {
                int withPound = k - withDollar;
                db(withPound, withDollar);
                if (withPound >= 0 && withPound < gadget[1].size())
                {
                    ll curr = 0;
                    curr += D * gadget[0][withDollar].f;
                    curr += P * gadget[1][withPound].f;
                    if (curr < minMoniesNeeded)
                    {
                        decomposition.f = withDollar;
                        decomposition.s = withPound;
                        minMoniesNeeded = curr;
                    }
                }
            }
            db(maxD, minMoniesNeeded, s);
            return minMoniesNeeded <= s;
        };
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (check(mid))
            {
                high = mid - 1;
                ans = min(ans, mid);
            }
            else
                low = mid + 1;
        }
        if (ans == INT_MAX)
        {
            cout << -1 << '\n';
            return;
        }
        check(ans);
        cout << ans + 1 << '\n';
        int idx1 = min_element(a.begin(), a.begin() + ans + 1) - a.begin();
        int idx2 = min_element(b.begin(), b.begin() + ans + 1) - b.begin();
        for (size_t i = 1; i <= decomposition.f; i++)
            cout << gadget[0][i].s + 1 << ' ' << idx1 + 1 << '\n';
        for (size_t i = 1; i <= decomposition.s; i++)
            cout << gadget[1][i].s + 1 << ' ' << idx2 + 1 << '\n';
        db(ans, decomposition);
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
