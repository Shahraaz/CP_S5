// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#define pc(...)
#endif

#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using Random = std::uniform_int_distribution<T>;

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
        vector<ll> a(n + 1);
        vector<int> locs[5005];
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i + 1];
            locs[a[i + 1]].pb(i + 1);
            // sumXor[i + 1] = sumXor[i] ^ a[i + 1];
        }
        vector<ll> dp(n + 1, -1);
        function<ll(int)> solve = [&](int idx) -> ll {
            if (idx == n + 1)
                return 0;
            auto &ret = dp[idx];
            if (ret >= 0)
                return ret;
            ret = solve(idx + 1);
            if (locs[a[idx]].front() == idx)
            {
                // db(idx, a[idx]);
                // pc(locs[a[idx]]);
                // set<int> viss, vis;
                // viss.insert(a[idx]);
                // vis.insert(a[idx]);
                int fptr = locs[a[idx]].front();
                int rptr = fptr;
                bool ok = false;
                while (fptr <= rptr)
                {
                    int f = locs[a[fptr]].front();
                    int b = locs[a[fptr]].back();
                    if (f < idx)
                    {
                        db(idx, ret);
                        return ret;
                    }
                    if (f = fptr)
                    {
                        rptr = max(rptr, b);
                    }
                    ++fptr;
                }
                set<int> s;
                fptr = locs[a[idx]].front();
                while (fptr <= rptr)
                {
                    s.insert(a[fptr]);
                    ++fptr;
                }
                ll sumXor = 0;
                for (auto &x : s)
                    sumXor ^= x;
                db(idx, a[idx], sumXor, fptr, rptr);
                ret = max(ret, sumXor + solve(rptr + 1));
            }
            db(idx, ret);
            return ret;
        };
        cout << solve(1) << '\n';
        pc(dp);
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}