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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>

struct BIT
{
    int N;
    vector<long long> bit;

    void init(int n)
    {
        N = n;
        bit.assign(n + 1, 0);
    }

    void update(int idx, long long val)
    {
        while (idx <= N)
        {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    void updateMax(int idx, long long val)
    {
        while (idx <= N)
        {
            bit[idx] = max(bit[idx], val);
            idx += idx & -idx;
        }
    }

    long long pref(int idx)
    {
        long long ans = 0;
        while (idx > 0)
        {
            ans += bit[idx];
            idx -= idx & -idx;
        }
        return ans;
    }

    long long rsum(int l, int r)
    {
        return pref(r) - pref(l - 1);
    }

    long long prefMax(int idx)
    {
        long long ans = -2e9;
        while (idx > 0)
        {
            ans = max(ans, bit[idx]);
            idx -= idx & -idx;
        }
        return ans;
    }
};

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, q;
        cin >> n >> q;
        BIT b;
        b.init(n + 1);
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            b.update(x, 1);
        }
        auto printb = [&]() {
            for (size_t i = 0; i <= n; i++)
                cout << b.rsum(i, i) << ' ';
            cout << '\n';
        };
        for (size_t i = 0; i < q; i++)
        {
            int x;
            cin >> x;
            if (x > 0)
            {
                b.update(x, 1);
            }
            else
            {
                x = -x;
                int low = 0, high = n, ans = n;
                while (low <= high)
                {
                    int mid = (low + high) / 2;
                    if (b.pref(mid) < x)
                        low = mid + 1;
                    else
                    {
                        ans = min(ans, mid);
                        high = mid - 1;
                    }
                }
                b.update(ans, -1);
                // o.erase((o.find_by_order(x)));
            }
            // printb();
        }
        for (size_t i = 0; i <= n; i++)
        {
            if (b.rsum(i, i))
            {
                cout << i << '\n';
                return;
            }
        }
        cout << 0 << '\n';
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
