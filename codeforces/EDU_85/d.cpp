// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
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

ll lastIndices[NAX];

class Solution
{
private:
public:
    Solution()
    {
        for (ll i = 1; i < NAX; i++)
            lastIndices[i] = i * i - i + 1;
    }
    ~Solution() {}
    void solveCase()
    {
        ll n, l, r;
        cin >> n >> l >> r;
        int idx1 = upper_bound(lastIndices, lastIndices + NAX, l) - lastIndices;
        --idx1;
        ll diff = l - lastIndices[idx1] + 1;
        db(idx1, lastIndices[idx1], diff);
        ll curr = 0, next = 0;
        idx1++;
        if (diff % 2 == 0)
        {
            curr = idx1;
            next = (diff + 1) / 2;
        }
        else
        {
            curr = (diff + 1) / 2;
            next = idx1;
        }
        db(diff, idx1);
        while (l <= r)
        {
            cout << curr << ' ';
            // db(l, curr, next, idx1);
            if (curr == idx1)
            {
                next++;
                if (next >= idx1)
                {
                    idx1++;
                    next = 1;
                    curr = idx1;
                }
            }
            swap(curr, next);
            ++l;
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